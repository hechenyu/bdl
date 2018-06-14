#include "error.h"
#include "io_context.h"
#include "partition_full_error.h"
#include "dataset_writer.h"
#include "dataset_util.h"

using namespace std;

DatasetWriter::DatasetWriter(shared_ptr<IOContext> io_context, const string &dataset_name, int cur_part_id):
    DatasetWriter(io_context, dataset_name, cur_part_id, 0, 9999)
{
}

DatasetWriter::DatasetWriter(shared_ptr<IOContext> io_context, const string &dataset_name, 
        int cur_part_id, int min_part_id, int max_part_id): 
    io_context_(io_context), dataset_name_(dataset_name), 
    cur_part_id_(cur_part_id), min_part_id_(min_part_id), max_part_id_(max_part_id)
{
    check_current_part_id_valid();
    reset_writers();
}

void DatasetWriter::write(const std::string &file_name, const std::string &file_type, const string &file_data)
{
    try {
        write_aux(file_name, file_type, file_data);
    } catch (const PartitionFullError &) {
        process_current_partition_full();
        write_aux(file_name, file_type, file_data);
    }
}

void DatasetWriter::write_aux(const std::string &file_name, const std::string &file_type, const std::string &file_data)
{
    auto index_item = partition_writer_->write(file_name, file_type, (uint8_t *) file_data.data(), file_data.size());
    indexfile_writer_->write(IndexfileItem(file_name, index_item.offset, index_item.file_size));
}

void DatasetWriter::check_current_part_id_valid()
{
    if (cur_part_id_ < min_part_id_)
        err_quit("invalid current part id: underflow");

    if (cur_part_id_ > max_part_id_)
        err_quit("invalid current part id: overflow");
}

void DatasetWriter::process_current_partition_full()
{
    cur_part_id_++;
    check_current_part_id_valid();
    reset_writers();
}

void DatasetWriter::reset_writers()
{
    auto root_name = io_context_->root_name();
    auto file_system = io_context_->file_system();

    auto partition_name = DatasetUtil::part_id_to_string(cur_part_id_);
    auto partition_path = DatasetUtil::gen_partition_path(root_name, dataset_name_, partition_name);
    partition_writer_ = make_shared<PartitionWriter>(partition_path,
                        file_system->create_file_writer(), file_system->create_file_reader());

    auto indexfile_path = DatasetUtil::gen_indexfile_path(root_name, dataset_name_, partition_name);
    indexfile_writer_ = make_shared<IndexfileWriter>(indexfile_path,
                        file_system->create_line_writer());
}
