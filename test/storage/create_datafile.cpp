#include <chrono>
#include "create_datafile.h"
#include "datafile_metadata.h"
#include "datafile_serializer.h"

using namespace std;
using namespace std::chrono;

vector<uint8_t> create_datafile(
        const string &file_name, const string &content_type,
        const map<string, string> attrs,
        const string &blob)
{
    DatafileMetadata meta(file_name, content_type, (const uint8_t *) blob.data(), blob.size(), attrs);
    DatafileSerializer datafile_serializer;
    return datafile_serializer.serialize(blob.data(), blob.size(), meta);
}
