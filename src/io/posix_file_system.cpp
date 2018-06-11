#include "posix_file_system.h"
#include "file_line_reader.h"
#include "file_line_writer.h"
#include "posix_file_reader.h"
#include "posix_file_writer.h"

using namespace std;

vector<string> PosixFileSystem::list_dir_file(const string &dir)
{
    return vector<string>();
}

shared_ptr<IFileReader> PosixFileSystem::create_file_reader()
{
    return make_shared<PosixFileReader>();
}

shared_ptr<IFileWriter> PosixFileSystem::create_file_writer()
{
    return make_shared<PosixFileWriter>();
}

shared_ptr<ILineReader> PosixFileSystem::create_line_reader(const string &path)
{
    auto file_reader = create_file_reader();
    file_reader->open(path.c_str());
    const int buf_size = LINE_BUF_SIZE;
    return make_shared<FileLineReader>(file_reader, buf_size);
}

shared_ptr<ILineWriter> PosixFileSystem::create_line_writer(const string &path)
{
    auto file_writer = create_file_writer();
    file_writer->open(path.c_str());
    file_writer->seek(0, SEEK_END);
    const int buf_size = LINE_BUF_SIZE;
    return make_shared<FileLineWriter>(file_writer, buf_size);
}
