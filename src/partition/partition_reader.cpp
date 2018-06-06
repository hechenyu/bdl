#include "error.h"
#include "partition_config.h"
#include "partition_reader.h"

using namespace std;

PartitionReader::PartitionReader(const string &partition_path, shared_ptr<IFileReader> reader): reader_(reader)
{
    const int section_size = PartitionConfig::kSectionSize;
    reader_->open(partition_path.c_str());

    long file_size = reader_->file_size();
    section_index_ = 0;
    total_section_ = file_size / section_size; 

    section_ = make_shared<SectionMemoryCache>(section_size);
    get_next_section();
    datafile_index_ = 0;
}

PartitionReader::~PartitionReader()
{
    reader_->close();
}

bool PartitionReader::has_next()
{
    if (static_cast<size_t>(datafile_index_) == datafile_list_.size()) {
        get_next_section();
        datafile_index_ = 0;
    }

    return (section_index_ < total_section_ || 
            static_cast<size_t>(datafile_index_) < datafile_list_.size());
}

DatafileView PartitionReader::next()
{
    if (!has_next())
        err_quit("PartitionReader::next fail: overflow");

    return datafile_list_.at(datafile_index_++);
}

void PartitionReader::get_next_section() {
    datafile_list_.clear();
    while (section_index_ < total_section_) {
        section_index_++;
        section_->load(*reader_);
        datafile_list_ = section_->get_file_list();
        if (!datafile_list_.empty())
            break;
    }
}

