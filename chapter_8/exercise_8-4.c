#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#undef NULL	

#define NULL		0
#define EOF		(-1)
#define BUFSIZ		1024
#define OPEN_MAX	20

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

typedef struct _iobuf {

	int	cnt;
	char	*ptr;
	char	*base;
	int	flag;
	int	fd;
	long	bufpos;	

} FILE;

extern FILE	_iob[OPEN_MAX];

#define stdin	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	(&_iob[2])

enum _flags {

	_READ	= 01,
	_WRITE	= 02,
	_UNBUF	= 04,
	_EOF	= 010,
	_ERR	= 020

};

int	_fillbuf (FILE *fp);
int	_flushbuf (int x, FILE *fp);

#define feof(p)		(((p)->flag & _EOF) != 0)
#define ferror(p)	(((p)->flag & _ERR) != 0)
#define fileno(p)	((p)->fd)

#define getc(p)		(--(p)->cnt >= 0 \
				? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p)	(--(p)->cnt >= 0 \
				? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)

#define PERMS		0666

FILE *fopen (char *name, char *mode)

{
	int	fd;
	FILE	*fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')

		return NULL;

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)

		if ((fp->flag & (_READ | _WRITE)) == 0)

			break;

	if (fp == _iob + OPEN_MAX)

		return NULL;

	if (*mode == 'w')

		fd = creat(name, PERMS);

	else if (*mode == 'a') {

		if ((fd = open(name, O_WRONLY, 0)) == -1)

			fd = creat(name, PERMS);

		lseek(fd, 0L, 2);

	} else

		fd = open(name, O_RDONLY, 0);

	if (fd == -1)

		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	fp->bufpos = 0;

	return fp;
}

int _fillbuf (FILE *fp)

{
	int	bufsize;

	if ((fp->flag & (_READ | _ERR)) != _READ)

		return EOF;

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	if (fp->base == NULL) {

		if ((fp->base = (char *) malloc(bufsize)) == NULL)

			return EOF;

	} else

		fp->bufpos += fp->ptr - fp->base;

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {

		if (fp->cnt == -1)

			fp->flag |= _EOF;

		else

			fp->flag |= _ERR;

		fp->cnt = 0;
		return EOF;

	} else

		fp->flag &= ~_EOF;

	return (unsigned char) *fp->ptr++;
}

int _flushbuf (int x, FILE *fp)

{
	int	bufsize;

	if ((fp->flag & (_WRITE | _ERR)) != _WRITE)

		return EOF;

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	if (fp->base == NULL) {

		if ((fp->base = (char *) malloc(bufsize)) == NULL)

			return EOF;

	} else if (write(fp->fd, fp->base, bufsize) != bufsize) {

		fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;

	} else 	

		fp->bufpos += bufsize;

	fp->ptr = fp->base;			
	fp->cnt = bufsize - 1;

	return (unsigned char) (*fp->ptr++ = x);
}

int	_flush (FILE *fp);

int fflush (FILE *fp)

{
	if (fp != NULL) {

		if (fp->flag & _ERR)

			return EOF;

		else if ((fp->flag & _WRITE) && fp->base != NULL)

			return _flush(fp);

		else

			return 0;

	} else {

		int	r, i;

		r = 0;
		for (i = 0; i < OPEN_MAX; i++) 

			if ((_iob[i].flag & (_WRITE | _ERR)) == _WRITE
			&& _iob[i].base != NULL
			&& _flush(&_iob[i]) == EOF)

				r = EOF;

		return r;

	}
}

int fseek (FILE *fp, long offset, int whence)

