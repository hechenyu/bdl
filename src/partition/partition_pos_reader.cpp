#include "error.h"
#include "datafile_index.h"
#include "partition_pos_reader.h"

using namespace std;

PartitionPosReader::PartitionPosReader(const string &partition_path, shared_ptr<IFileReader> reader): reader_(reader)
{
    reader_->open(partition_path.c_str());
}

PartitionPosReader::~PartitionPosReader()
{
    reader_->close();
}

DatafileView PartitionPosReader::read(DatafileIndex index)
{
    file_cache_.clear();
    file_cache_.resize(index.file_size);

    reader_->seek(index.offset, SEEK_SET);
    int n = reader_->readn(file_cache_.data(), file_cache_.size());
    if (n != static_cast<int>(file_cache_.size()))
        err_quit("PartitionPosReader::read error: invalid index offset = %d, len = %d",
                (int) index.offset, (int) index.file_size);

    return DatafileView(file_cache_.data(), file_cache_.size());
}

