//
// Module
//
#include "core/matrixworkspace.h"

#include <boost/python/class.hpp>
#include <boost/python/module.hpp>

using boost::python::no_init;
using boost::python::class_;

BOOST_PYTHON_MODULE(pycore) {

  class_<Workspace, boost::noncopyable>("Workspace", no_init);
  class_<MatrixWorkspace>("MatrixWorkspace")
    .def("id", &MatrixWorkspace::id)
  ;
}
