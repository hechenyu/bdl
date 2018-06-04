#include <iostream>
#include <iomanip>
#include "print_section.h"

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
