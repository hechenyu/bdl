#include <cstdint>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <boost/python.hpp>
#include "io_config.h"
#include "io_context.h"
#include "dataset_config.h"
#include "dataset_index.h"
#include "dataset_index_item.h"

using namespace boost::python;

void demo()
{
    std::cout << "hello st_dataset!" << std::endl;
    std::cout << "dataset_config: " << DatasetConfig::printable_info() << std::endl;
    std::cout << "STDC_FILE_READER_BUFFER_SIZE: " << STDC_FILE_READER_BUFFER_SIZE << std::endl;
}

std::shared_ptr<IOContext> (*create_io_context1) (std::string) = IOContext::create_io_context;
std::shared_ptr<IOContext> (*create_io_context2) (std::string, const IOContext::Configure &) = IOContext::create_io_context;

BOOST_PYTHON_MODULE(st_dataset)
{
    def("demo", demo);

    class_<IOContext::Configure>("IOConfig")
        .def_readwrite("read_buffered", &IOContext::Configure::read_buffered)
        ;

    class_<std::shared_ptr<IOContext>>("IOContextPtr");
    def("create_io_context", create_io_context1);
    def("create_io_context", create_io_context2);

    class_<DatasetIndexItem>("IndexItem", no_init)
        .def_readonly("file_path", &DatasetIndexItem::file_path)
        .def_readonly("offset", &DatasetIndexItem::offset)
        .def_readonly("file_size", &DatasetIndexItem::file_size)
        .def_readonly("partition_path", &DatasetIndexItem::partition_path)
        ;

    class_<DatasetIndexfileReader>("Indexfile", no_init)
        .def("__iter__", iterator<DatasetIndexfileReader>())
        ;

    class_<std::vector<DatasetIndexfileReader>>("IndexfileList", no_init)
        .def("__iter__", iterator<std::vector<DatasetIndexfileReader>>())
        ;

    class_<std::vector<uint8_t>>("ByteArray")
        .def("__iter__", iterator<std::vector<uint8_t>>());

    class_<DatasetIndex::FileReadHandle>("FileReadHandle", no_init)
        .def("readAll", &DatasetIndex::FileReadHandle::readAll)
        ;

    class_<DatasetIndex::FileAppendHandle>("FileAppendHandle", no_init)
       .def("writeAll", &DatasetIndex::FileAppendHandle::writeAll)
       ;

    class_<DatasetIndex>("Index", init<std::shared_ptr<IOContext>, std::string, std::string>())
        .def("__iter__", iterator<DatasetIndex>())
        .def_readonly("IndexFiles", &DatasetIndex::getIndexFiles)
        .def("open", &DatasetIndex::openFile)
        .def("AppendItem", &DatasetIndex::appendItem)
        .def("Append", &DatasetIndex::appendFile)
        ;
}


