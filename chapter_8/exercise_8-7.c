#include <unistd.h>

#define NALLOC		1024

/* Now there is a limit on the maximum amount of memory (in sizeof(Header) 
 * units) that can be allocated at once. 
 */

#define MAXALLOC	1000000

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
	if (nunits > MAXALLOC)

		return NULL;
	
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

	/* Make sure that the block to free is not NULL and that the memory
	 * allocator has been initialized. 
	 */

	if (ap == NULL || freep == NULL)

		return;

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

#include <stdio.h>

int main ()


{
	/* The program will not crash. */

	free((void *) &base);
	malloc(1000000000);
	free(NULL);

	printf("Ok!\n");

	return 0;
}
