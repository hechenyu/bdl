#include "indexfile_reader.h"

using namespace std;

IndexfileReader::IndexfileReader(shared_ptr<ILineReader> reader): reader_(reader)
{
}

bool IndexfileReader::has_next()
{
    string s;
    bool ret = reader_->getline(s);
    if (!ret) { // EOF
        return false;
    }

    item_.deserialize(s);
    return true;
}

IndexItem IndexfileReader::next()
{
    return std::move(item_);
}
