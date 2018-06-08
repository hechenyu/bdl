#ifndef __indexfile_writer_h
#define __indexfile_writer_h

#include <memory>
#include "index_item.h"
#include "i_line_writer.h"

class IndexfileWriter {
private:
    std::shared_ptr<ILineWriter> writer_;

public:
    IndexfileWriter(std::shared_ptr<ILineWriter> writer);

    void write(const IndexItem &item);
};

#endif

