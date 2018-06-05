#ifndef __datafile_metadata_h
#define __datafile_metadata_h

#include <map>
#include <string>
#include <chrono>

class DatafileMetadata {
public:
    static const char *METADATA_KEY;
    static const char *METADATA_REFTYPE;

    using AttrMap = std::map<std::string, std::string>;

private:
    int32_t size_ = 0;
    std::string etag_;
    std::string content_type_;
    std::chrono::system_clock::time_point creation_time_;
    AttrMap attrs_;
    std::string file_name_;

public:
    DatafileMetadata(const std::string &file_name, const std::string &file_type,
            const uint8_t *file_data, int file_size, const AttrMap &attrs);

    DatafileMetadata(const char *serialized_data, size_t len);

    DatafileMetadata(const std::string &serialized_data); 

    std::string serialize() const ;

    int32_t file_size() const;
    const std::string &etag() const;
    const std::string &content_type() const;
    std::chrono::system_clock::time_point creation_time() const;
    const std::map<std::string, std::string> &attrs() const;
    const std::string &file_name() const;

private:
    void deserialize(const char *data, size_t len);
};

#endif
