#include <algorithm>
#include <iterator>
#include <boost/algorithm/string.hpp>
#include "error.h"
#include "datafile_index.h"
#include "datafile_view.h"
#include "partition_pos_reader.h"
#include "io_context.h"
#include "dataset_config.h"
#include "dataset_util.h"
#include "dataset_index.h"
#include "dataset_writer.h"
#include "dataset_reader.h"
#include "dataset_indexfile_writer.h"

#ifndef NDEBUG
#include <iostream>
#endif

using namespace std;
using namespace boost::algorithm;

DatasetIndex::DatasetIndex(shared_ptr<IOContext> io_context, string dataset_index_name, string open_flag): io_context_(io_context)
{
    open_flag_ = get_and_check_open_flag(open_flag);

    std::tie(dataset_name_, index_branch_) = DatasetUtil::parse_dataset_index_name(dataset_index_name);

    load_partition_name_list();

    if (open_flag_ == OpenFlag::kAppend) {
        init_for_append();
    } else if (open_flag_ == OpenFlag::kRead) {
        init_for_read();
    } else {
        err_dump("impossibly run here!");
    }
}

DatasetIndex::FileAppendHandle DatasetIndex::appendFile(string file_name, string file_type)
{
    if (open_flag_ != OpenFlag::kAppend)
        err_quit("DatasetIndex::appendFile error: invalid open mode");

    return FileAppendHandle(dataset_writer_, file_name, file_type);
}

DatasetIndex::FileReadHandle DatasetIndex::openFile(DatasetIndexItem index_item)
{
    if (open_flag_ != OpenFlag::kRead)
        err_quit("DatasetIndex::openFile error: invalid open mode");

    auto partition_reader = dataset_reader_->get_partition_reader(index_item.partition_path());
    return FileReadHandle(partition_reader, index_item);
}

vector<DatasetIndexfileReader> DatasetIndex::getIndexFiles()
{
    return dataset_indexfile_readers_;
}

void DatasetIndex::fill_indexfile_readers()
{
    dataset_indexfile_readers_.clear();

    auto file_system = io_context_->file_system();
    auto root_name = io_context_->root_name();

    for (const auto &indexfile_name: indexfile_name_list_) {
        auto indexfile_path = DatasetUtil::gen_indexfile_path(root_name, dataset_name_, indexfile_name, index_branch_);
        auto partition_path = DatasetUtil::gen_partition_path(root_name, dataset_name_, indexfile_name);
        dataset_indexfile_readers_.push_back(
                DatasetIndexfileReader(file_system, indexfile_path, partition_path));
    }
}

void DatasetIndex::load_indexfile_name_list()
{
    indexfile_name_list_.clear();

    auto file_system = io_context_->file_system();
    auto root_name = io_context_->root_name();
    auto dataset_path = DatasetUtil::gen_dataset_path(root_name, dataset_name_);

    file_system->make_dir(dataset_path);
    string suffix = DatasetUtil::gen_indexfile_suffix(index_branch_);
    auto file_name_list = file_system->list_dir_file(dataset_path, 
            [&suffix](const string &str) { return ends_with(str, suffix); }
            );

    transform(file_name_list.begin(), file_name_list.end(), back_inserter(indexfile_name_list_),
            [&suffix](const string &str) { return str.substr(0, str.size() - suffix.size()); }
            ); 

    sort(indexfile_name_list_.begin(), indexfile_name_list_.end());

#ifndef NDEBUG
    copy(indexfile_name_list_.begin(), indexfile_name_list_.end(),
            ostream_iterator<string>(cout, "\n"));
#endif
}

void DatasetIndex::load_partition_name_list()
{
    partition_name_list_.clear();

    auto file_system = io_context_->file_system();
    auto root_name = io_context_->root_name();
    auto dataset_path = DatasetUtil::gen_dataset_path(root_name, dataset_name_);
    file_system->make_dir(dataset_path);
    auto file_name_list = file_system->list_dir_file(dataset_path, 
            [](const string &str) { return ends_with(str, DatasetConfig::kPartFileSuffix); }
            );

    transform(file_name_list.begin(), file_name_list.end(), back_inserter(partition_name_list_),
            [](const string &str) { return str.substr(0, str.size() - DatasetConfig::kPartFileSuffix.size()); }
            ); 

    sort(partition_name_list_.begin(), partition_name_list_.end());

#ifndef NDEBUG
    copy(partition_name_list_.begin(), partition_name_list_.end(),
            ostream_iterator<string>(cout, "\n"));
#endif
}

DatasetIndex::OpenFlag DatasetIndex::get_and_check_open_flag(const std::string &open_flag)
{
    if (open_flag == "r")
        return OpenFlag::kRead;
    else if (open_flag == "a")
        return OpenFlag::kAppend;
    else
        err_quit("invalid open_flag: %s", open_flag.c_str());
}

void DatasetIndex::init_for_append()
{
    auto cur_part_id = get_max_part_id();
    dataset_writer_ = make_shared<DatasetWriter>(io_context_, dataset_name_, cur_part_id);
    dataset_indexfile_writer_ = make_shared<DatasetIndexfileWriter>(io_context_->file_system(), index_branch_); 
}

void DatasetIndex::init_for_read()
{
    dataset_reader_ = make_shared<DatasetReader>(io_context_);
    load_indexfile_name_list();
    fill_indexfile_readers();
}

int DatasetIndex::get_max_part_id() const
{
    int max_part_id = 0;
    const size_t max_part_name_size = DatasetConfig::kPartIdSetW + DatasetConfig::kPartFileSuffix.size();
    for (auto &part_name: partition_name_list_) {
        if (part_name.size() > max_part_name_size)
            continue;

        int part_id = atoi(part_name.c_str());
        if (part_id > max_part_id)
            max_part_id = part_id;
    }

    return max_part_id;
}

// =================================================================================================

DatasetIndex::FileAppendHandle::FileAppendHandle(shared_ptr<DatasetWriter> dataset_writer,
        const string &file_name, const string &file_type):
    dataset_writer_(dataset_writer)
{
    file_name_ = make_shared<string>(file_name);
    file_type_ = make_shared<string>(file_type);
}

void DatasetIndex::FileAppendHandle::writeAll(const std::string &file_data)
{
    if (!dataset_writer_)
        err_quit("invalid DatasetIndex::FileAppendHandle");

    dataset_writer_->write(*file_name_, *file_type_, file_data);
    dataset_writer_.reset();
}

// =================================================================================================

DatasetIndex::FileReadHandle::FileReadHandle(shared_ptr<PartitionPosReader> partition_reader,
        DatasetIndexItem index_item):
    partition_reader_(partition_reader), index_item_(index_item)
{
}

string DatasetIndex::FileReadHandle::readAll()
{
    DatafileIndex index(index_item_.offset(), index_item_.file_size());
    DatafileView file_view = partition_reader_->read(index);
    return string(reinterpret_cast<const char *>(file_view.blob_data()), file_view.blob_size());
}
