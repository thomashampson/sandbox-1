#include "PythonObject.h"
#include "PythonErrors.h"

namespace Python {

/**
 * Turn the current global error indicator into a string. If there is
 * no error then an empty string is returned. The error indicator
 * is cleared.
 * @return A string representation of the current error
 */
std::string errorToString() {
  std::string error;
  auto exception = PyErr_Occurred();
  if (!exception)
    return error;
  auto str = PyObject_Str(exception);
  if (!str)
    error = "An error occurred while checking the error state!";
  else {
    error = PyString_AsString(str);
    detail::decref(str);
  }
  PyErr_Clear();
  return error;
}
}
