#include <boost/python.hpp>
#include <iostream>
#include <string>

namespace bp = boost::python;

namespace {
  /// Singleton type not directly constructible
  class Singleton {
    Singleton() : _value("singleton") { std::cerr << "Singleton constructor: " << this << "\n"; }
    ~Singleton() { std::cerr << "Singleton destructor: " << this << "\n"; }

    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;

  public:
    static Singleton & instance() {
      static Singleton env;
      return env;
    }
    const std::string get() const { return _value; }

  private:
    std::string _value;
  };

  // Indirection method
  const std::string singleton_get(Singleton const * const self) {
    return self->get();
  }

  Singleton& default_Singleton() { return Singleton::instance(); }

  /// Constructible type
  class Constructible {
  public:
    Constructible() : _v("constructible") {std::cerr << "Constructible constructor: " << this << "\n";}
    ~Constructible() { std::cerr << "Constructible destructor: " << this << "\n"; }
    const std::string get() const { return _v; }
  private:
    std::string _v;
  };

  // Indirection method
  const std::string constructible_get(const Constructible &self) {
    return self.get();
  }


}

BOOST_PYTHON_MODULE(const_ref_self) {

  bp::def("singleton", &default_Singleton, bp::return_value_policy<bp::reference_existing_object>());
  bp::class_<Singleton, boost::noncopyable>("Singleton", bp::no_init)
    .def("get", &singleton_get);

  bp::class_<Constructible>("Constructible")
    .def("get", &constructible_get);

}