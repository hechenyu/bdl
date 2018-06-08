#include <cassert>
#include "partition_config.h"
#include "partition_writer.h"
#include "datafile_serializer.h"

using namespace std;

PartitionWriter::PartitionWriter(const string &partition_path, shared_ptr<IFileWriter> writer): writer_(writer)
{
    const int section_size = PartitionConfig::kSectionSize;
    section_ = make_shared<SectionMemoryCache>(section_size);
    section_index_ = 0;
    writer_->open(partition_path.c_str());

    writer_->truncate();
}

PartitionWriter::PartitionWriter(const string &partition_path, shared_ptr<IFileWriter> writer, shared_ptr<IFileReader> reader): writer_(writer)
{
    const int section_size = PartitionConfig::kSectionSize;
    section_ = make_shared<SectionMemoryCache>(section_size);
    section_index_ = 0;
    writer_->open(partition_path.c_str());

    reader->open(partition_path.c_str());
    long file_size = reader->file_size();
    int total_section = file_size / section_size; 

    if (total_section == 0) {   // empty file or new file
        reader->close();
        return;
    } 

    section_index_ = total_section - 1;
    long offset = static_cast<long>(section_size) * section_index_;
    reader->seek(offset, SEEK_SET);
    section_->load(*reader);
    reader->close();

    writer_->seek(offset, SEEK_SET);
}

PartitionWriter::~PartitionWriter()
{
    if (!section_->is_empty())
        section_->flush(*writer_);
    writer_->close();
}

DatafileIndex PartitionWriter::write(const string &file_name, const string &file_type,
        const uint8_t *file_data, int file_size, const DatafileMetadata::AttrMap &attrs)
{
    DatafileMetadata meta(file_name, file_type, file_data, file_size, attrs);
    DatafileSerializer datafile_serializer;
    auto output = datafile_serializer.serialize(file_data, file_size, meta);

    long offset = static_cast<long>(PartitionConfig::kSectionSize) * section_index_ + section_->section_size();
    if (!section_->append_file(output.data(), output.size())) {
        section_->flush(*writer_);
        section_->clear_data();
        section_index_++;

        offset = static_cast<long>(PartitionConfig::kSectionSize) * section_index_ + section_->section_size();
        auto ret = section_->append_file(output.data(), output.size());
        assert(ret);
    }

    DatafileIndex index;
    index.offset = offset;
    index.file_size = output.size();

    return index;
}

