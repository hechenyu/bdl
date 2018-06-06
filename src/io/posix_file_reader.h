#ifndef __posix_file_reader_h
#define __posix_file_reader_h

#include "i_file_reader.h"

class PosixFileReader: public IFileReader {
private:
    int fd_ = -1;

public:
    PosixFileReader(); 
    ~PosixFileReader() override;

    void open(const char *filepath) override;
    bool is_open() override;
    int read(void *buf, int len) override;
    long seek(long offset, int whence) override;
    void close() override;
    long file_size() override;
};

#endif
