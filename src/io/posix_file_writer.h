#ifndef __posix_file_writer_h
#define __posix_file_writer_h

#include "i_file_writer.h"

class PosixFileWriter: public IFileWriter {
private:
    int fd_ = -1;

public:
    PosixFileWriter();
    ~PosixFileWriter() override;

    void open(const char *filepath) override;
    bool is_open() override;
    void truncate() override;
    void truncate(int len) override;
    void write(const char *buf, int len) override;
    int seek(int offset, int whence) override;
    void close() override;

    PosixFileWriter(const PosixFileWriter &) = delete;
    void operator =(const PosixFileWriter &) = delete;
};

#endif
