#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/* Undefine NULL macro, as it may already be defined in one of the previously 
 * included headers. 
 */

#undef NULL	

#define NULL		0
#define EOF		(-1)
#define BUFSIZ		1024
#define OPEN_MAX	20

typedef struct _iobuf {

	int	cnt;
	char	*ptr;
	char	*base;
	int	flag;
	int	fd;

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

	return fp;
}

int _fillbuf (FILE *fp)

{
	int	bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)

		return EOF;

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	if (fp->base == NULL)

		if ((fp->base = (char *) malloc(bufsize)) == NULL)

			return EOF;

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {

		if (fp->cnt == -1)

			fp->flag |= _EOF;

		else

			fp->flag |= _ERR;

		fp->cnt = 0;
		return EOF;

	}

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

	} 	

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

int fclose (FILE *fp)

{
	int	r;

	/* If open for writing, flush write buffer. */

	r = 0;
	if (fp->flag & _WRITE)

		r = fflush(fp);	

	/* Free buffer memory then close file. */

	if (fp->base != NULL)

		free(fp->base);

	fp->flag = 0;

	return close(fp->fd) == -1 ? EOF : r;
}

/* This function works only for non-erroneous write-only file, checks must be
 * made before calling it.
 */

int _flush (FILE *fp) 

{
	if (write(fp->fd, fp->base, fp->ptr - fp->base) 
		!= fp->ptr - fp->base) {

		fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;

	} else {

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

/* To test this sample implementation of stdio.h's functions, we use the code
 * of exercise 7-2 (which has been slightly modified).
 */

#include <ctype.h>

#define TABSIZE         8
#define LINESIZE        80

int main ()

{
        int     column, c, d;

        column = 0;
        while ((c = getchar()) != EOF) {

                if (c == '\t')

                        column += TABSIZE;

                else if (c == '\n')

                        column = 0;

                else

                        column++;

                if (isprint(c) || c == '\t' || c == '\n') {

                        if (column > LINESIZE) {

                                putchar('\n');
                                column = c == '\t' ? TABSIZE : 1;

                        }
                        putchar(c);

                } else {

                        if ((column += 3) > LINESIZE) {

                                putchar('\n');
                                column = 4;

                        }
			putchar('\\');

			d = (c >> 4) & 0x0f;
			d += d < 10 ? '0' : 'a';
			putchar(d);

			c &= 0x0f;
			c += c < 10 ? '0' : 'a';
			putchar(c);

                }

        }
	fflush(stdout);		/* Flush write buffer. */

        return 0;
}
