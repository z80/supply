
#include "supply.h"
#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE( supplyctrlusb )
{
    // Create the Python type object for our extension class and define __init__ function.
    class_<Supply>("Supply", init<>())
        .def( "setIo", &Supply::setIo )
        .def( "io", &Supply::io )
        .def( "reopen", &Supply::reopen );
}






