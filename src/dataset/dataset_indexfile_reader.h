#ifndef __dataset_indexfile_reader_h
#define __dataset_indexfile_reader_h

#include <memory>
#include <string>
#include <iterator>
#include "i_file_system.h"
#include "indexfile_reader.h"
#include "dataset_index_item.h"

class DatasetIndexfileReader {
private:
    std::shared_ptr<IFileSystem> file_system_;
    std::shared_ptr<std::string> indexfile_path_;
    std::shared_ptr<std::string> partition_path_;
    mutable std::shared_ptr<IndexfileReader> indexfile_reader_; 
    DatasetIndexItem index_item_;

    friend class iterator;

public:
    DatasetIndexfileReader(std::shared_ptr<IFileSystem> file_system, 
            const std::string &indexfile_path, const std::string &partition_path);

public:
    struct iterator: public std::iterator<std::input_iterator_tag, DatasetIndexItem, std::ptrdiff_t, 
            const DatasetIndexItem *, const DatasetIndexItem &>  {
        DatasetIndexfileReader *reader_;
        bool is_eof_ = true;

        typedef iterator this_type;

        iterator() = default;
        iterator(DatasetIndexfileReader *reader): reader_(reader) 
        {
            next();
        }

        reference operator *() const
        {
            return reader_->index_item_;
        }

        pointer operator ->() const
        {
            return &reader_->index_item_;
        }

        void next()
        {
            is_eof_ = !reader_->get_next_item();
        }

        this_type &operator ++()
        {
            next();
            return *this;
        }

        this_type operator ++(int)
        {
            this_type tmp(*this);
            next();
            return *this;
        }

        bool operator ==(const this_type &other) const
        {
            if (this->is_eof_ && other.is_eof_)
                return true;
            else
                return false;
        }

        bool operator !=(const this_type &other) const
        {
            return !(*this == other);
        }
    };

    iterator begin() const
    {
        if (!indexfile_reader_) {
            indexfile_reader_ = std::make_shared<IndexfileReader>(*indexfile_path_, file_system_->create_line_reader());
        }
        return iterator(const_cast<DatasetIndexfileReader *>(this));
    }

    iterator end() const
    {
        return iterator();
    }

private:
    bool get_next_item();
};

#endif
