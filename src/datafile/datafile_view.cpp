#include <cassert>
#include "error.h"
#include "datafile_view.h"
#include "datafile_config.h"

using namespace std;

DatafileView::DatafileView(const uint8_t *data, int size)
{
    if (size < sizeof (DatafileHeader))
        err_quit("incomplete datafile header");

    header_ = reinterpret_cast<const DatafileHeader *>(data);
    if (size < header_->total_size)
        err_quit("incomplete datafile data");

    assert(header_->total_size % DatafileConfig::kAlignSize == 0);
}

uint32_t DatafileView::CRC() const
{
    return header_->CRC;
}

uint32_t DatafileView::total_size() const
{
    return header_->total_size;
}

uint32_t DatafileView::blob_size() const
{
    return header_->blob_size;
}

uint16_t DatafileView::metadata_size() const
{
    return header_->metadata_size;
}

tuple<uint8_t, uint8_t> DatafileView::flags() const
{
    const uint8_t *flags = header_->flags;
    return make_tuple(flags[0], flags[1]);
}

const uint8_t *DatafileView::blob_data() const
{
    return header_->blob;
}

DatafileMetadata DatafileView::metadata() const
{
    const char *metadata_data = reinterpret_cast<const char *>(header_->blob) + header_->blob_size;
    return DatafileMetadata(metadata_data, header_->metadata_size);
}
