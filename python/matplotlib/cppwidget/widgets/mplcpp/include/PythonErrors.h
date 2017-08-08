#ifndef PYTHONERRORS_H
#define PYTHONERRORS_H

#include <stdexcept>

namespace Python {

//-----------------------------------------------------------------------------
// Exceptions
//-----------------------------------------------------------------------------
/**
 * @brief The PythonError class
 *
 * A custom exception type to indicate a python error occurred.
 */
class PythonError : public std::exception {
public:
  explicit PythonError(std::string msg) : m_msg(msg) {}
  const char *what() const noexcept override { return m_msg.c_str(); }

private:
  std::string m_msg;
};

//-----------------------------------------------------------------------------
// Error Handling Utilities
//-----------------------------------------------------------------------------
/// Convert the current error indicator to a string and clear it
std::string errorToString();
}
#endif // PYTHONERRORS_H
