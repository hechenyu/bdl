#include "error.h"
#include "dataset_util.h"
#include "dataset_indexfile_writer.h"

using namespace std;

DatasetIndexfileWriter::DatasetIndexfileWriter(shared_ptr<IFileSystem> file_system, const string &index_branch):
    file_system_(file_system), index_branch_(index_branch)
{
}

void DatasetIndexfileWriter::write(DatasetIndexItem item)
{
    auto partition_path = item.partition_path();
    if (partition_path.empty()) {
        err_msg("DatasetIndexfileWriter::write(), item.partition_path is empty");
        return;
    }

    if (partition_path != cached_partition_path_) {
        auto indexfile_path = DatasetUtil::partition_path_to_indexfile_path(partition_path, index_branch_);
        cached_indexfile_writer_ = make_shared<IndexfileWriter>(indexfile_path, file_system_->create_line_writer());
        cached_partition_path_ = partition_path;
    }

    cached_indexfile_writer_->write(*item.file_item_);
}
