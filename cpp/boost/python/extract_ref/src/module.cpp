#include "DataObjects.h"
#include "DataService.h"
#include "WorkspaceFactory.h"

#include <boost/python/class.hpp>
#include <boost/python/def.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/module.hpp>
#include <boost/python/ptr.hpp>
#include <boost/python/register_ptr_to_python.hpp>
#include <boost/python/scope.hpp>

using namespace boost::python;

//------------------------------------------------------------------------------
// boost methods
//------------------------------------------------------------------------------
namespace boost {

  template<typename T>
  inline T* get_pointer(const boost::weak_ptr<T> & wrapper) {
    if (auto p = wrapper.lock()) {
      // Safe as we can guarantee that another reference exists
      return p.get();
    } else {
      throw std::runtime_error("Variable invalidated, data has been deleted.");
    }
  }
}

//------------------------------------------------------------------------------
// Python methods
//------------------------------------------------------------------------------
void DataService_add(DataService &self,
                     const std::string & name,
                     const boost::python::object & value) {
  extract<WorkspaceWeakPtr> weak_extract(value);
  if(weak_extract.check()) {
    self.add(name, weak_extract().lock());
    return;
  }

  extract<WorkspaceSharedPtr> shared_extract(value);
  if(shared_extract.check()) {
    self.add(name, shared_extract());
  }
}

WorkspaceWeakPtr DataService_get(DataService &self,
                                 const std::string & name) {
  return WorkspaceWeakPtr(self.get(name));
}

void do_something(DataService &svc) {
  auto item = svc.get("test2");
  std::cerr << "Workspace stuff " << item->name() << "\n";
}

//------------------------------------------------------------------------------
// Module
//------------------------------------------------------------------------------
BOOST_PYTHON_MODULE(extract_ref)
{
  // Classes
  class_<DataItem, boost::noncopyable>("DataItem", no_init)
    .def("id", &DataItem::id)
  ;
  class_<Workspace, bases<DataItem>,
         boost::noncopyable>("Workspace", no_init)
    .def("name", &Workspace::name)
  ;
  class_<MatrixWorkspace, bases<Workspace>,
         boost::noncopyable>("MatrixWorkspace", no_init)
  ;
  class_<Workspace2D, bases<MatrixWorkspace>,
         boost::noncopyable>("Workspace2D", no_init)
  ;

  // Factory
  class_<WorkspaceFactory, boost::noncopyable>("WorkspaceFactory", no_init)
    .def("create", &WorkspaceFactory::create)
    .staticmethod("create")
  ;

  // DataService
  class_<DataService, boost::noncopyable>("DataService", no_init)
    .def("add", &DataService_add)
    .def("remove", &DataService::remove)
    .def("get", &DataService_get)
    .def("size", &DataService::size)
    .def("clear", &DataService::clear)
  ;

  // Functions
  def("do_something", &do_something);

  // Pointers
  register_ptr_to_python<WorkspaceSharedPtr>();
  register_ptr_to_python<WorkspaceWeakPtr>();
  register_ptr_to_python<MatrixWorkspaceSharedPtr>();
  register_ptr_to_python<Workspace2DSharedPtr>();
  register_ptr_to_python<DataService*>();

  // Global store - There will be a memory leak with this
  auto * global_store = new DataService;
  scope().attr("global_store") = ptr(global_store);


}
