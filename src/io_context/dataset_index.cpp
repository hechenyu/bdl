#include "dataset_util.h"
#include "dataset_index.h"

using namespace std;

DatasetIndex::DatasetIndex(IOContext *io_context, string dataset_index_name, string open_flag): io_context_(io_context)
{
    std::tie(dataset_name_, index_name_) = DatasetUtil::parse_dataset_index_name(dataset_index_name);
}

