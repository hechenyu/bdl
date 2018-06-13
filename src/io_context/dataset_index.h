#ifndef __dataset_index_h
#define __dataset_index_h

#include <string>
#include "dataset_config.h"

class IOContext;

class DatasetIndex {
private:
    IOContext *io_context_;
    std::string dataset_name_;
    std::string index_name_;

public:
    DatasetIndex(IOContext *io_context, std::string dataset_index_name, std::string open_flag);
};

#endif
