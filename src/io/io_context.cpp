#include "io_context.h"
#include "posix_file_system.h"
#include "posix_file_system_rbuf.h"

using namespace std;

IOContext::IOContext(const string &root_name, shared_ptr<IFileSystem> file_system):
    root_name_(root_name), file_system_(file_system)
{
}

shared_ptr<IOContext> IOContext::create_io_context(string root_name)
{
    return std::make_shared<IOContext>(root_name, make_shared<PosixFileSystem>());
}

shared_ptr<IOContext> IOContext::create_io_context(string root_name, const Configure &conf)
{
    if (conf.read_buffered) { 
        return std::make_shared<IOContext>(root_name, make_shared<PosixFileSystemRbuf>());
    } else {
        return std::make_shared<IOContext>(root_name, make_shared<PosixFileSystem>());
    }
}

const string &IOContext::root_name() const
{
    return root_name_;
}

shared_ptr<IFileSystem> IOContext::file_system()
{
    return file_system_;
}
