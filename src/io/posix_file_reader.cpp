#include "posix_file_reader.h"
#include "error.h"
#include "wrapposix.h"
#include <fcntl.h>

PosixFileReader::PosixFileReader()
{
}

PosixFileReader::~PosixFileReader()
{
    if (is_open())
        close();
}

void PosixFileReader::open(const char *filepath)
{
    if (is_open()) {
        err_quit("couldn't open %s, because this reader already opened!", filepath);
    }

    fd_ = Open(filepath, O_RDONLY);
}

bool PosixFileReader::is_open()
{
    return (fd_ >= 0);
}

int PosixFileReader::read(void *buf, int len)
{
    return Read(fd_, buf, len);
}

int PosixFileReader::readn(void *buf, int n)
{
    int nleft = n;
    int nread = 0;
	char *ptr = static_cast<char *>(buf);
    while (nleft > 0) {
        if ( (nread = this->read(ptr, nleft)) == 0) {
            break;              /* EOF */
        }

        nleft -= nread;
        ptr   += nread;
    }

	return(n - nleft);		/* return >= 0 */
}

long PosixFileReader::seek(long offset, int whence)
{
    return Lseek(fd_, offset, whence);
}

void PosixFileReader::close()
{
    Close(fd_);
    fd_ = -1;
}

long PosixFileReader::file_size() 
{
    struct stat buf;
    Fstat(fd_, &buf);
    return buf.st_size;
}

