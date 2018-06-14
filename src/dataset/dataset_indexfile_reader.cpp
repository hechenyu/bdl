#include "dataset_indexfile_reader.h"

using namespace std;

DatasetIndexfileReader::DatasetIndexfileReader(shared_ptr<IFileSystem> file_system, 
        const string &indexfile_path, const string &partition_path): file_system_(file_system)
{
    indexfile_path_ = make_shared<string>(indexfile_path);
    partition_path_ = make_shared<string>(partition_path);
}
