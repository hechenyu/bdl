#include <cassert>
#include "file_line_writer.h"

FileLineWriter::FileLineWriter(std::shared_ptr<IFileWriter> file_writer, int cache_size): 
    cache_size_(cache_size), writer_(file_writer)
{
    assert(cache_size > 0);
}

FileLineWriter::~FileLineWriter()
{
    if (is_open())
        close();
}

void FileLineWriter::open_truncate(const char *filepath)
{
    writer_->open(filepath);
    writer_->truncate();
}

void FileLineWriter::open_for_append(const char *filepath)
{
    writer_->open(filepath);
    writer_->seek(0, SEEK_END);
}

bool FileLineWriter::is_open()
{
    return writer_->is_open();
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

void FileLineWriter::close()
{
    if (!write_buf_.empty())
        writer_->write(write_buf_.data(), write_buf_.size());

    writer_->close();
}
