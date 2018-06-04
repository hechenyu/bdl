#include <map>
#include <string>
#include <iostream>
#include "create_datafile.h"
#include "section_memory_cache.h"
#include "posix_file_writer.h"
#include "print_section.h"

using namespace std;

int main(int argc, char *argv[])
{
    string filename = "test.section";
    int nfile = 10;
    int section_size = 10*1024;

    string blob = "hello world! xxx -- ";
    string etag = "tag yyy -- ";
    string content_type = "type zzz -- ";
    map<string, string> attrs = 
        {{"key1", "value1"}, {"key2", "value2"}};

    SectionMemoryCache section(section_size); 
    for (int i = 0; i < nfile; i++) {
        string index = to_string(i+1);
        auto serialized_data = create_datafile(
                etag+index, content_type+index, attrs,
                blob+index);
        if (!section.append_file(serialized_data.data(), 
                    serialized_data.size())) {
            cout << "section is full" << endl;
            break;
        }
    }

    PosixFileWriter writer;
    writer.open(filename.c_str());
    writer.truncate();

    section.flush(writer);
    print_section_header(section, "section header:");

    return 0;
}

