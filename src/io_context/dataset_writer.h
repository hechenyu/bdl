#ifndef __dataset_writer_h
#define __dataset_writer_h

#include <string>
#include <tuple>
#include <memory>
#include "dataset_config.h"
#include "partition_writer.h"
#include "indexfile_writer.h"

class IOContext;

class DatasetWriter {
private:
    std::shared_ptr<IOContext> io_context_;
    std::string dataset_name_;
    int cur_part_id_ = 0;
    int min_part_id_ = DatasetConfig::kMinPartId;
    int max_part_id_ = DatasetConfig::kMaxPartId;
    std::shared_ptr<PartitionWriter> partition_writer_;
    std::shared_ptr<IndexfileWriter> indexfile_writer_;

public:
    DatasetWriter(std::shared_ptr<IOContext> io_context, const std::string &dataset_name, int cur_part_id);
    DatasetWriter(std::shared_ptr<IOContext> io_context, const std::string &dataset_name, int cur_part_id, int min_part_id, int max_part_id);

    void write(const std::string &file_name, const std::string &file_type, const std::string &file_data);

private:
    void write_aux(const std::string &file_name, const std::string &file_type, const std::string &file_data);
    void process_current_partition_full();
    void check_current_part_id_valid();
    void reset_writers();
};

#endif

