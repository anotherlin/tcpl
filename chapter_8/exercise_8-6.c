#include <unistd.h>

#define NALLOC	1024

typedef long	Align;

union header {

	struct {

		union header	*ptr;
		unsigned	size;

	} s;

	Align	x;

};

typedef union header	Header;

static Header	base;
static Header	*freep = NULL;

static Header 	*morecore (unsigned nu);

void *malloc (unsigned nbytes)

{
	Header		*p, *prevp;
	unsigned	nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {

		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;

	}

	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {

		if (p->s.size >= nunits) {

			if (p->s.size == nunits) 

				prevp->s.ptr = p->s.ptr;

			else {

				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;

			}
			freep = prevp;
	
			return (void *) (p + 1);

		}
		if (p == freep)
	
			if ((p = morecore(nunits)) == NULL)

				return NULL;

	}
}

void free (void *ap)

{
	Header	*bp, *p;

	bp = (Header *) ap - 1;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)

		if (p >= p->s.ptr && (bp > p ||  bp < p->s.ptr))	

			break;

	if (bp + bp->s.size == p->s.ptr) {

		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;

	} else

		bp->s.ptr = p->s.ptr;

	if (p + p->s.size == bp) {

		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;

	} else

		p->s.ptr = bp;

	freep = p;
}

static Header *morecore (unsigned nu)

{
	char	*cp;
	Header	*up;

	if (nu < NALLOC)

		nu = NALLOC;

	if ((cp = sbrk(nu * sizeof(Header))) == (char *) -1)

		return NULL;
	
	up = (Header *) cp;
	up->s.size = nu;
	free((void *) (up + 1));

	return freep;
}

void *calloc (unsigned n, unsigned size)

{
	void	*p;

	if ((p = malloc(n * size)) != NULL) {

		int	i;
		long	*l;
		char	*c;

		/* We use the fact that returned memory is always long aligned.
		 * It can be zeroed faster.
 		 */ 

		l = (long *) p;
		for (i = 0; i < n * size / sizeof(long); i++)

			*l++ = 0;

		c = (char *) p + (n * size / sizeof(long)) * sizeof(long);
		for (i = 0; i < n * size % sizeof(long); i++)

			*c++ = 0;

	}

	return p;
}

#include <stdio.h>

#define ARRAYSIZE	29

int main ()

{
	char	*a;
	int	i;

	a = calloc(ARRAYSIZE, sizeof(long));
	for (i = 0; i < ARRAYSIZE; i++)

		if (a[i]) {

			printf("calloc() doesn't work!\n");
			return 1;

		}

	printf("calloc() works fine.\n");

	return 0;
}
