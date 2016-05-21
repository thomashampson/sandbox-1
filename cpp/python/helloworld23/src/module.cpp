#include <boost/python/def.hpp>
#include <boost/python/module.hpp>

using namespace boost::python;

std::string hello() {
#if PY_MAJOR_VERSION >= 3
  return "Hello Python 3!";
#else
  return "Hello Python 2!";
#endif
}

//------------------------------------------------------------------------------
// Module
//------------------------------------------------------------------------------
BOOST_PYTHON_MODULE(helloworld23)
{
  def("hello", hello);
}
