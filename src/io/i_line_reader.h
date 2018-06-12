#ifndef __i_line_reader_h
#define __i_line_reader_h

#include <string>

class ILineReader {
public:
    virtual ~ILineReader();

    virtual void open(const char *filepath) = 0;
    virtual bool is_open() = 0;

    // if no data return false, else return true
    virtual bool getline(std::string &str) = 0;

    virtual void close() = 0;
};

#endif
