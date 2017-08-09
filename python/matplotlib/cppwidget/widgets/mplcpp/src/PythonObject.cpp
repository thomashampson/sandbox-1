#include "PythonObject.h"
#include "PythonErrors.h"

#include <sstream>

namespace Python {

//-----------------------------------------------------------------------------
// PythonObject
//----------------------------------------------------------------------------

/**
 * @param name Name of the attribute
 * @return The object defining this attribute
 * @throws
 */
Python::PythonObject Python::PythonObject::getAttr(const char *name) const {
  auto objPtr = PyObject_GetAttrString(m_ptr, name);
  if (objPtr)
    return PythonObject(NewRef(objPtr));
  else {
    throw PythonError(errorToString());
  }
}

//-----------------------------------------------------------------------------
// Utilities
//----------------------------------------------------------------------------
/**
 * Import a module and return a new reference
 * @param name The name of the module
 * @return A PythonObject referencing the module
 * @throws PythonError if the module cannot be imported
 */
PythonObject importModule(const char *name) {
  auto objPtr = PyImport_ImportModule(name);
  if (!objPtr)
    throw PythonError(errorToString());
  return PythonObject(NewRef(objPtr));
}

/**
 * Retrieve an attribute from a module
 * @param moduleName The name of the module containing the attribute
 * @param attrName The name of the attribute
 * @return A PythonObject referencing the attribute
 * @throws PythonError if an error occurred
 */
PythonObject getAttrOnModule(const char *moduleName, const char *attrName) {
  auto module = importModule(moduleName);
  return module.getAttr(attrName);
}
}
