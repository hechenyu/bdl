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
#include "dataset_direct_reader.h"
#include "export_py.h"

using namespace boost::python;

void demo()
{
    std::cout << "hello st_dataset!" << std::endl;
    std::cout << "dataset_config: " << DatasetConfig::printable_info() << std::endl;
    std::cout << "STDC_FILE_READER_BUFFER_SIZE: " << STDC_FILE_READER_BUFFER_SIZE << std::endl;
}

std::shared_ptr<IOContext> (*create_io_context1) (std::string) = IOContext::create_io_context;
std::shared_ptr<IOContext> (*create_io_context2) (std::string, const IOContext::Configure &) = IOContext::create_io_context;

DatasetDirectReader::FileReadHandle 
(DatasetDirectReader::*DatasetDirectReader_openFile1)(DatasetIndexItem index_item) = &DatasetDirectReader::openFile; 

DatasetDirectReader::FileReadHandle 
(DatasetDirectReader::*DatasetDirectReader_openFile2)(std::string serialized_item) = &DatasetDirectReader::openFile; 

dict getAttrs(DatasetFileReadHandle &handle)
{
    auto m = handle.getAttrs();
    dict d;

    for (auto &pair: m) {
        d[pair.first] = pair.second;
    }

    return d;
}

BOOST_PYTHON_MODULE(st_dataset)
{
    def("demo", demo);

    class_<IOContext::Configure>("IOConfig", "config of dataset loader")
        .def_readwrite("read_buffered", &IOContext::Configure::read_buffered, "flag of file reader using read buffer or not")
        ;

    class_<std::shared_ptr<IOContext>>("IOContextPtr", "st_dataset.create_io_context return type, and used by st_dataset.Index");
    def("create_io_context", create_io_context1, "create io context, input params root_name");
    def("create_io_context", create_io_context2, "create io context, input params root_name and IOConfig");

    class_<DatasetIndexItem>("IndexItem", init<std::string>())
        .def_readonly("file_path", &DatasetIndexItem::file_path)
        .def_readonly("offset", &DatasetIndexItem::offset)
        .def_readonly("file_size", &DatasetIndexItem::file_size)
        .def_readonly("partition_path", &DatasetIndexItem::partition_path)
        .def("to_string", &DatasetIndexItem::to_string, "serialized IndexItem to string")
        ;

    class_<DatasetIndexfileReader>("Indexfile", "file reader of st_dataset.IndexItem", no_init)
        .def("__iter__", iterator<DatasetIndexfileReader>(), demo_dataset_index_indexfiles_docs)
        ;

    class_<std::vector<DatasetIndexfileReader>>("IndexfileList", "list of Indexfile, st_dataset.Index.IndexFiles return type", no_init)
        .def("__iter__", iterator<std::vector<DatasetIndexfileReader>>(), demo_dataset_index_indexfiles_docs)
        ;

    class_<std::vector<uint8_t>>("ByteArray", "can convert to bytes type, return type of st_dataset.FileReadHandle.readAll")
        .def("__iter__", iterator<std::vector<uint8_t>>(), demo_dataset_read_docs);

    class_<DatasetFileReadHandle>("FileReadHandle", "file handle of read datafile from dataset, st_dataset.Index.open return type", no_init)
        .def("readAll", &DatasetFileReadHandle::readAll, demo_dataset_read_docs)
        ;

    class_<DatasetIndex::FileAppendHandle>("FileAppendHandle", "file handle of append datafile to dataset, st_dataset.Index.Append", no_init)
       .def("writeAll", &DatasetIndex::FileAppendHandle::writeAll, demo_dataset_index_append_docs)
       ;

    class_<DatasetIndex>("Index", dataset_index_docs, init<std::shared_ptr<IOContext>, std::string, std::string>())
        .def("__iter__", iterator<DatasetIndex>(), demo_dataset_index_iterator_docs)
        .def_readonly("IndexFiles", &DatasetIndex::getIndexFiles, demo_dataset_index_indexfiles_docs)
        .def("open", &DatasetIndex::openFile, demo_dataset_read_docs)
        .def("AppendItem", &DatasetIndex::appendItem, demo_dataset_index_appenditem_docs)
        .def("Append", &DatasetIndex::appendFile, demo_dataset_index_append_docs)
        ;

    class_<DatasetDirectReader>("DirectReader", "direct read from dataset", init<std::shared_ptr<IOContext>>())
        .def("open", DatasetDirectReader_openFile1, demo_dataset_direct_reader1_docs)
        .def("open", DatasetDirectReader_openFile2, demo_dataset_direct_reader2_docs)
        ;

    def("getAttrs", getAttrs, demo_dataset_get_attrs_docs);
}



