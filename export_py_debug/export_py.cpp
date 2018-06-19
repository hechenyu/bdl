#include <memory>
#include <string>
#include <iostream>
#include <boost/python.hpp>
#include "io_context.h"
#include "dataset_index.h"
#include "dataset_index_item.h"
#include "posix_file_system.h"

using namespace boost::python;

void demo()
{
    std::cout << "hello st_dataset!" << std::endl;
}

BOOST_PYTHON_MODULE(st_dataset)
{
    def("demo", demo);

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
}


