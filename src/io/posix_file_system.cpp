#include <boost/filesystem.hpp>
#include "posix_file_system.h"
#include "file_line_reader.h"
#include "file_line_writer.h"
#include "posix_file_reader.h"
#include "posix_file_writer.h"

using namespace std;
namespace fs = boost::filesystem;

vector<string> PosixFileSystem::list_dir_file(const string &dir)
{
    vector<string> file_list;
    for(auto& p: fs::directory_iterator(dir)) {
        file_list.push_back(p.path().string());
    }
    return file_list;
}

shared_ptr<IFileReader> PosixFileSystem::create_file_reader()
{
    return make_shared<PosixFileReader>();
}

shared_ptr<IFileWriter> PosixFileSystem::create_file_writer()
{
    return make_shared<PosixFileWriter>();
}

shared_ptr<ILineReader> PosixFileSystem::create_line_reader()
{
    auto file_reader = create_file_reader();
    const int buf_size = LINE_BUF_SIZE;
    return make_shared<FileLineReader>(file_reader, buf_size);
}

shared_ptr<ILineWriter> PosixFileSystem::create_line_writer()
{
    auto file_writer = create_file_writer();
    const int buf_size = LINE_BUF_SIZE;
    return make_shared<FileLineWriter>(file_writer, buf_size);
}
