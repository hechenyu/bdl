#include "posix_file_writer.h"
#include "file_line_writer.h"
#include "index_item.h"
#include "indexfile_writer.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

IndexItem create_index_item(const std::string &key, uint32_t offset, uint32_t file_size)
{
    IndexItem item;
    item.key = key;
    item.offset = offset;
    item.file_size = file_size;

    return std::move(item);
}

int main(int argc, char *argv[])
{
    string filename = "test.index";
    int nfile = 1000;
    int buf_size = 1024;

    auto line_writer = make_shared<FileLineWriter>(make_shared<PosixFileWriter>(), buf_size);
    IndexfileWriter writer(filename, line_writer);

    string file_prefix = "file";
    uint32_t file_size = 2048;
    uint32_t offset = 0;

    for (int i = 0; i < nfile; i++) {
        auto item = create_index_item(file_prefix+to_string(i), offset, file_size);
        writer.write(item);   
        offset += file_size;
    }
    
    return 0;
}
