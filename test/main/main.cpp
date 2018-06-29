#include <iostream>
#include "error.h"
#include "io_config.h"
#include "dataset_config.h"

using namespace std;

int main(int argc, char *argv[])
{
    err_msg("hello world!");
    cout << "dataset_config: " << DatasetConfig::printable_info() << endl;
    std::cout << "STDC_FILE_READER_BUFFER_SIZE: " << STDC_FILE_READER_BUFFER_SIZE << std::endl;

    return 0;
}
