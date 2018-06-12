#include "indexfile_writer.h"

using namespace std;

IndexfileWriter::IndexfileWriter(const std::string &file_path, shared_ptr<ILineWriter> writer): writer_(writer)
{
    writer_->open_for_append(file_path.c_str());
}

IndexfileWriter::~IndexfileWriter()
{
    writer_->close();
}

void IndexfileWriter::write(const IndexItem &item)
{
    auto data = item.serialize();
    writer_->putline(data);
}

