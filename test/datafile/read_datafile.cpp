#include "datafile_config.h"
#include "datafile_metadata.h"
#include "datafile_serializer.h"
#include "datafile_view.h"
#include "print_metadata.h"
#include "print_datafile.h"
#include "dump_data.h"
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " file" << endl;
        return -1;
    }

    ifstream  in(argv[1]);
    istreambuf_iterator<char>  beg(in),  end;    
    string  serialize_data(beg,  end);

    DatafileView datafile_view((const uint8_t *) serialize_data.data(), serialize_data.size());
    print(datafile_view, "datafile from serialize_data:");

    return 0;
}


