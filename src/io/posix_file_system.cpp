#include <boost/filesystem.hpp>
#include "posix_file_system.h"
#include "file_line_reader.h"
#include "file_line_writer.h"
#include "posix_file_reader.h"
#include "posix_file_writer.h"

using namespace std;
namespace fs = boost::filesystem;

void PosixFileSystem::make_dir(const std::string &path)
{
    fs::create_directories(path);
}

vector<string> PosixFileSystem::list_dir_file(const string &dir)
{
    vector<string> file_list;
    for(auto& p: fs::directory_iterator(dir)) {
        file_list.push_back(p.path().filename().string());
    }
    return file_list;
}

vector<std::string> PosixFileSystem::list_dir_file(const string &dir, function<bool (const string &)> filter)
{
    vector<string> file_list;
    for(auto& p: fs::directory_iterator(dir)) {
        auto filename = p.path().filename().string();
        if (filter(filename))
            file_list.push_back(filename);
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

shared_ptr<IFileSystem> create_posix_file_system()
{
    return make_shared<PosixFileSystem>();
}
