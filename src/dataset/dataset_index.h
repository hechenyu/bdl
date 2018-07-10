#ifndef __dataset_index_h
#define __dataset_index_h

#include <memory>
#include <string>
#include <vector>
#include <iterator>

#include "i_partition_pos_reader_factory.h"
#include "dataset_index_item.h"
#include "dataset_indexfile_reader.h"
#include "dataset_file_read_handle.h"

class IOContext;
class DatasetWriter;
class DatasetIndexfileWriter;
class PartitionPosReader;

class DatasetIndex {
public:
    enum class OpenFlag { kAppend, kRead };

private:
    std::shared_ptr<IOContext> io_context_;
    std::string dataset_name_;
    std::string index_branch_;
    std::vector<std::string> partition_name_list_;
    std::vector<std::string> indexfile_name_list_;
    OpenFlag open_flag_;
    std::shared_ptr<DatasetWriter> dataset_writer_;
    std::shared_ptr<IPartitionPosReaderFactory> partition_pos_reader_factory_;
    std::vector<DatasetIndexfileReader> dataset_indexfile_readers_;
    std::shared_ptr<DatasetIndexfileWriter> dataset_indexfile_writer_;

public:
    class FileAppendHandle {
    private:
        std::shared_ptr<DatasetWriter> dataset_writer_;
        std::shared_ptr<std::string> file_name_; 
        std::shared_ptr<std::string> file_type_;

    public:
        FileAppendHandle(std::shared_ptr<DatasetWriter> dataset_writer, 
                const std::string &file_name, const std::string &file_type);

        void writeAll(const std::string &file_data);
    };

    typedef DatasetFileReadHandle FileReadHandle;

    struct iterator: public std::iterator<std::input_iterator_tag, DatasetIndexItem, std::ptrdiff_t, 
            const DatasetIndexItem *, const DatasetIndexItem &>  {
        std::vector<DatasetIndexfileReader>::const_iterator file_;
        std::vector<DatasetIndexfileReader>::const_iterator end_;
        DatasetIndexfileReader::iterator item_;

        typedef iterator this_type;

        iterator(std::vector<DatasetIndexfileReader>::const_iterator file,
                std::vector<DatasetIndexfileReader>::const_iterator end)
                : file_(file), end_(end)
        {
            while (file_ != end_) {
                item_ = file_->begin();
                if (item_ != file_->end())
                    break;
                ++file_;
            }
        }

        reference operator *() const
        {
            return *item_;
        }

        pointer operator ->() const
        {
            return &*item_;
        }

        void next()
        {
            assert(file_ != end_);

            ++item_;
            if (item_ != file_->end())
                return;

            ++file_;
            while (file_ != end_) {
                item_ = file_->begin();
                if (item_ != file_->end())
                    break;
                ++file_;
            }

            if (file_ == end_) {
                item_ = DatasetIndexfileReader::iterator();
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
            return tmp;
        }

        bool operator ==(const this_type &other) const
        {
            if (this->file_ == other.file_ && this->item_ == other.item_)
                return true;
            else
                return false;
        }

        bool operator !=(const this_type &other) const
        {
            return !(*this == other);
        }
    };

public:
    DatasetIndex(std::shared_ptr<IOContext> io_context, std::string dataset_index_name, std::string open_flag);

    FileAppendHandle appendFile(std::string file_name, std::string file_type);

    void appendItem(DatasetIndexItem index_item);

    FileReadHandle openFile(DatasetIndexItem index_item);   // open file for read only

    std::vector<DatasetIndexfileReader> getIndexFiles();

    iterator begin() const
    {
        return iterator(dataset_indexfile_readers_.begin(), dataset_indexfile_readers_.end());
    }

    iterator end() const
    {
        return iterator(dataset_indexfile_readers_.end(), dataset_indexfile_readers_.end());
    }

private:
    void fill_indexfile_readers();
    void load_indexfile_name_list();
    void load_partition_name_list();
    OpenFlag get_and_check_open_flag(const std::string &open_flag);
    void init_for_append();
    void init_for_read();
    int get_max_part_id() const;
};

#endif
