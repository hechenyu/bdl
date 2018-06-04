#ifndef __i_file_reader_h
#define __i_file_reader_h

class IFileReader {
public:
    virtual ~IFileReader();

    virtual void open(const char *filepath) = 0;
    virtual bool is_open() = 0;
    virtual int read(void *buf, int len) = 0;       // if EOF, return 0
    virtual int seek(int offset, int whence) = 0;   // whence: SEEK_SET, SEEK_CUR, SEEK_END
    virtual void close() = 0;
};

#endif
