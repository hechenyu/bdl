#include <map>
#include <string>
#include <iostream>
#include "section_memory_cache.h"
#include "posix_file_reader.h"
#include "print_section.h"

using namespace std;

int main(int argc, char *argv[])
{
    string filename = "test.section";
    int section_size = 10*1024;

    PosixFileReader reader;
    reader.open(filename.c_str());

    SectionMemoryCache section(section_size); 
    section.load(reader);
    print(section, "section from file: ");

    return 0;
}
