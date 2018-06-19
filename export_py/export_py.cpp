#include <memory>
#include <string>
#include <iostream>
#include <boost/python.hpp>
#include "io_context.h"
#include "dataset_index.h"

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

    class_<DatasetIndex>("Index", 
            init<std::shared_ptr<IOContext>, std::string, std::string>());
}


