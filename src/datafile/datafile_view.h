#ifndef __datafile_view_h
#define __datafile_view_h

#include <tuple>
#include "datafile_header.h"
#include "datafile_metadata.h"

class DatafileView {
private:
    const DatafileHeader *header_ = nullptr;

public:
    DatafileView(const uint8_t *data, int size);

    // file header
    uint32_t CRC() const;
    uint32_t total_size() const;
    uint32_t blob_size() const;
    uint16_t metadata_size() const;
    std::tuple<uint8_t, uint8_t> flags() const;

    // file data
    const uint8_t *blob_data() const;

    // metadata
    DatafileMetadata metadata() const;
};

#endif
