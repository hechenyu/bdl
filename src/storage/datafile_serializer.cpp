#include "error.h"
#include "datafile_serializer.h"
#include "datafile_header.h"
#include "datafile_metadata.h"
#include <cstring>

using namespace std;

void DatafileSerializer::serializer(buffer_type output, const_buffer_type blob, const_buffer_type metadata)
{
    char *output_buffer; int output_capacity;
    std::tie(output_buffer, output_capacity) = output;

    const char *blob_data; int blob_len;
    std::tie(blob_data, blob_len) = blob;

    const char *metadata_data; int metadata_len;
    std::tie(metadata_data, metadata_len) = metadata;

    uint32_t total_size = sizeof(DatafileHeader) + blob_len + metadata_len;
    if (total_size > output_capacity)
        err_quit("serialize datafile output buffer overflow");

    DatafileHeader *file_header = reinterpret_cast<DatafileHeader *>(output_buffer);
    memcpy(file_header->blob, blob_data, blob_len);
    memcpy(file_header->blob + blob_len, metadata_data, metadata_len);
}

vector<uint8_t> DatafileSerializer::serializer(const char *blob, int blob_len, 
        const DatafileMetadata &metadata)
{
    vector<uint8_t> output;
    string serialize_meta = metadata.toString();

    int total_size = sizeof(DatafileHeader) + blob_len + serialize_meta.length();
    output.resize(total_size);

    serializer(buffer_type(reinterpret_cast<char *>(output.data()), output.size()),
            const_buffer_type(blob, blob_len),
            const_buffer_type(serialize_meta.data(), serialize_meta.length()));
    return std::move(output);
}

