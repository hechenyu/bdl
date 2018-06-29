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
    struct Configure {
        bool read_buffered = false;
    };

    IOContext(const std::string &root_name, std::shared_ptr<IFileSystem> file_system);

    static std::shared_ptr<IOContext> create_io_context(std::string root_name);
    static std::shared_ptr<IOContext> create_io_context(std::string root_name, const Configure &conf);

    const std::string &root_name() const;
    std::shared_ptr<IFileSystem> file_system();
};

#endif
