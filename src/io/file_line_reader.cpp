#include <cassert>
#include "file_line_reader.h"

using namespace std;

FileLineReader::FileLineReader(shared_ptr<IFileReader> file_reader, int buf_size): 
    read_buf_(buf_size), reader_(file_reader)
{
}

FileLineReader::~FileLineReader()
{
    if (is_open())
        close();
}

void FileLineReader::open(const char *filepath)
{
    reader_->open(filepath);
}

bool FileLineReader::is_open()
{
    return reader_->is_open();
}

int FileLineReader::read_char(char *ptr)
{
	if (read_cnt_ <= 0) {
        read_cnt_ = reader_->read(read_buf_.data(), read_buf_.size());
        if (read_cnt_ == 0)
            return 0;
        read_ptr_ = read_buf_.data();
	}

	read_cnt_--;
	*ptr = *read_ptr_++;
	return(1);
}

bool FileLineReader::getline(string &str)
{
    str.clear();
    char c;
    while (true) {
        int rc = read_char(&c);
        if (rc == 0) {
            break;
        }
        assert(rc == 1);
        str.push_back(c);
        if (c == '\n') break;
    }

    if (str.empty())
        return false;

    if (str.back() == '\n')
        str.pop_back();

    return true;
}

void FileLineReader::close()
{
    reader_->close();
}

