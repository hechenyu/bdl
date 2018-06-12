#ifndef __file_line_reader_h
#define __file_line_reader_h

#include <string>
#include <vector>
#include <memory>
#include "i_line_reader.h"
#include "i_file_reader.h"

class FileLineReader: public ILineReader {
private:
    int  read_cnt_ = 0;
    char *read_ptr_ = nullptr;
    std::vector<char> read_buf_;
    std::shared_ptr<IFileReader> reader_;

public:
    FileLineReader(std::shared_ptr<IFileReader> file_reader, int buf_size);
    ~FileLineReader() override;

    void open(const char *filepath) override;
    bool is_open() override;

    bool getline(std::string &str) override;

    void close() override;

private:
    int read_char(char *ptr);  // if eof return 0, else return 1 and save data in *ptr
};

#endif
