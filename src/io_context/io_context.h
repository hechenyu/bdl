#ifndef __io_context_h
#define __io_context_h

#include <string>
#include <memory>
#include "i_file_system.h"

class IOContext {
private:
    std::string root_name_;
    std::shared_ptr<IFileSystem> file_system_;

public:
    IOContext(std::string root_name, std::shared_ptr<IFileSystem> file_system);

    const std::string &root_name() const;
    std::shared_ptr<IFileSystem> file_system();
};

#endif
