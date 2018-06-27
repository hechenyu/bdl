#include <iostream>
#include "error.h"
#include "dataset_config.h"

using namespace std;

int main(int argc, char *argv[])
{
    err_msg("hello world!");
    cout << "dataset_config: " << DatasetConfig::printable_info() << endl;

    return 0;
}
