#include <cassert>
#include "partition_config.h"
#include "partition_writer.h"
#include "datafile_serializer.h"

using namespace std;

PartitionWriter::PartitionWriter(const string &partition_path, shared_ptr<IFileWriter> writer):
    writer_(writer), path_(partition_path)
{
    writer_->open(path_.c_str());
    writer_->truncate();
    const int section_size = PartitionConfig::kSectionSize;
    section_ = make_shared<SectionMemoryCache>(section_size);
    section_index_ = 0;
}

PartitionWriter::~PartitionWriter()
{
    if (!section_->is_empty())
        section_->flush(*writer_);
    writer_->close();
}

void PartitionWriter::write(const string &file_name, const string &file_type,
        const uint8_t *file_data, int file_size, const DatafileMetadata::AttrMap &attrs)
{
    DatafileMetadata meta(file_name, file_type, file_data, file_size, attrs);
    DatafileSerializer datafile_serializer;
    auto output = datafile_serializer.serialize(file_data, file_size, meta);

    if (!section_->append_file(output.data(), output.size())) {
        section_->flush(*writer_);
        section_.reset();
        section_index_++;

        auto ret = section_->append_file(output.data(), output.size());
        assert(ret);
    }
}

