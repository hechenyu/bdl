#ifndef __dataset_index_item_h
#define __dataset_index_item_h

#include <memory>
#include "indexfile_item.h"

struct DatasetIndexItem {
    std::shared_ptr<IndexfileItem> file_item_;
    std::shared_ptr<std::string> partition_path_;

    DatasetIndexItem() = default;
    DatasetIndexItem(const std::string &serialized_data);

    std::string file_path() const;

    uint32_t offset() const;

    uint32_t file_size() const;

    std::string partition_path() const;

    std::string to_string() const;
};

#endif
