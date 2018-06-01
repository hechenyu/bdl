#include "datafile_serializer.h"
#include "datafile_header.h"
#include "datafile_metadata.h"

using namespace std;

void DatafileSerializer::append(vector<uint8_t> &output, const char *blob, int blob_len, const DatafileMetadata &metadata)
{
    string serialize_meta = metadata.toString();
    uint32_t total_size = sizeof(DatafileHeader) + blob_len + serialize_meta.length();
}

