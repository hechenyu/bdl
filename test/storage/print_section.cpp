#include <iostream>
#include <iomanip>
#include "print_section.h"
#include "print_datafile.h"

using namespace std;

void print_section_header(const SectionMemoryCache &section, const std::string &title)
{
    cout << title << "\n";
    cout << "\tsection.magic: " << showbase << hex << section.magic() << dec << "\n";
    cout << "\tsection.CRC: " << showbase << hex << section.CRC() << dec << "\n";
    cout << "\tsection.version: " << section.version() << "\n";
    cout << "\tsection.section_size: " << section.section_size() << "\n";
    cout << "\tsection.timestamp: " << section.timestamp() << "\n";
}

void print(const SectionMemoryCache &section, const std::string &title)
{
    cout << title << "\n";
    cout << "===============================\n";
    print_section_header(section, "section header:");
    cout << "===============================\n";
    cout << "file data:\n";

    auto files = section.get_file_list();
    int i = 1;
    for (auto file: files) {
        cout << "--------------------------\n";
        print(file, "file"+to_string(++i)+":");
    } 

    cout << "===============================\n";
}
