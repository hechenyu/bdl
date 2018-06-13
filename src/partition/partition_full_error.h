#ifndef __partition_full_error_h
#define __partition_full_error_h

#include <stdexcept>

class PartitionFullError: public std::runtime_error {
public:
    PartitionFullError();
};

#endif
