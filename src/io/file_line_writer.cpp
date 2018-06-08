#include <cassert>
#include "file_line_writer.h"

FileLineWriter::FileLineWriter(std::shared_ptr<IFileWriter> file_writer, int cache_size): 
    cache_size_(cache_size), writer_(file_writer)
{
    assert(cache_size > 0);
}

FileLineWriter::~FileLineWriter()
{
    if (!write_buf_.empty())
        writer_->write(write_buf_.data(), write_buf_.size());
}

void FileLineWriter::putline(const std::string &str)
{
    write_buf_ += str;
    write_buf_.push_back('\n');

    if (write_buf_.size() < static_cast<size_t>(cache_size_))
        return;

    writer_->write(write_buf_.data(), write_buf_.size());
    write_buf_.clear();
}

