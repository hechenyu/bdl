#ifndef __datafile_serializer_h
#define __datafile_serializer_h

#include <cstdint>
#include <vector>
#include <tuple>

class DatafileMetadata;

// serialize datafile and append to output
class DatafileSerializer {
private:
    typedef std::tuple<uint8_t *, int> buffer_type;
    typedef std::tuple<const uint8_t *, int> const_buffer_type;

    int calculate_total_size(int blob_size, int metadata_size);
    int serialize(buffer_type output, const_buffer_type blob, const_buffer_type metadata);

public:
    std::vector<uint8_t> serialize(const uint8_t *blob, int blob_len, const DatafileMetadata &metadata);
};

#endif
