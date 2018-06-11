#ifndef __posix_file_system_h
#define __posix_file_system_h

#include "i_file_system.h"

class PosixFileSystem: public IFileSystem {
public:
    static const int LINE_BUF_SIZE;

    std::vector<std::string> list_dir_file(const std::string &dir) override;
    std::shared_ptr<IFileReader> create_file_reader() override;
    std::shared_ptr<IFileWriter> create_file_writer() override;
    std::shared_ptr<ILineReader> create_line_reader(const std::string &path) override;
    std::shared_ptr<ILineWriter> create_line_writer(const std::string &path) override;
};

const int PosixFileSystem::LINE_BUF_SIZE = 1024*1024;

#endif
