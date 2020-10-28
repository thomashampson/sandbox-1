#pragma once

#include <sip.h>
#include <stdexcept>

#include <boost/python/object.hpp>

// Alias for boost python object wrapper
using Object = boost::python::object;

// Alias for handle wrapping a raw PyObject*
template <typename T = PyObject> using Handle = boost::python::handle<T>;

// Helper to create an Object from a new reference to a raw PyObject*
inline Object NewRef(PyObject *obj) {
  return Object(Handle<>(obj));
}

inline Object BorrowedRef(PyObject *obj) {
  return Object(Handle<>(boost::python::borrowed(obj)));
}

namespace Detail {
  const sipAPIDef *sipAPI();
} // namespace detail

/**
 * Extract a C++ object of type T from the Python object
 * @param obj A sip-wrapped Python object
 */
template <typename T> T *extract(const Object &obj) {
  const auto sipapi = Detail::sipAPI();
  if (!PyObject_TypeCheck(obj.ptr(), sipapi->api_wrapper_type)) {
    throw std::runtime_error("extract() - Object is not a sip-wrapped type.");
  }
  // transfer ownership from python to C++
  sipapi->api_transfer_to(obj.ptr(), 0);
  // reinterpret to sipWrapper
  auto wrapper = reinterpret_cast<sipSimpleWrapper *>(obj.ptr());
#if (SIP_API_MAJOR_NR == 8 && SIP_API_MINOR_NR >= 1) || SIP_API_MAJOR_NR > 8
  return static_cast<T *>(sipapi->api_get_address(wrapper));
#elif SIP_API_MAJOR_NR == 8
  return static_cast<T *>(wrapper->data);
#else
  return static_cast<T *>(wrapper->u.cppPtr);
#endif
}
