#ifndef __print_indexfile_item_h
#define __print_indexfile_item_h

#include <iostream>
#include "indexfile_item.h"

std::ostream &operator <<(std::ostream &out, const IndexfileItem &item)
{
    out << '\"' << item.key << '\"' << ", " 
        << item.offset << ", "
        << item.file_size;
    return out;
}

#endif
