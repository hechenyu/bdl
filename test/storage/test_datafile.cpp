#include "datafile_config.h"
#include "datafile_metadata.h"
#include "datafile_serializer.h"
#include "print_metadata.h"
#include "dump_data.h"
#include <string>
#include <chrono>
#include <iostream>
#include <cassert>

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    DatafileMetadata meta;

    meta.etag = "tag_aaa";
    meta.content_type = "image";
    meta.creation_time = system_clock::now();
    meta.attrs = {{"key1", "value1"}, {"key2", "value2"}};

    print(meta, "orignal metadata:");

    string blob = "hello world!";

    DatafileSerializer datafile_serializer;
    vector<uint8_t> serialize_data = datafile_serializer.serialize(blob.data(), blob.size(), meta);
    assert(serialize_data.size() % DatafileConfig::kAlignSize == 0);

    dump_data("\nmeta serialize", (const char *) serialize_data.data(), serialize_data.size());

//    DatafileMetadata meta2(serialize_data);
//    print(meta2, "metadata from serialize_data:");

    return 0;
}


