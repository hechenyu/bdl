#include <string>
#include <iostream>
#include <memory>
#include <boost/python.hpp>
#include "io_context.h"
#include "dataset_index.h"
#include "dataset_index_item.h"

using namespace boost::python;

void demo()
{
    std::cout << "hello st_dataset!" << std::endl;
}

BOOST_PYTHON_MODULE(st_dataset)
{
    def("demo", demo);

    class_<std::shared_ptr<IOContext>>("IOContextPtr");
    def("create_io_context", &IOContext::create_io_context);

    class_<DatasetIndexItem>("IndexItem")
        .def_readonly("file_path", &DatasetIndexItem::file_path)
        .def_readonly("offset", &DatasetIndexItem::offset)
        .def_readonly("file_size", &DatasetIndexItem::file_size)
        .def_readonly("partition_path", &DatasetIndexItem::partition_path)
        ;

    class_<DatasetIndexfileReader>("IndexFile", no_init)
        .def("__iter__", iterator<DatasetIndexfileReader>())
        ;

    class_<std::vector<DatasetIndexfileReader>>("IndexFileList")
        .def("__iter__", iterator<std::vector<DatasetIndexfileReader>>())
        ;

    class_<DatasetIndex>("Index", init<std::shared_ptr<IOContext>, std::string, std::string>())
        .def("__iter__", iterator<DatasetIndex>())
        .def("IndexFiles", &DatasetIndex::getIndexFiles)
        ;
}


