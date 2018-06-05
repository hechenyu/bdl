#include "datafile_metadata.h"
#include "metadata.pb.h"
#include "error.h"

using namespace std;
using namespace std::chrono;
using namespace sensetime::spring::dataset;

const char* DatafileMetadata::METADATA_KEY = "_key";
const char* DatafileMetadata::METADATA_REFTYPE = "_reftype";

namespace {

// Convert timestamp from time_point to Timestamp
metadata::Timestamp createTimestamp(system_clock::time_point tp) {
    metadata::Timestamp time_stamp;
    long long nanos = duration_cast<nanoseconds>(tp.time_since_epoch()).count();

    time_stamp.set_seconds(nanos / 1000000000);
    time_stamp.set_nanos(nanos % 1000000000);
    return time_stamp;
}

system_clock::time_point createTimepoint(const metadata::Timestamp &ts) {
    auto nanos = duration_cast<microseconds>(seconds(ts.seconds())) +
        duration_cast<microseconds>(nanoseconds(ts.nanos()));
    return system_clock::time_point(nanos);
}

std::string calculate_message_digest(const uint8_t *file_data, int file_size)
{
    // TODO: calculate md5
    err_msg("%s, unimplemented", __func__);
    return "fake md";
}

}   // namespace

DatafileMetadata::DatafileMetadata(const std::string &file_name, const std::string &file_type,
        const uint8_t *file_data, int file_size, const AttrMap &attrs):
    size_(file_size), content_type_(file_type), attrs_(attrs), file_name_(file_name)
{
    creation_time_ = system_clock::now();
    etag_ = calculate_message_digest(file_data, file_size);
}

DatafileMetadata::DatafileMetadata(const char *serialized_data, size_t len) 
{
    deserialize(serialized_data, len);
}

DatafileMetadata::DatafileMetadata(const string &serialized_data) 
{
    if (!serialized_data.empty())
        deserialize(serialized_data.data(), serialized_data.size());
}

void DatafileMetadata::deserialize(const char *data, size_t len) 
{
    if (!data || len == 0) {
        err_msg("data is null or len is 0");
        return;
    }

    metadata::MetaData md;
    if (!md.ParseFromArray(data, len)) {
        err_quit("invalid metadata");
    }

    size_ = md.size();
    creation_time_ = createTimepoint(md.creation_time());
    etag_ = md.etag();
    content_type_ = md.content_type();
    for (auto e: md.attrs()) {
        attrs_[e.first] = e.second;
    }
    file_name_ = md.file_name();
}

string DatafileMetadata::serialize() const { 
    metadata::MetaData md;

    md.set_size(size_);
    *md.mutable_creation_time() = createTimestamp(creation_time_);
    md.set_etag(etag_);
    md.set_content_type(content_type_);
    auto t = md.mutable_attrs();
    for (auto e: attrs_) {
        (*t)[e.first] = e.second;
    }
    md.set_file_name(file_name_);

    string out;
    if (!md.SerializeToString(&out)) {
        err_quit("failed to serialize metadata");
    }

    return std::move(out);
}

int32_t DatafileMetadata::file_size() const
{
    return size_;
}

const string &DatafileMetadata::etag() const
{
    return etag_;
}

const string &DatafileMetadata::content_type() const
{
    return content_type_;
}

system_clock::time_point DatafileMetadata::creation_time() const
{
    return creation_time_;
}

const map<string, string> &DatafileMetadata::attrs() const
{
    return attrs_;
}

const std::string &DatafileMetadata::file_name() const
{
    return file_name_;
}
