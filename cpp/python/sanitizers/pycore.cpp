#include <boost/python/def.hpp>
#include <boost/python/module.hpp>

#include "core.hpp"

using namespace boost::python;

//------------------------------------------------------------------------------
// Module
//------------------------------------------------------------------------------
BOOST_PYTHON_MODULE(core)
{
  def("hello", core::hello);
}
