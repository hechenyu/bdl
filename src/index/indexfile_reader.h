#ifndef __indexfile_reader_h
#define __indexfile_reader_h

#include <memory>
#include "index_item.h"
#include "i_line_reader.h"

class IndexfileReader {
private:
    std::shared_ptr<ILineReader> reader_;
    IndexItem item_;   // cache last item

public:
    IndexfileReader(std::shared_ptr<ILineReader> reader);

    bool has_next();
    IndexItem next();
};

#endif
