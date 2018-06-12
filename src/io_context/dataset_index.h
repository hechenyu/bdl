#ifndef __dataset_index_h
#define __dataset_index_h

#include <string>
#include <tuple>

class IOContext;

class DatasetIndex {
public:
    enum open_flag_type { kOpenForRead, kOpenForAppend };

private:
    IOContext *io_context_;
    int min_part_id_ = 0;
    int max_part_id_ = 9999;
    int cur_part_id_ = 0;
    std::string dataset_name_;
    std::string index_name_;
    open_flag_type open_flag_; 

public:
    DatasetIndex(IOContext *io_context, std::string path, std::string open_flag);

    DatasetIndex(IOContext *io_context, std::string path, std::string open_flag, int min_part_id, int max_part_id);

private:
    std::tuple<std::string, std::string> parse_path(const std::string &path);
};

#endif
