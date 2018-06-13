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

public:
    DatasetIndexfileReader(std::shared_ptr<IFileSystem> file_system, 
            const std::string &indexfile_path, const std::string &partition_path);

public:
    struct iterator: public std::iterator<std::input_iterator_tag, DatasetIndexItem, std::ptrdiff_t, 
            const DatasetIndexItem *, const DatasetIndexItem &>  {
        std::shared_ptr<std::string> partition_path_;
        std::shared_ptr<IndexfileReader> indexfile_reader_; 
        DatasetIndexItem index_item_;
        bool is_eof_ = true;

        typedef iterator this_type;

        iterator() = default;
        iterator(std::shared_ptr<std::string> partition_path,
                std::shared_ptr<IndexfileReader> indexfile_reader):
            partition_path_(partition_path), indexfile_reader_(indexfile_reader)
        {
            next();
        }

        reference operator *() const
        {
            return index_item_;
        }

        pointer operator ->() const
        {
            return &index_item_;
        }

        void next()
        {
            is_eof_ = !indexfile_reader_->has_next();
            if (!is_eof_) {
                index_item_.file_item_ = indexfile_reader_->next();
                index_item_.partition_path_ = this->partition_path_;
            }
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
        return iterator(partition_path_, 
                std::make_shared<IndexfileReader>(*indexfile_path_, file_system_->create_line_reader()));
    }

    iterator end() const
    {
        return iterator();
    }
};

#endif
