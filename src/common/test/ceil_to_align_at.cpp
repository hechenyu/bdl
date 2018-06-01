#include "ceil_to_align_at.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " num align_at" << endl;
        return -1;
    }

    auto val = stol(argv[1]);
    auto align = stoi(argv[2]);

    auto val_align = ceil_to_align_at(val, align);

    cout << val << " ceil to align at " << align << " is " << val_align << endl;

    return 0;
}
