#include "dataset_index_item.h"
#include "json11.hpp"
#include "error.h"

using namespace std;
using namespace json11;

namespace {
    const std::string kFilePath = "file_path";
    const std::string kOffset = "offset";
    const std::string kFileSize = "file_size";
    const std::string kPartitionPath = "partition_path";
}   // namespace

DatasetIndexItem::DatasetIndexItem(const string &serialized_data)
{
    std::string err;
    auto json = Json::parse(serialized_data, err);
    if (!err.empty()) {
        err_quit("parse json error: %s, serialized_data: %s", err.c_str(), serialized_data.c_str());
    }

    auto _file_path = json[kFilePath].string_value();
    auto _offset = json[kOffset].int_value();
    auto _file_size = json[kFileSize].int_value();
    auto _partition_path = json[kPartitionPath].string_value();

    file_item_ = make_shared<IndexfileItem>(_file_path, _offset, _file_size);
    partition_path_ = make_shared<string>(_partition_path);    // TODO: can shared with other index item
}

string DatasetIndexItem::file_path() const
{
    if (file_item_)
        return file_item_->key;
    else
        return "";
}

uint32_t DatasetIndexItem::offset() const
{
    if (file_item_)
        return file_item_->offset;
    else
        return 0;
}

uint32_t DatasetIndexItem::file_size() const
{
    if (file_item_)
        return file_item_->file_size;
    else
        return 0;
}

string DatasetIndexItem::partition_path() const
{
    if (partition_path_)
        return *partition_path_;
    else
        return "";
}

string DatasetIndexItem::to_string() const
{
    const Json obj = Json::object({
            {kFilePath, file_path()},
            {kOffset, static_cast<int>(offset())},
            {kFileSize, static_cast<int>(file_size())},
            {kPartitionPath, partition_path()}
            });

    return obj.dump();
}
