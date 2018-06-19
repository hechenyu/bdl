#include "dataset_indexfile_reader.h"

using namespace std;

DatasetIndexfileReader::DatasetIndexfileReader(shared_ptr<IFileSystem> file_system, 
        const string &indexfile_path, const string &partition_path): file_system_(file_system)
{
    indexfile_path_ = make_shared<string>(indexfile_path);
    partition_path_ = make_shared<string>(partition_path);
}

bool DatasetIndexfileReader::get_next_item()
{
    bool ret = indexfile_reader_->has_next();
    if (ret) {
        index_item_.file_item_ = indexfile_reader_->next();
        index_item_.partition_path_ = this->partition_path_;
    }
    return ret;
}
