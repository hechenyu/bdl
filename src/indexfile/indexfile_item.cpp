#include "error.h"
#include "indexfile_item.h"
#include <sstream>
#include <iomanip>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

IndexItem::IndexItem(const string &key, uint32_t offset, uint32_t file_size):
    key(key), offset(offset), file_size(file_size)
{
}

string IndexItem::serialize() const
{
    ostringstream os;
    os << this->key << "," 
        << hex << showbase << uppercase
        << this->offset << ","
        << this->file_size; 
    return os.str();
}

void IndexItem::deserialize(const string &s)
{
    vector<string> results;

    split(results, s, is_any_of(","));  // Note this is boost::split

    const int expect_item_fields = 3;
    if (results.size() != expect_item_fields) {
        err_quit("invalid index item, fields number not correct: "
                "expect %d fields, actual %d fields", 
                expect_item_fields, results.size());
    }

    this->key = results[0];
    this->offset = stoul(results[1], nullptr, 0);
    this->file_size = stoul(results[2], nullptr, 0);
}
