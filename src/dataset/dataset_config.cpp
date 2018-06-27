#include "dataset_config.h"
#include "boost/format.hpp"

using namespace std;

const string DatasetConfig::kPartFileSuffix = ".part";
const string DatasetConfig::kIdxFileSuffix = ".idx";

string DatasetConfig::printable_info()
{
    boost::format fmt(R"({"USE_PARTITION_POS_READER_POOL": %s})");
    std::string use_partition_pos_reader_pool;
#ifdef USE_PARTITION_POS_READER_POOL
    use_partition_pos_reader_pool = "true";
#else
    use_partition_pos_reader_pool = "false";
#endif

    fmt % use_partition_pos_reader_pool;
    return fmt.str();
}
