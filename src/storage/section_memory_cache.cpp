#include <cassert>
#include <cstring>
#include "error.h"
#include "section_memory_cache.h"
#include "datafile_serializer.h"

SectionMemoryCache::SectionMemoryCache(int buffer_size): buffer_(buffer_size)
{
    assert(buffer_size >= sizeof (SectionHeader));

    header_ = reinterpret_cast<SectionHeader *>(buffer_.data());
    available_size_ = buffer_.size() - sizeof (SectionHeader);

    init_header();
}

SectionMemoryCache::SectionMemoryCache(IFileReader &reader, int buffer_size): buffer_(buffer_size)
{
    uint8_t *ptr = buffer_.data();
    int nleft = buffer_.size();
    int nread = 0;
    while (nleft > 0) {
        if ( (nread = reader.read(ptr, nleft)) == 0) {
            break;              /* EOF */
        }

        nleft -= nread;
        ptr   += nread;
    }

    if (ptr - buffer_.data() < sizeof (SectionHeader))
        err_quit("incomplete section header");

    header_ = reinterpret_cast<SectionHeader *>(buffer_.data());
    available_size_ = nleft;
}

void SectionMemoryCache::flush(IFileWriter &writer)
{
    header_->section_size = buffer_.size() - available_size_;

    // TODO: calculate CRC32
    header_->CRC = 0x2345;

    writer.write(buffer_.data(), header_->section_size);
}

bool SectionMemoryCache::append_file(const uint8_t *file_data, int file_size)
{
    if (file_size > SectionConfig::kMaxFileSize) {
        err_quit("append file fail, file is too large: %d bytes", file_size);
    }

    if (file_size > available_size()) {
        err_msg("append file fail, no enough space, file size: %d bytes, available size: %d bytes", 
                file_size, available_size());
        return false;
    }

    memcpy(append_ptr(), file_data, file_size);
    available_size_ -= file_size;
    return true;
}

std::vector<DatafileView> SectionMemoryCache::get_file_list() const
{
    uint8_t *data = header_->files;
    uint8_t *data_end = header_->files + (buffer_.size() - available_size_ - sizeof (SectionHeader));

    std::vector<DatafileView> files;
    while (data < data_end) {
        DatafileView file(data, data_end - data);
        files.push_back(file);
        data += file.total_size();
    }

    return std::move(files);
}

uint32_t SectionMemoryCache::magic() const
{
    return header_->magic;
}

uint32_t SectionMemoryCache::CRC() const
{
    return header_->CRC;
}

uint32_t SectionMemoryCache::version() const
{
    return header_->version;
}

uint64_t SectionMemoryCache::timestamp() const
{
    return header_->timestamp;
}

const uint8_t *SectionMemoryCache::files_begin() const
{
    return header_->files;
}

uint8_t *SectionMemoryCache::append_ptr()
{
    return buffer_.data()+(buffer_.size()-available_size_);
}

void SectionMemoryCache::init_header()
{
    // TODO initialize header, magic, version, timestamp etc...
    header_->magic = SectionConfig::kSectionMagic; 
    header_->version = SectionConfig::kSectionVersion;
}
