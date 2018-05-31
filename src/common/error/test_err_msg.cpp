#include "error.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <system_error>

using namespace std;

int main(int argc, char *argv[])
try
{
    const char *filename = "./nofile.txt";
    if (argc > 1)
        filename = argv[1];

    if (open(filename, O_RDONLY) < 0) {
        err_msg("open file %s fail", filename);
    } else {
        cout << "open file " << filename << " success!" << endl;
    }

    cout << "process exit normally" << endl;
    return 0;
}
catch (const system_error &e)
{
    cout << "catch system_error" << endl;
    cout << e.what() << endl;
}
catch (const runtime_error &e)
{
    cout << "catch runtime_error" << endl;
    cout << e.what() << endl;
}
