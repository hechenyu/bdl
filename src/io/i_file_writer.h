#ifndef __i_file_writer_h
#define __i_file_writer_h

class IFileWriter {
public:
    virtual ~IFileWriter();

//    virtual void open_excl(const char *filepath) = 0;  // open and if file exist, throw error
    virtual void open(const char *filepath) = 0;    // open for write, and seek to begin
    virtual bool is_open() = 0;
//    virtual void truncate(int len) = 0;
    virtual void write(const char *buf, int len) = 0;
    virtual int seek(int offset, int whence) = 0;   // whence: SEEK_SET, SEEK_CUR, SEEK_END
    virtual void close() = 0;
};

#endif
