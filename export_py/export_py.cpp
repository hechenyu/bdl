#include <iostream>
#include <memory>
#include <boost/python.hpp>
#include "io_context.h"

using namespace boost;

void demo()
{
    std::cout << "hello st_dataset!" << std::endl;
}

BOOST_PYTHON_MODULE(st_dataset)
{
    python::def("demo", demo);

    python::class_<std::shared_ptr<IOContext>>("IOContextPtr");
    python::def("create_io_context", &IOContext::create_io_context);
}


