#include "io_context.h"

using namespace std;

IOContext::IOContext(string root, shared_ptr<IFileSystem> file_system):
    root_(root), file_system_(file_system)
{
}

const string &IOContext::root() const
{
    return root_;
}

shared_ptr<IFileSystem> IOContext::file_system()
{
    return file_system_;
}
