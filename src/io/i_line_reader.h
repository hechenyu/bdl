#ifndef __i_line_reader_h
#define __i_line_reader_h

#include <string>

class ILineReader {
public:
    virtual ~ILineReader();

    // if no data return false, else return true
    virtual bool getline(std::string &str) = 0;
};

#endif
