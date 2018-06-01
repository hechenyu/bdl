#include "error.h"
#include "wrapposix.h"

#include <fcntl.h>
#include <stdarg.h>

int Open(const char *pathname, int oflag, ...)
{
    int		fd;
    va_list	ap;
    mode_t	mode;

    if (oflag & O_CREAT) {
        va_start(ap, oflag);		/* init ap to final named argument */
        mode = va_arg(ap, mode_t);
        if ( (fd = open(pathname, oflag, mode)) == -1)
            err_sys("open error for %s", pathname);
        va_end(ap);
    } else {
        if ( (fd = open(pathname, oflag)) == -1)
            err_sys("open error for %s", pathname);
    }
    return(fd);
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
    ssize_t n;

    if ( (n = read(fd, ptr, nbytes)) == -1)
        err_sys("read error");
    return(n);
}

void Write(int fd, void *ptr, size_t nbytes)
{
    if (write(fd, ptr, nbytes) != (ssize_t) nbytes)
        err_sys("write error");
}

off_t Lseek(int fd, off_t offset, int whence)
{
    off_t pos;

    if ( (pos = lseek(fd, offset, whence)) == (off_t) -1)
        err_sys("lseek error");
    return(pos);
}

void Close(int fd)
{
    if (close(fd) < 0)
        err_ret("close error");
}

void Ftruncate(int fd, off_t length)
{
    if (ftruncate(fd, length) == -1)
        err_sys("ftruncate error");
}
