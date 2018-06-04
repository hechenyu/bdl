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

int PosixFileReader::seek(int offset, int whence)
{
    return Lseek(fd_, offset, whence);
}

void PosixFileReader::close()
{
    Close(fd_);
    fd_ = -1;
}
