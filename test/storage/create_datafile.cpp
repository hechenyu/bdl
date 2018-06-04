#include <chrono>
#include "create_datafile.h"
#include "datafile_metadata.h"
#include "datafile_serializer.h"

using namespace std;
using namespace std::chrono;

vector<uint8_t> create_datafile(
        const string &etag, const string &content_type,
        const map<string, string> attrs,
        const string &blob)
{
    DatafileMetadata meta;

    meta.etag = etag;
    meta.content_type = content_type;
    meta.creation_time = system_clock::now();
    meta.attrs = attrs;

    DatafileSerializer datafile_serializer;
    return datafile_serializer.serialize(blob.data(), blob.size(), meta);
}
