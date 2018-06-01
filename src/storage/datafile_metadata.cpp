#include "datafile_metadata.h"
#include "metadata.pb.h"
#include "error.h"

using namespace sensetime::spring::dataset;

const char* DatafileMetadata::METADATA_KEY = "_key";
const char* DatafileMetadata::METADATA_REFTYPE = "_reftype";

// Convert timestamp from time_point to Timestamp
static metadata::Timestamp createTimestamp(std::chrono::system_clock::time_point tp) {
    using namespace std::chrono;
    metadata::Timestamp time_stamp;
    long long nanos = duration_cast<nanoseconds>(tp.time_since_epoch()).count();

    time_stamp.set_seconds(nanos / 1000000000);
    time_stamp.set_nanos(nanos % 1000000000);
    return time_stamp;
}

static std::chrono::system_clock::time_point createTimepoint(const metadata::Timestamp &ts) {
    using namespace std::chrono;
    auto nanos = duration_cast<microseconds>(seconds(ts.seconds())) +
        duration_cast<microseconds>(nanoseconds(ts.nanos()));
    return system_clock::time_point(nanos);
}

void DatafileMetadata::init(const char *data, size_t len) {
    size = 0;
    if (!data || len == 0) {
        err_msg("data is null or len is 0");
        return;
    }

    metadata::MetaData md;
    if (!md.ParseFromArray(data, len)) {
        err_quit("invalid metadata");
    }
    size = md.size();
    creation_time = createTimepoint(md.creation_time());
    etag = md.etag();
    content_type = md.content_type();
    for (auto e: md.attrs()) {
        attrs[e.first] = e.second;
    }
}

std::string DatafileMetadata::toString() const { 
    metadata::MetaData md;
    md.set_size(size);
    *md.mutable_creation_time() = createTimestamp(creation_time);
    md.set_etag(etag);
    md.set_content_type(content_type);
    auto t = md.mutable_attrs();
    for (auto e: attrs) {
        (*t)[e.first] = e.second;
    }
    std::string out;
    if (!md.SerializeToString(&out)) {
        err_quit("failed to serialize metadata");
    }
    return std::move(out);
}

