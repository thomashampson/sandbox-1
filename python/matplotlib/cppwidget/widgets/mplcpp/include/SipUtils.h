#ifndef SIPUTILS_H
#define SIPUTILS_H

#include "PythonObject.h"

namespace Python {
void *sipUnwrap(PyObject *obj_ptr);
}

#endif // SIPUTILS_H
