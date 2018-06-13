#include <algorithm>
#include <iterator>
#include <boost/algorithm/string.hpp>
#include "error.h"
#include "dataset_config.h"
#include "dataset_util.h"
#include "dataset_index.h"

using namespace std;
using namespace boost::algorithm;

DatasetIndex::DatasetIndex(shared_ptr<IOContext> io_context, string dataset_index_name, string open_flag): io_context_(io_context)
{
    open_flag_ = get_and_check_open_flag(open_flag);

    std::tie(dataset_name_, index_name_) = DatasetUtil::parse_dataset_index_name(dataset_index_name);

    load_partition_name_list();

    if (open_flag_ == OpenFlag::kAppend) {
        init_for_append();
    } else if (open_flag_ == OpenFlag::kRead) {
        init_for_read();
    } else {
        err_dump("impossibly run here!");
    }
}

shared_ptr<DatasetIndex::FileAppendHandle> DatasetIndex::appendFile(string file_name, string file_type)
{
    if (open_flag_ != OpenFlag::kAppend)
        err_quit("DatasetIndex::appendFile error: invalid open mode");

    return make_shared<FileAppendHandle>(dataset_writer_, file_name, file_type);
}

void DatasetIndex::load_partition_name_list()
{
    partition_name_list_.clear();

    auto file_system = io_context_->file_system();
    auto root_name = io_context_->root_name();
    auto dataset_path = DatasetUtil::gen_dataset_path(root_name, dataset_name_);
    file_system->make_dir(dataset_path);
    auto file_name_list = file_system->list_dir_file(dataset_path);

    copy_if(file_name_list.begin(), file_name_list.end(), back_inserter(partition_name_list_),
            [](const string &str) { return ends_with(str, DatasetConfig::kPartFileSuffix); }); 
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
}

void DatasetIndex::init_for_read()
{
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
    dataset_writer_(dataset_writer), file_name_(file_name), file_type_(file_type)
{
}

void DatasetIndex::FileAppendHandle::writeAll(const std::string &file_data)
{
    if (!dataset_writer_)
        err_quit("invalid DatasetIndex::FileAppendHandle");

    dataset_writer_->write(file_name_, file_type_, file_data);
    dataset_writer_.reset();
}
