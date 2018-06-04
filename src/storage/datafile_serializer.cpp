#include "error.h"
#include "datafile_serializer.h"
#include "datafile_header.h"
#include "datafile_metadata.h"
#include "datafile_config.h"
#include "ceil_to_align_at.h"
#include <cstring>
#include <cassert>

using namespace std;

int DatafileSerializer::calculate_total_size(int blob_size, int metadata_size)
{
    auto total_size = sizeof(DatafileHeader) + blob_size + metadata_size;
    total_size = ceil_to_align_at(total_size, DatafileConfig::kAlignSize);
    return total_size;
}

int DatafileSerializer::serialize(buffer_type output, const_buffer_type blob, const_buffer_type metadata)
{
    // get buffer and size
    char *output_buffer; int output_capacity;
    std::tie(output_buffer, output_capacity) = output;

    const char *blob_data; int blob_size;
    std::tie(blob_data, blob_size) = blob;

    const char *metadata_data; int metadata_size;
    std::tie(metadata_data, metadata_size) = metadata;

    // calculate total size with alginment, and check if overflow
    int total_size = calculate_total_size(blob_size, metadata_size);
    if (total_size > output_capacity)
        err_quit("serialize datafile output buffer overflow");

    // serialize data
    DatafileHeader *file_header = reinterpret_cast<DatafileHeader *>(output_buffer);
    memcpy(file_header->blob, blob_data, blob_size);
    memcpy(file_header->blob + blob_size, metadata_data, metadata_size);

    file_header->CRC = 0xabcd;    // TODO
    file_header->total_size = total_size;
    file_header->blob_size = blob_size;
    file_header->metadata_size = metadata_size;
    file_header->flags[0] = 0x01; file_header->flags[1] = 0x02; // TODO

    return total_size;
}

vector<uint8_t> DatafileSerializer::serialize(const char *blob, int blob_size, 
        const DatafileMetadata &metadata)
{
    assert(blob && blob_size >= 0);

    vector<uint8_t> output;
    string serialize_meta = metadata.toString();

    int total_size = calculate_total_size(blob_size, serialize_meta.size());
    output.resize(total_size);

    auto n = serialize(buffer_type(reinterpret_cast<char *>(output.data()), output.size()),
            const_buffer_type(blob, blob_size),
            const_buffer_type(serialize_meta.data(), serialize_meta.length()));
    assert(n == total_size);

    return std::move(output);
}

