#ifndef __dataset_indexfile_writer_h
#define __dataset_indexfile_writer_h

#include <memory>
#include <string>

#include "i_file_system.h"
#include "indexfile_writer.h"
#include "dataset_index_item.h"

class DatasetIndexfileWriter {
private:
    std::shared_ptr<IFileSystem> file_system_;
    std::string index_branch_;
    std::string cached_partition_path_;
    std::shared_ptr<IndexfileWriter> cached_indexfile_writer_;

public:
    DatasetIndexfileWriter(std::shared_ptr<IFileSystem> file_system, const std::string &index_branch);

    void write(DatasetIndexItem item);
};

#endif
