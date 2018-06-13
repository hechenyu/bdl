#ifndef __print_dataset_index_item_h
#define __print_dataset_index_item_h

#include <iostream>
#include "dataset_index_item.h"

std::ostream &operator <<(std::ostream &out, const DatasetIndexItem &item)
{
    out << '\"' << item.file_path() << '\"' << ", " 
        << item.partition_path() << ", "
        << item.offset() << ", "
        << item.file_size();
    return out;
}

#endif
