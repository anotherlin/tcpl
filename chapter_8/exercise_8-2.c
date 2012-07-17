#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/* This is just exercise 8-3 written using bit-fields instead.  The generated
 * code is slightly bigger, and probably somewhat slower too.
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

	struct {

		unsigned	read	: 1;
		unsigned	write 	: 1;
		unsigned	unbuf 	: 1;
		unsigned	eof 	: 1;
		unsigned	err 	: 1;

	} flag;

	int	fd;

} FILE;

extern FILE	_iob[OPEN_MAX];

#define stdin	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	(&_iob[2])

int	_fillbuf (FILE *fp);
int	_flushbuf (int x, FILE *fp);

#define feof(p)		((p)->flag.eof)
#define ferror(p)	((p)->flag.err)
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

		if (!fp->flag.read && !fp->flag.write)

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
	fp->flag.read 
		= fp->flag.write 
		= fp->flag.unbuf 
		= fp->flag.eof
		= fp->flag.err
		= 0;

	if (*mode == 'r')

		fp->flag.read = !0;

	else

		fp->flag.write = !0;

	return fp;
}

int _fillbuf (FILE *fp)

{
	int	bufsize;

	if (!fp->flag.read || fp->flag.eof || fp->flag.err)

		return EOF;

	bufsize = fp->flag.unbuf ? 1 : BUFSIZ;

	if (fp->base == NULL)

		if ((fp->base = (char *) malloc(bufsize)) == NULL)

			return EOF;

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {

		if (fp->cnt == -1)

			fp->flag.eof = !0;

		else

			fp->flag.err = !0;

		fp->cnt = 0;
		return EOF;

	}

	return (unsigned char) *fp->ptr++;
}

int _flushbuf (int x, FILE *fp)

{
	int	bufsize;

	if (!fp->flag.write || fp->flag.err)

		return EOF;

	bufsize = fp->flag.unbuf ? 1 : BUFSIZ;

	if (fp->base == NULL) {

		if ((fp->base = (char *) malloc(bufsize)) == NULL)

			return EOF;

	} else if (write(fp->fd, fp->base, bufsize) != bufsize) {

		fp->flag.err = !0;
		fp->cnt = 0;
		return EOF;

	} 	

	fp->ptr = fp->base;			
	fp->cnt = bufsize - 1;

	return (unsigned char) (*fp->ptr++ = x);
}

int 	_flush (FILE *fp);

int fflush (FILE *fp)

{
	if (fp != NULL) {

		if (fp->flag.err)

			return EOF;

		else if (fp->flag.write && fp->base != NULL)

			return _flush(fp);

		else

			return 0;

	} else {

		int	r, i;

		r = 0;
		for (i = 0; i < OPEN_MAX; i++) 

			if (_iob[i].flag.write && !_iob[i].flag.err
			&& _iob[i].base != NULL 
			&& _flush(&_iob[i]) == EOF)

				r = EOF;

		return r;

	}
}

int fclose (FILE *fp)

{
	int	r;

	r = 0;
	if (fp->flag.write)

		r = fflush(fp);

	if (fp->base != NULL)

		free(fp->base);

	fp->flag.read = fp->flag.write = 0;

	return close(fp->fd) == -1 ? EOF : r;
}

int _flush (FILE *fp) 

{
	if (write(fp->fd, fp->base, fp->ptr - fp->base) 
		!= fp->ptr - fp->base) {

		fp->flag.err = !0;
		fp->cnt = 0;
		return EOF;

	} else {

		fp->ptr = fp->base;
		fp->cnt = fp->flag.unbuf ? 0 : BUFSIZ;

		return 0;

	}
}

FILE _iob[OPEN_MAX] = {

	{ 0, NULL, NULL, { !0, 0, 0, 0, 0 } , 0 },
	{ 0, NULL, NULL, { 0, !0, 0, 0, 0 }, 1 },
	{ 0, NULL, NULL, { 0, !0, !0, 0, 0 }, 2 }

};

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
	fflush(stdout);

        return 0;
}
