#include "print_metadata.h"

#include <string>
#include <chrono>
#include <map>
#include <iostream>

using namespace std;
using namespace std::chrono;

string utc_to_string(const system_clock::time_point &tp)
{
    char buffer[80];
    time_t tt = system_clock::to_time_t(tp);
    struct tm timeinfo;

    {
        struct tm *ptm = gmtime(&tt);
        timeinfo = *ptm;
    }

    strftime (buffer,80,"%Y-%m-%d,%H:%M:%S",&timeinfo);

    return string(buffer);
}

void print(const DatafileMetadata &meta, const string &title)
{
    cout << title << "\n";
    cout << "\tmeta.etag: " << meta.etag << "\n";
    cout << "\tmeta.content_type: " << meta.content_type << "\n";
    cout << "\tmeta.creation_time: " << utc_to_string(meta.creation_time) << "\n";

    for (auto &attr: meta.attrs)
        cout << "\tmeta.attrs[" << attr.first << "]: " << attr.second << "\n";
}

