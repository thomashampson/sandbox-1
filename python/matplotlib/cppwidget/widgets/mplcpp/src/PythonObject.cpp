#include "PythonObject.h"

namespace Python {

/**
 * @param name Name of the attribute
 * @return The object defining this attribute
 * @throws
 */
Python::PythonObject Python::PythonObject::getAttr(const char *name) const {
  auto objPtr = PyObject_GetAttrString(m_ptr, name);
  if (objPtr)
    return PythonObject(NewRef(objPtr));
  else
    throw AttributeNotFoundError(std::string("Unknown attribute ") + name);
}
}
