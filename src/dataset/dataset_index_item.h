#ifndef __dataset_index_item_h
#define __dataset_index_item_h

#include <memory>
#include "indexfile_item.h"

struct DatasetIndexItem {
    std::shared_ptr<IndexfileItem> file_item_;
    std::shared_ptr<std::string> partition_path_;

    std::string file_path() const
    {
        if (file_item_)
            return file_item_->key;
        else
            return "";
    }

    uint32_t offset() const
    {
        if (file_item_)
            return file_item_->offset;
        else
            return 0;
    }

    uint32_t file_size() const
    {
        if (file_item_)
            return file_item_->file_size;
        else
            return 0;
    }

    std::string partition_path() const
    {
        if (partition_path_)
            return *partition_path_;
        else
            return "";
    }
};

#endif
