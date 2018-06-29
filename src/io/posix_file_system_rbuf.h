#ifndef __posix_file_system_rbuf_h
#define __posix_file_system_rbuf_h

#include "posix_file_system.h"

class PosixFileSystemRbuf: public PosixFileSystem {
public:
    std::shared_ptr<IFileReader> create_file_reader() override;
};

#endif
