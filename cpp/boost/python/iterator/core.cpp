#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/def.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/module.hpp>
#include <boost/python/reference_existing_object.hpp>

#include "container.h"
#include "containeritem.h"
#include "containeriterator.h"

using namespace boost::python;

class ContainerPythonIterator {
public:
  explicit ContainerPythonIterator(const Container &source)
      : m_begin(source.begin()), m_end(source.end()), first_or_done(true) {}

  const ContainerItem &next() {
    if(!first_or_done)
      ++m_begin;
    else
      first_or_done = false;
    if (m_begin == m_end) {
      first_or_done = true;
      objects::stop_iteration_error();
    }
    return *m_begin;
  }

private:
  ContainerIterator m_begin;
  ContainerIterator m_end;
  bool first_or_done;
};

ContainerPythonIterator make_pyiterator(const Container &source) {
  return ContainerPythonIterator(source);
};

const Container &container() {
  static Container container;
  return container;
}

BOOST_PYTHON_MODULE(core) {

  class_<Container, boost::noncopyable>("Container", no_init)
      .def("__iter__", make_pyiterator);

  class_<ContainerPythonIterator>("ContainerPythonIterator", no_init)
      .def("__iter__", objects::identity_function())
      .def(
#if PY_VERSION_HEX >= 0x03000000
          "__next__"
#else
          "next"
#endif
          ,
          &ContainerPythonIterator::next,
          return_value_policy<reference_existing_object>());

  class_<ContainerItem, boost::noncopyable>("ContainerItem", no_init)
      .add_property("index", &ContainerItem::index, "Return the index");

  def("container", container, return_value_policy<reference_existing_object>());
}
