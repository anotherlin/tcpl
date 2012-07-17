#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* Standard UNIX system calls are used instead of low level directory content
 * and inode readings.
 */

void	fsize (char *name);

int main (int argc, char **argv)

{
	if (argc == 1)

		fsize(".");

	else 

		while (--argc > 0)

			fsize(*++argv);

	return 0;
}

void	dirwalk (char *dir, void (*fcn) (char *));

void fsize (char *name)

{
	struct stat	stbuf;
	int		f;

	if (stat(name, &stbuf) == -1) {

		fprintf(stderr, "fsize: can't access %s\n", name);
		return;

	}

	if (S_ISDIR(stbuf.st_mode))

		dirwalk(name, fsize);

	printf("%s\n", name);

	/* Print file type. */
	
	if (S_ISREG(stbuf.st_mode))

		putchar('-');

	else if (S_ISDIR(stbuf.st_mode))

		putchar('d');

	else if (S_ISCHR(stbuf.st_mode))

		putchar('c');

	else if (S_ISBLK(stbuf.st_mode))

		putchar('b');

	else

		putchar('?');	/* Unknown file type. */

	/* Print permissions. */

	f = 0400;
	do {

		putchar(stbuf.st_mode & f ? 'r' : '-');
		f >>= 1;
		putchar(stbuf.st_mode & f ? 'w' : '-');
		f >>= 1;
		putchar(stbuf.st_mode & f ? 'x' : '-');
		f >>= 1;

	} while (f);

	/* Print size (in bytes) and last modification time. */

	printf(" %8ld", stbuf.st_size);
	printf(" %s", ctime(&stbuf.st_mtime));
}

#define MAX_PATH	1024

void dirwalk (char *dir, void (*fcn) (char *))

{
	char		name[MAX_PATH];
	DIR		*dfd;
	struct dirent	*dp;

	if ((dfd = opendir(dir)) == NULL) {

		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;

	} 

	while ((dp = readdir(dfd)) != NULL) {

		if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))

			continue;

		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))

			fprintf(stderr, 
				"dirwalk: name %s/%s too long\n",
				dir, dp->d_name);

		else {
	
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);

		}

	}

	closedir(dfd);
}
