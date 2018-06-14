#ifndef __dataset_index_h
#define __dataset_index_h

#include <memory>
#include <string>
#include <vector>

#include "dataset_index_item.h"

class IOContext;
class DatasetWriter;
class DatasetReader;

class DatasetIndex {
public:
    enum class OpenFlag { kAppend, kRead };

private:
    std::shared_ptr<IOContext> io_context_;
    std::string dataset_name_;
    std::string index_branch_;
    std::vector<std::string> partition_name_list_;
    std::vector<std::string> indexfile_name_list_;
    OpenFlag open_flag_;
    std::shared_ptr<DatasetWriter> dataset_writer_;
    std::shared_ptr<DatasetReader> dataset_reader_;

public:
    DatasetIndex(std::shared_ptr<IOContext> io_context, std::string dataset_index_name, std::string open_flag);

public:
    class FileAppendHandle {
    private:
        std::shared_ptr<DatasetWriter> dataset_writer_;
        std::shared_ptr<std::string> file_name_; 
        std::shared_ptr<std::string> file_type_;

    public:
        FileAppendHandle(std::shared_ptr<DatasetWriter> dataset_writer, 
                const std::string &file_name, const std::string &file_type);

        void writeAll(const std::string &file_data);
    };

    FileAppendHandle appendFile(std::string file_name, std::string file_type);

    class FileReadHandle {
    private:
        DatasetIndexItem index_item_;

    public:
    };

private:
    void load_partition_name_list();
    void load_indexfile_name_list();
    OpenFlag get_and_check_open_flag(const std::string &open_flag);
    void init_for_append();
    void init_for_read();
    int get_max_part_id() const;
};

#endif
