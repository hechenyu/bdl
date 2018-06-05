#include "datafile_metadata.h"
#include "print_metadata.h"
#include "dump_data.h"
#include <string>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    string blob = "test";
    DatafileMetadata meta("test.txt", "plain/txt", (const uint8_t *) blob.data(), blob.size(),
            {{"key1", "value1"}, {"key2", "value2"}});

    print(meta, "orignal metadata:");

    string serialize_data = meta.serialize();
    dump_data("\nmeta serialize", serialize_data.data(), serialize_data.size());

    DatafileMetadata meta2(serialize_data);
    print(meta2, "metadata from serialize_data:");

    return 0;
}

