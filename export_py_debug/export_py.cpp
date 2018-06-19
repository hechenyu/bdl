#include <memory>
#include <string>
#include <iostream>
#include <boost/python.hpp>
#include "io_context.h"
#include "dataset_index.h"
#include "dataset_index_item.h"
#include "posix_file_system.h"
#include "dataset_indexfile_reader.h"

using namespace boost::python;

void demo()
{
    std::cout << "hello st_dataset!" << std::endl;
}

BOOST_PYTHON_MODULE(st_dataset)
{
    def("demo", demo);

    class_<std::shared_ptr<IFileSystem>>("IFileSystemPtr");

    def("create_posix_file_system", &create_posix_file_system);

    class_<IndexfileItem>("IndexfileItem")
        .def_readwrite("key", &IndexfileItem::key)
        .def_readwrite("offset", &IndexfileItem::offset)
        .def_readwrite("file_size", &IndexfileItem::file_size)
        ;

    class_<std::shared_ptr<ILineReader>>("ILineReaderPtr")
        ;

    class_<PosixFileSystem>("PosixFileSystem")
        .def("create_line_reader", &PosixFileSystem::create_line_reader)
        ;

    class_<IndexfileReader>("IndexfileReader", init<const std::string &, std::shared_ptr<ILineReader>>())
        .def("has_next", &IndexfileReader::has_next)
        .def("next", &IndexfileReader::next_move)
        ;

    class_<DatasetIndexItem>("IndexItem")
        .def_readonly("file_path", &DatasetIndexItem::file_path)
        .def_readonly("offset", &DatasetIndexItem::offset)
        .def_readonly("file_size", &DatasetIndexItem::file_size)
        .def_readonly("partition_path", &DatasetIndexItem::partition_path)
        ;

    class_<DatasetIndexfileReader>("DatasetIndexfileReader", init<std::shared_ptr<IFileSystem>, const std::string &, const std::string &>())
        .def("__iter__", iterator<DatasetIndexfileReader>())
        ;
}