{
	long    curpos, newpos;

        if ((fp->flag & _ERR) 
	|| (!(fp->flag & _READ) && !(fp->flag & _WRITE)))

                return -1;

	curpos = fp->bufpos + (fp->base != NULL ? fp->ptr - fp->base : 0);

	if (whence == SEEK_SET)

		newpos = offset;

	else if (whence == SEEK_CUR)

		newpos = curpos + offset;

	else {	/* SEEK_END */

		if ((newpos = lseek(fp->fd, 0, SEEK_END)) == -1
		|| lseek(fp->fd, fp->bufpos, SEEK_SET) == -1) {

			fp->flag |= _ERR;
			fp->cnt = 0;
			return -1;

		}
		newpos += offset;

	}

        if (fp->flag & _UNBUF)

		fp->bufpos = newpos;

	else if (fp->flag & _READ) {

		if (fp->base == NULL)

			fp->bufpos = newpos;

		else if (newpos < fp->bufpos || newpos >= curpos + fp->cnt) {

			fp->ptr = fp->base;
			fp->cnt = 0;
			fp->bufpos = newpos;

		} else {

			fp->ptr = fp->base + newpos - fp->bufpos;
			fp->cnt -= newpos - curpos;

		}

	} else {

		if (fp->base == NULL)

			fp->bufpos = newpos;

		else if (newpos < curpos || newpos >= fp->bufpos + BUFSIZ) {

			_flush(fp);
			fp->bufpos = newpos;

		} else {

			long	n;

			n = newpos - curpos; 
			while (n--) {

				*fp->ptr++ = 0;
				fp->cnt++;

			}

		}

	}
	
	if (lseek(fp->fd, fp->bufpos, SEEK_SET) == -1) {

		fp->flag |= _ERR;
		fp->cnt = 0;
		return -1;

	} else

		return 0;
}

int fclose (FILE *fp)

{
	int	r;

	r = 0;
	if (fp->flag & _WRITE)

		r = fflush(fp);

	if (fp->base != NULL)

		free(fp->base);

	fp->flag = 0;

	return close(fp->fd) == -1 ? EOF : r;
}

int _flush (FILE *fp) 

{
	if (write(fp->fd, fp->base, fp->ptr - fp->base) 
		!= fp->ptr - fp->base) {

		fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;

	} else {

		fp->bufpos += fp->ptr - fp->base;
		fp->ptr = fp->base;
		fp->cnt = fp->flag & _UNBUF ? 0 : BUFSIZ;

		return 0;

	}
}

FILE _iob[OPEN_MAX] = {

	{ 0, NULL, NULL, _READ, 0 },
	{ 0, NULL, NULL, _WRITE, 1 },
	{ 0, NULL, NULL, _WRITE | _UNBUF, 2 }

};

#include <string.h>

int main ()

{
	FILE	*f;
	int	ok;
	char	test_ok[] = "fseek() works fine.\n",
		test_failed[] = "fseek() doesn't work!\n",
		*s;

	/* Create a test file "test.bin" and write in it.  Then re-open it in 
	 * read mode and read it to check.
 	 */

	f = fopen("test.bin", "w");
	fseek(f, 2000, SEEK_SET);
	putc('x', f); 
	fseek(f, -2000, SEEK_CUR);
	putc('a', f); 
	fseek(f, 100, SEEK_SET);
	putc('b', f); 
	fseek(f, 200, SEEK_SET);
	putc('c', f); 
	fseek(f, 0, SEEK_END);
	putc('y', f);
	fclose(f);

	f = fopen("test.bin", "r");
	fseek(f, 1, SEEK_CUR);
	ok = getc(f) == 'a' ? !0 : 0;
	fseek(f, 100, SEEK_SET);
	ok = getc(f) == 'b' ? !0 : 0;
	fseek(f, 99, SEEK_CUR);
	ok = getc(f) == 'c' ? !0 : 0;
	fseek(f, -100, SEEK_CUR);
	ok = getc(f) == 'b' ? !0 : 0;
	fseek(f, -2, SEEK_END);
	ok = getc(f) == 'x' ? !0 : 0;
	ok = getc(f) == 'y' ? !0 : 0; 
	fseek(f, 100, SEEK_SET);
	ok = getc(f) == 'b' ? !0 : 0;
	fclose(f);

	s = ok ? test_ok : test_failed;
	write(1, s, strlen(s));

	return 0;
}
