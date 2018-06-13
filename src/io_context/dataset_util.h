#ifndef __dataset_util_h
#define __dataset_util_h

#include <string>
#include <tuple>

class DatasetUtil {
public:
    static std::string gen_partition_path(const std::string &root_name,
            const std::string &dataset_name, int part_id);

    static std::string gen_indexfile_path(const std::string &root_name,
            const std::string &dataset_name, int part_id);

    static std::string gen_indexfile_path(const std::string &root_name,
            const std::string &dataset_name, 
            const std::string &index_name, int part_id);

    static std::string part_id_to_string(int part_id);

    static std::tuple<std::string, std::string> parse_dataset_index_name(const std::string &dataset_index_name);
};

#endif
