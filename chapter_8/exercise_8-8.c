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

void bfree (void *p, unsigned n)

{
	if (n / sizeof(Header) >= 2) {

		Header	*up;

		up = (Header *) p;
		up->s.size = n / sizeof(Header);
		free((void *) (up + 1));

	}
}

#include <stdio.h>

/* To test bfree(), a block size of one allocation unit (sizeof(Header)) more 
 * than the default allocation size, is chosen.
 */

#define ARRAYSIZE	((NALLOC + 2) * sizeof(Header))

char	array[ARRAYSIZE];

int main ()

{
	/* Allocate one unit, this will start the memory allocator. */

	malloc(1);

	/* After the bfree(), the memory allocator has one free block of 
 	 * NALLOC - 2 units and another (the one made available by bfree()) of 
	 * NALLOC + 1 units, malloc(NALLOC + 1) will return the later. 
 	 */

	bfree(array, ARRAYSIZE);
	if ((char *) malloc((NALLOC + 1) * sizeof(Header)) 
		== array + sizeof(Header)) {

		printf("bfree() works ok.\n");
		return 0;

	} else {

		printf("doesn't work!\n");
		return 1;
	
	}
}
