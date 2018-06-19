#ifndef __indexfile_reader_h
#define __indexfile_reader_h

#include <memory>
#include "indexfile_item.h"
#include "i_line_reader.h"

class IndexfileReader {
private:
    std::shared_ptr<ILineReader> reader_;
    IndexfileItem item_;   // cache last item

public:
    IndexfileReader(const std::string &file_path, std::shared_ptr<ILineReader> reader);
    ~IndexfileReader();

    bool has_next();
    std::shared_ptr<IndexfileItem> next();
    IndexfileItem next_move();
};

#endif
