#include "dataset_file_read_handle.h"
#include "datafile_index.h"
#include "datafile_view.h"
#include "partition_pos_reader.h"

using namespace std;

DatasetFileReadHandle::DatasetFileReadHandle(shared_ptr<PartitionPosReader> partition_reader,
        DatasetIndexItem index_item):
    partition_reader_(partition_reader), index_item_(index_item)
{
}

vector<uint8_t> DatasetFileReadHandle::readAll()
{
    DatafileIndex index(index_item_.offset(), index_item_.file_size());
    DatafileView file_view = partition_reader_->read(index);
    return vector<uint8_t>(file_view.blob_data(), file_view.blob_data()+file_view.blob_size());
}

map<string, string> DatasetFileReadHandle::getAttrs()
{
    DatafileIndex index(index_item_.offset(), index_item_.file_size());
    DatafileView file_view = partition_reader_->read(index);
    return file_view.metadata().attrs();
}
