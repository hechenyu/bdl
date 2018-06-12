#ifndef __i_line_writer_h
#define __i_line_writer_h

#include <string>

class ILineWriter {
public:
    virtual ~ILineWriter();

    virtual void open_truncate(const char *filepath) = 0;       // open for write and truncate
    virtual void open_for_append(const char *filepath) = 0;     // open for append
    virtual bool is_open() = 0;

    virtual void putline(const std::string &str) = 0;

    virtual void close() = 0;
};

#endif

