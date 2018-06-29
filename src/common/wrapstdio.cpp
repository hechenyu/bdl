/*
 * Standard I/O wrapper functions.
 */

#include	"wrapstdio.h"

void
Fclose(FILE *fp)
{
	if (fclose(fp) != 0)
		err_quit("fclose error");
}

FILE *
Fdopen(int fd, const char *type)
{
	FILE	*fp;

	if ( (fp = fdopen(fd, type)) == NULL)
		err_quit("fdopen error");

	return(fp);
}

char *
Fgets(char *ptr, int n, FILE *fp)
{
	char	*rptr;

	if ( (rptr = fgets(ptr, n, fp)) == NULL && ferror(fp))
		err_quit("fgets error");

	return (rptr);
}

FILE *
Fopen(const char *filename, const char *mode)
{
	FILE	*fp;

	if ( (fp = fopen(filename, mode)) == NULL)
		err_quit("fopen error");

	return(fp);
}

void
Fputs(const char *ptr, FILE *fp)
{
	if (fputs(ptr, fp) == EOF)
		err_quit("fputs error");
}

size_t 
Fread(void *ptr, size_t size, size_t nobj, FILE *fp)
{
    size_t n;
    if ((n = fread(ptr, size, nobj, fp)) < nobj) {
        if (ferror(fp)) {
            err_quit("fread error");
        }
    }

    return n;
}

size_t
Fread2(void *ptr, size_t size, FILE *fp)
{
    return Fread(ptr, 1, size, fp);
}

void 
Fwrite(const void *ptr, size_t size, size_t nobj, FILE *fp)
{
    size_t n;
    if ((n = fwrite(ptr, size, nobj, fp)) != nobj) {
        err_quit("fwrite error");
    }
}

void 
Fwrite2(const void *ptr, size_t size, FILE *fp)
{
    Fwrite(ptr, size, 1, fp);
}

long
Ftell(FILE *fp)
{
    long offset;
    if ((offset = ftell(fp)) == -1) {
        err_quit("ftell error");
    }
    return offset;
}

void
Fseek(FILE *fp, long int offset, int origin)
{
    if (fseek(fp, offset, origin) == -1) {
        err_quit("fseek error");
    }
}

FILE *
Popen(const char *command, const char *mode)
{
	FILE	*fp;

	if ( (fp = popen(command, mode)) == NULL)
		err_quit("popen error");
	return(fp);
}

int
Pclose(FILE *fp)
{
	int		n;

	if ( (n = pclose(fp)) == -1)
		err_quit("pclose error");
	return(n);
}


