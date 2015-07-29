#include "executescript.h"
#include "pythoninterpreter.h"
#include "code.h"
#include <Python.h>

ExecuteScript::ExecuteScript(PythonInterpreter &interpreter, const Code &source)
    : QRunnable(), m_interp(interpreter), m_src(source.str()) {}

void ExecuteScript::run() {
  auto gilstate = PyGILState_Ensure();
  m_interp.saveThreadID(PyThreadState_Get()->interp->tstate_head->thread_id);
  PyObject *codeObject = m_interp.toByteCode(m_src.toAscii().data());
  m_interp.executeByteCode(codeObject);
  if (PyErr_Occurred()) {
    PyErr_Print();
  }
  PyGILState_Release(gilstate);
}
