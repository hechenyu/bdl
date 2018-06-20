#ifndef __dataset_indexfile_reader_h
#define __dataset_indexfile_reader_h

#include <memory>
#include <string>
#include <iterator>
#include "i_file_system.h"
#include "indexfile_reader.h"
#include "dataset_index_item.h"

class DatasetIndexfileReader {
private:
    std::shared_ptr<IFileSystem> file_system_;
    std::shared_ptr<std::string> indexfile_path_;
    std::shared_ptr<std::string> partition_path_;
    mutable std::vector<DatasetIndexItem> index_item_list_; 
    mutable bool is_loaded_ = false;

    friend class iterator;

public:
    DatasetIndexfileReader(std::shared_ptr<IFileSystem> file_system, 
            const std::string &indexfile_path, const std::string &partition_path);

public:
    typedef std::vector<DatasetIndexItem>::const_iterator iterator;

    iterator begin() const
    {
        if (!is_loaded_) {
            load_indexfile();
            is_loaded_ = true;
        }
        return index_item_list_.begin();
    }

    iterator end() const
    {
        if (!is_loaded_) {
            load_indexfile();
            is_loaded_ = true;
        }
        return index_item_list_.end();
    }

private:
    void load_indexfile() const;
};

#endif
