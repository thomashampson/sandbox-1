#include "pythoninterpreter.h"
#include "code.h"
#include "executescript.h"
#include <Python.h>

#include <QApplication>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>

#include <iostream>

namespace {

/// Handle to the threadstate of the thread that called PyInitialize()
PyThreadState *THREADSTATE_INIT = nullptr;
}

//-----------------------------------------------------------------------------
// Public
//-----------------------------------------------------------------------------

PythonInterpreter::PythonInterpreter(QObject *parent)
    : QObject(parent), m_locals(NULL), m_threadid(-1) {
  Py_Initialize();
  THREADSTATE_INIT = PyGILState_GetThisThreadState();

  // Store the main module as context for execution
  PyObject *mainModule = PyImport_AddModule("__main__");
  m_locals = PyDict_Copy(PyModule_GetDict(mainModule));

  // Lower the check interval for better response to cancellation
  // requests
  PyObject *sys = PyImport_ImportModule("sys");
  // Check for other threads every 5 ticks
  PyObject_CallMethod(sys, "setcheckinterval", "i", 5);
  Py_DECREF(sys);

  PyEval_InitThreads();
  // Set a null threadstate to ensure the acquire call doesn't deadlock
  PyEval_SaveThread();
}

/**
 * Calls Py_Finalize
 */
PythonInterpreter::~PythonInterpreter() {
  PyEval_RestoreThread(THREADSTATE_INIT);
  Py_DECREF(m_locals);
  Py_Finalize();
}

/**
 * Execute the code with the current interpreter environment in a separate
 * thread
 * @param code
 */
void PythonInterpreter::execute(const Code &code) {
  QThreadPool::globalInstance()->start(new ExecuteScript(*this, code));
}

/**
 * Abort the script that is executing
 */
void PythonInterpreter::abort() {
  auto gilstate = PyGILState_Ensure();
  raiseKeyboardInterrupt();
  PyGILState_Release(gilstate);
}

/**
 * Imports matplotlib
 */
void PythonInterpreter::importMatplotlib() const {
  PyImport_ImportModule("matplotlib");
  if (PyErr_Occurred()) {
    PyErr_Print();
  } else {
    std::cerr << "matplotlib imported successfully";
  }
}

void PythonInterpreter::saveThreadID(long tid) { m_threadid = tid; }

/**
 * Compiles the source code to Python byte code
 * @param src A c-string containing the Python source
 */
PyObject *PythonInterpreter::toByteCode(const char *src) const {
  // Simplest case: Code is a single expression
  return Py_CompileString(src, "", Py_file_input);
}

/**
 * Takes a Python bytcode object and executes it. Note: No check on the code
 * object is performed.
 * @param codeObject A code object, usually the result of a Py_CompileString
 * call
 * @param context An optional Py_DICT type describing the current environment
 * context. If null
 * the default context of the main interpreter is used.
 */
PyObject *PythonInterpreter::executeByteCode(PyObject *codeObject,
                                             PyObject *context) const {
  bool ownContext(context == NULL);
  if (!context)
    context = PyDict_Copy(m_locals);
  auto *result = PyEval_EvalCode((PyCodeObject *)codeObject, context, context);
  if (ownContext)
    Py_DECREF(context);
  return result;
}

/**
 * Sets the PythonError indicator
 * @return
 */
void PythonInterpreter::raiseKeyboardInterrupt() const {
  PyThreadState_SetAsyncExc(m_threadid, PyExc_KeyboardInterrupt);
}
