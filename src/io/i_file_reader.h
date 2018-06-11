#ifndef __i_file_reader_h
#define __i_file_reader_h

class IFileReader {
public:
    virtual ~IFileReader();

    virtual void open(const char *filepath) = 0;
    virtual bool is_open() = 0;
    virtual int read(void *buf, int len) = 0;       // if EOF, return 0
    virtual int readn(void *buf, int n) = 0;        // read n bytes, if get EOF, maybe read bytes less than n
    virtual long seek(long offset, int whence) = 0; // whence: SEEK_SET, SEEK_CUR, SEEK_END
    virtual void close() = 0;
    virtual long file_size() = 0;
};

#endif
