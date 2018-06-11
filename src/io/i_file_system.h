#ifndef __i_file_system_h
#define __i_file_system_h

#include <string>
#include <vector>
#include <memory>

#include "i_file_reader.h"
#include "i_file_writer.h"
#include "i_line_reader.h"
#include "i_line_writer.h"

class IFileSystem {
public:
    virtual ~IFileSystem();

    virtual std::vector<std::string> list_dir_file(const std::string &dir) = 0;
    virtual std::shared_ptr<IFileReader> create_file_reader() = 0;
    virtual std::shared_ptr<IFileWriter> create_file_writer() = 0;
    virtual std::shared_ptr<ILineReader> create_line_reader(const std::string &path) = 0;
    virtual std::shared_ptr<ILineWriter> create_line_writer(const std::string &path) = 0;
};

#endif
