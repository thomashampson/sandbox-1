#ifndef PYTHONOBJECT_H
#define PYTHONOBJECT_H

#include <Python.h>

namespace Python {

namespace detail {

/**
 * @brief Increase the reference count of the given object
 * @param obj A raw Python object pointer
 * @return Object with increased reference count
 */
inline PyObject *incref(PyObject *obj) {
  Py_INCREF(obj);
  return obj;
}

/**
 * @brief Decrease the reference count of the given object. No NULL check.
 * @param obj A raw Python object pointer
 */
inline void decref(PyObject *obj) { Py_DECREF(obj); }

/**
 * @brief Decrease the reference count of the given object. Checks for NULL.
 * @param obj A raw Python object pointer
 */
inline void xdecref(PyObject *obj) { Py_XDECREF(obj); }
}

struct NewRef {
  explicit NewRef(PyObject *ref) : ptr(ref) {}
  // No copy
  NewRef(const NewRef &) = delete;
  NewRef &operator=(const NewRef &) = delete;
  // Move allowed
  NewRef(NewRef &&) = default;
  NewRef &operator=(NewRef &&) = default;

  PyObject *ptr;
};
struct BorrowedRef {
  explicit BorrowedRef(PyObject *ref) : ptr(detail::incref(ref)) {}
  // No copy
  BorrowedRef(const BorrowedRef &) = delete;
  BorrowedRef &operator=(const BorrowedRef &) = delete;
  // Move allowed
  BorrowedRef(BorrowedRef &&) = default;
  BorrowedRef &operator=(BorrowedRef &&) = default;

  PyObject *ptr;
};

/**
 * @brief A handle for Python objects to handle reference counting in an
 * RAII style. By default an object is construct as None.
 */
class PythonObject {
public:
  PythonObject() : m_ptr(detail::incref(Py_None)) {}
  explicit PythonObject(NewRef ref) : m_ptr(ref.ptr) {}
  explicit PythonObject(BorrowedRef ref) : m_ptr(ref.ptr) {}
  ~PythonObject() { detail::xdecref(m_ptr); }

  inline Py_ssize_t refCount() const { return Py_REFCNT(m_ptr); }
  /// Return true if this object is the None object
  inline bool isNone() const { return m_ptr == Py_None; }

private:
  PyObject *m_ptr;
};
}
#endif // PYTHONOBJECT_H
