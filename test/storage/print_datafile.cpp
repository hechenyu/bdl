#include "print_datafile.h"
#include "print_metadata.h"
#include "dump_data.h"

#include <iostream>
#include <iomanip>

using namespace std;

void print(const DatafileView &view, const std::string &title)
{
    cout << "\n" << title << "\n";
    cout << showbase;
    cout << "header.CRC:           " << hex << view.CRC() << dec << "\n";
    cout << "header.total_size:    " << view.total_size() << "\n";
    cout << "header.blob_size:     " << view.blob_size() << "\n";
    cout << "header.metadata_size: " << view.metadata_size() << "\n";
    cout << "header.flags[0]:      " << hex << (uint32_t) get<0>(view.flags()) << dec << "\n";
    cout << "header.flags[1]:      " << hex << (uint32_t) get<1>(view.flags()) << dec << "\n";

    dump_data("blob", reinterpret_cast<const char *>(view.blob_data()), view.blob_size());

    print(view.metadata(), "metadata");
}
