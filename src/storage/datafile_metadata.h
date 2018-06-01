#ifndef __datafile_metadata_h
#define __datafile_metadata_h

#include <map>
#include <string>
#include <chrono>

struct DatafileMetadata {
    static const char *METADATA_KEY;
    static const char *METADATA_REFTYPE;

    using AttrMap = std::map<std::string, std::string>;

    int32_t size = 0;
    std::string etag;
    std::string content_type;
    std::chrono::system_clock::time_point creation_time;
    std::map<std::string, std::string> attrs;

    DatafileMetadata() {}

    DatafileMetadata(const char *data, size_t len) {
        init(data, len);
    }

    DatafileMetadata(const std::string &data) {
		if (!data.empty())
			init(data.data(), data.size());
    }

    std::string toString() const ;

private:
    void init(const char *data, size_t len);
};

#endif
