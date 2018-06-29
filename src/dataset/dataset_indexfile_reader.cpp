#include "dataset_indexfile_reader.h"

using namespace std;

DatasetIndexfileReader::DatasetIndexfileReader(shared_ptr<IFileSystem> file_system, 
        const string &indexfile_path, const string &partition_path): file_system_(file_system)
{
    indexfile_path_ = make_shared<string>(indexfile_path);
    partition_path_ = make_shared<string>(partition_path);
}

DatasetIndexItem *DatasetIndexfileReader::get_new_index_item()
{
    if (index_item_cached_queue_.size() > kMaxIndexItemCached) {
        index_item_cached_queue_.pop_front();
    } 
    index_item_cached_queue_.push_back(DatasetIndexItem());
    return &index_item_cached_queue_.back();
}
