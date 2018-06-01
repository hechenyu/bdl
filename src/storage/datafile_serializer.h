#ifndef __datafile_serializer_h
#define __datafile_serializer_h

#include <cstdint>
#include <vector>

class DatafileMetadata;

// serialize datafile and append to output
class DatafileSerializer {
public:
    void append(std::vector<uint8_t> &output, const char *blob, int blob_len, const DatafileMetadata &metadata);
};

#endif
