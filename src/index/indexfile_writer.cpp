#include "indexfile_writer.h"

using namespace std;

IndexfileWriter::IndexfileWriter(shared_ptr<ILineWriter> writer): writer_(writer)
{
}

void IndexfileWriter::write(const IndexItem &item)
{
    auto data = item.serialize();
    writer_->putline(data);
}

