#include "posix_file_writer.h"
#include "error.h"
#include "wrapposix.h"
#include <fcntl.h>

#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

PosixFileWriter::PosixFileWriter()
{
}

PosixFileWriter::~PosixFileWriter() 
{
    if (is_open())
        close();
}

void PosixFileWriter::open(const char *filepath)
{
    if (is_open()) {
        err_quit("couldn't open %s, because this writer already opened!", filepath);
        return;
    }

    fd_ = Open(filepath, O_WRONLY | O_CREAT , FILE_MODE);
}

bool PosixFileWriter::is_open()
{
    return (fd_ >= 0);
}

void PosixFileWriter::write(const char *buf, int len) 
{
    Write(fd_, const_cast<char *>(buf), len);
}

int PosixFileWriter::seek(int offset, int whence) 
{
    return Lseek(fd_, offset, whence);
}

void PosixFileWriter::close()
{
    ::close(fd_);
}
