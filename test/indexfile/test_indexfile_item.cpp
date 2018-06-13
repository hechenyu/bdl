#include <iostream>

#include "indexfile_item.h"
#include "print_indexfile_item.h"

using namespace std;

int main(int argc, char *arg[])
{
    IndexItem item;
    item.key = "/tmp/test.txt";
    item.offset = 1024;
    item.file_size = 2048;

    cout << "original item: " << item << endl;

    string serialized_data = item.serialize();

    cout << "serialized data: " << serialized_data << endl; 

    IndexItem item2;
    item2.deserialize(serialized_data);
    cout << "desrialized item: " << item2 << endl;

    serialized_data = "/home/xxx/xxa.txt, 0X100, 0X1000";
    item.deserialize(serialized_data);
    cout << "desrialized item from \"" << serialized_data << "\": " << item << endl;

    return 0;
}
