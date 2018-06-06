#include <cassert>
#include <cstring>
#include <algorithm>
#include "error.h"
#include "section_memory_cache.h"
#include "datafile_serializer.h"
#include "calculate_crc32.h"

using namespace std;

SectionMemoryCache::SectionMemoryCache(int buffer_size): buffer_(buffer_size, 0)
{
    assert(buffer_size > 0);
    assert(static_cast<size_t>(buffer_size) >= sizeof (SectionHeader));

    header_ = reinterpret_cast<SectionHeader *>(buffer_.data());
    used_size_ =  sizeof (SectionHeader);

    init_header();
}

void SectionMemoryCache::clear_data()
{
    fill(buffer_.begin(), buffer_.end(), 0);
    header_ = reinterpret_cast<SectionHeader *>(buffer_.data());
    used_size_ =  sizeof (SectionHeader);

    init_header();
}

bool SectionMemoryCache::is_empty()
{
    return used_size_ == sizeof (SectionHeader);
}

void SectionMemoryCache::load(IFileReader &reader)
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

    if (nleft > 0)
        err_quit("incomplete section header");

    header_ = reinterpret_cast<SectionHeader *>(buffer_.data());
    used_size_ = header_->section_size;
}

void SectionMemoryCache::flush(IFileWriter &writer)
{
    header_->section_size = used_size_;
    header_->CRC = calculate_crc32(header_->files, section_body_size());
    writer.write(buffer_.data(), buffer_.size());
}

int SectionMemoryCache::available_size() const
{
    return buffer_.size() - used_size_;
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
    used_size_ += file_size;
    return true;
}

vector<DatafileView> SectionMemoryCache::get_file_list() const
{
    const uint8_t *data = header_->files;
    const uint8_t *data_end = buffer_.data() + used_size_;

    vector<DatafileView> files;
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

uint32_t SectionMemoryCache::section_size() const
{
    return used_size_;
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
    return buffer_.data()+used_size_;
}

void SectionMemoryCache::init_header()
{
    // TODO initialize header, magic, version, timestamp etc...
    header_->magic = SectionConfig::kSectionMagic; 
    header_->version = SectionConfig::kSectionVersion;
}

uint32_t SectionMemoryCache::section_body_size()
{
    return section_size() - sizeof (SectionHeader);
}
