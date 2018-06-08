#ifndef __file_line_writer_h
#define __file_line_writer_h

#include <string>
#include <memory>
#include "i_line_writer.h"
#include "i_file_writer.h"

class FileLineWriter: public ILineWriter {
private:
    const int cache_size_;
    std::string write_buf_;
    std::shared_ptr<IFileWriter> writer_;

public:
    FileLineWriter(std::shared_ptr<IFileWriter> file_writer, int cache_size);
    ~FileLineWriter();
    void putline(const std::string &str) override;
};

#endif

