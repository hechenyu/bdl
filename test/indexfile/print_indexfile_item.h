#ifndef __print_index_h
#define __print_index_h

#include <iostream>
#include "indexfile_item.h"

std::ostream &operator <<(std::ostream &out, const IndexItem &item)
{
    out << '\"' << item.key << '\"' << ", " 
        << item.offset << ", "
        << item.file_size;
    return out;
}

#endif
