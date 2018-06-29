#ifndef __stdc_file_reader_h
#define __stdc_file_reader_h

#include <stdio.h>
#include "i_file_reader.h"

class StdcFileReader: public IFileReader {
private:
    FILE *fp_ = nullptr;
    char *buffer_;

public:
    StdcFileReader(); 
    ~StdcFileReader() override;

    void open(const char *filepath) override;
    bool is_open() override;
    int read(void *buf, int len) override;
    int readn(void *buf, int n) override;
    long seek(long offset, int whence) override;
    void close() override;
    long file_size() override;
};

#endif
