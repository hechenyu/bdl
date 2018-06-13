#include "error.h"
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

void IndexfileWriter::write(const IndexfileItem &item)
{
    check_item_valid(item);

    auto data = item.serialize();
    writer_->putline(data);
}

void IndexfileWriter::check_item_valid(const IndexfileItem &item)
{
    if (item.key.find_first_of(",") != string::npos)
        err_quit("Invalid indexfile item: %s", item.key.c_str());
}
