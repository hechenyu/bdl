#include "stdc_file_reader.h"
#include "error.h"
#include "wrapposix.h"
#include "wrapstdio.h"

#ifndef STDC_FILE_READER_BUFFER_SIZE
#define STDC_FILE_READER_BUFFER_SIZE BUFSIZ
#endif

StdcFileReader::StdcFileReader()
{
    buffer_ = new char[STDC_FILE_READER_BUFFER_SIZE];
}

StdcFileReader::~StdcFileReader()
{
    if (is_open())
        close();
    delete [] buffer_;
}

void StdcFileReader::open(const char *filepath)
{
    if (is_open()) {
        err_quit("couldn't open %s, because this reader already opened!", filepath);
    }

    fp_ = Fopen(filepath, "r");
    setvbuf(fp_, buffer_, _IOFBF, STDC_FILE_READER_BUFFER_SIZE);
}

bool StdcFileReader::is_open()
{
    return fp_ != nullptr;
}

int StdcFileReader::read(void *buf, int len)
{
    return Fread2(buf, len, fp_);
}

int StdcFileReader::readn(void *buf, int n)
{
    return Fread2(buf, n, fp_);
}

long StdcFileReader::seek(long offset, int whence)
{
    Fseek(fp_, offset, whence);
    return Ftell(fp_);
}

void StdcFileReader::close()
{
    Fclose(fp_);
    fp_ = nullptr;
}

long StdcFileReader::file_size() 
{
    if (!is_open()) {
        err_quit("file_size error, because this reader not open!");
    }

    struct stat buf;
    Fstat(fileno(fp_), &buf);
    return buf.st_size;
}

