#include "dataset_indexfile_reader.h"

using namespace std;

DatasetIndexfileReader::DatasetIndexfileReader(shared_ptr<IFileSystem> file_system, 
        const string &indexfile_path, const string &partition_path): file_system_(file_system)
{
    indexfile_path_ = make_shared<string>(indexfile_path);
    partition_path_ = make_shared<string>(partition_path);
}

void DatasetIndexfileReader::load_indexfile() const
{
    index_item_list_.clear();

    IndexfileReader indexfile_reader(*indexfile_path_, file_system_->create_line_reader());
    DatasetIndexItem index_item;
    while (indexfile_reader.has_next()) {
        index_item.file_item_ = indexfile_reader.next();
        index_item.partition_path_ = this->partition_path_;
        index_item_list_.push_back(index_item);
    }
}

