#ifndef __dataset_index_item_h
#define __dataset_index_item_h

#include <memory>
#include "indexfile_item.h"

struct DatasetIndexItem {
    std::shared_ptr<IndexfileItem> file_item_;
    std::shared_ptr<std::string> partition_path_;
};

#endif
