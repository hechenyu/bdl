#include "posix_file_system_rbuf.h"
#include "stdc_file_reader.h"

using namespace std;

shared_ptr<IFileReader> PosixFileSystemRbuf::create_file_reader()
{
    return make_shared<StdcFileReader>();
}

