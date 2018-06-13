#ifndef __index_item_h
#define __index_item_h

#include <string>

class IndexfileItem {
public:
    std::string key;
    uint32_t offset = 0;
    uint32_t file_size = 0;

    IndexfileItem() = default;
    IndexfileItem(const std::string &key, uint32_t offset, uint32_t file_size);

    std::string serialize() const;
    void deserialize(const std::string &s);
};

#endif
