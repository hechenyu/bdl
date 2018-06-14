#include "io_context.h"

using namespace std;

IOContext::IOContext(string root_name, shared_ptr<IFileSystem> file_system):
    root_name_(root_name), file_system_(file_system)
{
}

const string &IOContext::root_name() const
{
    return root_name_;
}

shared_ptr<IFileSystem> IOContext::file_system()
{
    return file_system_;
}
