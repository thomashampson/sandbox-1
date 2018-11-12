#include <boost/python/def.hpp>
#include <boost/python/module.hpp>
#include <boost/python/type_id.hpp>

using namespace boost::python;

std::string global_string;

void set_the_string(const std::string & value) {
  global_string = value;
}

std::string get_the_string() {
  return global_string;
}

#if PY_VERSION_HEX < 0x03000000

struct from_unicode_py2 {

  from_unicode_py2() {
    boost::python::converter::registry::push_back(
                                                  &convertible,
                                                  &construct,
                                                  boost::python::type_id<std::string>());
  }

  static void* convertible(PyObject* obj_ptr) {
    return (PyUnicode_Check(obj_ptr)) ? obj_ptr : 0;
  }

  static void construct(PyObject* obj_ptr,
                        boost::python::converter::rvalue_from_python_stage1_data* data) {
    PyObject *pyutf8 = PyUnicode_AsUTF8String(obj_ptr);
    if (pyutf8 == 0) boost::python::throw_error_already_set();
    const char* value = PyString_AsString(pyutf8);
    if (value == 0) boost::python::throw_error_already_set();
    Py_DECREF(pyutf8);
    void* storage = (
                     (boost::python::converter::rvalue_from_python_storage<std::string>*)
                     data)->storage.bytes;
    new (storage) std::string(value);
    data->convertible = storage;
  }

};

#endif

BOOST_PYTHON_MODULE(stringy) {

#if PY_VERSION_HEX < 0x03000000
  from_unicode_py2();
#endif

  def("set_the_string", set_the_string);
  def("get_the_string", get_the_string);

}
