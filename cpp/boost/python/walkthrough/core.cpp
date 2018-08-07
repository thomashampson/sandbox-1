#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/reference_existing_object.hpp>
#include <boost/python/def.hpp>
#include <boost/python/module.hpp>
#include <boost/python/iterator.hpp>

#include "container.h"
#include "containeritem.h"
#include "containeriterator.h"

using namespace boost::python;

const Container &container() {
  static Container container;
  return container;
}

BOOST_PYTHON_MODULE(core) {

  class_<Container>("Container", no_init)
    .def("__iter__", range<return_value_policy<copy_const_reference> >(
               &Container::begin
             , &Container::end));

  class_<ContainerItem>("Iterator", no_init)
         .add_property("index", &ContainerItem::index,
                       "Return the index");

  def("container", container,
      return_value_policy<reference_existing_object>());
}
