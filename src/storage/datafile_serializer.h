#ifndef __datafile_serializer_h
#define __datafile_serializer_h

#include <cstdint>
#include <vector>
#include <tuple>

class DatafileMetadata;

// serialize datafile and append to output
class DatafileSerializer {
public:
    typedef std::tuple<char *, int> buffer_type;
    typedef std::tuple<const char *, int> const_buffer_type;

    int serializer(buffer_type output, const_buffer_type blob, const_buffer_type metadata);
    std::vector<uint8_t> serializer(const char *blob, int blob_len, const DatafileMetadata &metadata);
};

#endif
