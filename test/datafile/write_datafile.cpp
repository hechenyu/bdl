#include "datafile_config.h"
#include "datafile_metadata.h"
#include "datafile_serializer.h"
#include "print_metadata.h"
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " etag outfile" << endl;
        return 0;
    }

    string blob;

    string line;
    while (getline(cin, line)) {
        blob += line;
        blob += '\n';
    }

    DatafileMetadata meta(argv[1], "plain/txt", (const uint8_t *) blob.data(), blob.size(),
            {{"key1", "value1"}, {"key2", "value2"}});

    print(meta, "orignal metadata:");

    DatafileSerializer datafile_serializer;
    vector<uint8_t> serialize_data = datafile_serializer.serialize((const uint8_t *) blob.data(), blob.size(), meta);
    assert(serialize_data.size() % DatafileConfig::kAlignSize == 0);

    ofstream ofile(argv[2]);
    if (!ofile) {
        cout << "open file for write error, file name: " << argv[2] << endl;
        return -1;
    }

    ofile.write((char *)serialize_data.data(), serialize_data.size());

    return 0;
}


