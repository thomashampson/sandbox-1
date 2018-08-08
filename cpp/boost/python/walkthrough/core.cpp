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
      : m_begin(source.begin()), m_end(source.end()), m_current(*m_begin) {}

  const ContainerItem &next() {
    if (m_begin == m_end)
      objects::stop_iteration_error();
    m_current = *m_begin++;
    return m_current;
  }

private:
  ContainerIterator m_begin;
  ContainerIterator m_end;
  ContainerItem m_current;
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
          return_value_policy<copy_const_reference>());

  class_<ContainerItem>("ContainerItem", no_init)
      .add_property("index", &ContainerItem::index, "Return the index");

  def("container", container, return_value_policy<reference_existing_object>());
}
