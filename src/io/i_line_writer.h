#ifndef __i_line_writer_h
#define __i_line_writer_h

#include <string>

class ILineWriter {
public:
    virtual ~ILineWriter();

    virtual void putline(const std::string &str) = 0;
};

#endif

