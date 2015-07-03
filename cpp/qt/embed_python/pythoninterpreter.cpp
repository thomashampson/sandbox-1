#include "pythoninterpreter.h"
#include "code.h"
#include <Python.h>

#include <QRunnable>
#include <QThreadPool>

#include <iostream>

namespace {
PyObject *toByteCode(const char *src) {
  // Simplest case: Code is a single expression
  return Py_CompileString(src, "", Py_file_input);
}

/**
 * Worker task for the asynchronous exec calls
 */
class ExecutePythonScript : public QRunnable {
public:
  ExecutePythonScript(const Code &source, PyObject *locals)
      : QRunnable(), m_src(source.str()), m_locals(locals) {}

  void run() {
    std::cerr << "ExecutePythonScript::run() - In thread " << QThread::currentThread() << "\n";
    PyGILState_STATE state = PyGILState_Ensure();
    std::cerr << "Current Python threadstate " << PyThreadState_Get() << "\n";
    
    PyObject *codeObject = toByteCode(m_src.toAscii().data());
    PyObject *result(NULL);
    if (codeObject) {

      result = PyEval_EvalCode((PyCodeObject *)codeObject, m_locals, m_locals);
    }
    if (!result) {
      PyErr_Clear();
    }
    
    PyGILState_Release(state);
  }

private:
  QString m_src;
  PyObject *m_locals;
};
}

//-----------------------------------------------------------------------------
// Public
//-----------------------------------------------------------------------------

/**
 * Calls Py_Initialize if Py_Initialized returns false
 */
PythonInterpreter::PythonInterpreter(QObject *parent)
    : QObject(parent), m_locals(NULL) {
  if (Py_IsInitialized() == 0) {
    Py_Initialize();
    PyEval_InitThreads();
    std::cerr << "Current Python threadstate " << PyThreadState_Get() << "\n";


    PyObject *mainModule = PyImport_AddModule("__main__");
    m_locals = PyDict_Copy(PyModule_GetDict(mainModule));
    PyEval_SaveThread();
    //std::cerr << "Current Python threadstate " << PyThreadState_Get() << "\n";
  }
}

/**
 * Calls Py_Finalize
 */
PythonInterpreter::~PythonInterpreter() {
  Py_DECREF(m_locals);
  Py_Finalize();
}

/**
 * Update the sys.path attribute if the string is not empty and is not already
 * present.
 * Note the path does not have to exist
 * @param path Directory to add to sys.path
 */
void PythonInterpreter::sysPathAppend(const QString &path) {
  if (path.isEmpty())
    return;
  QString code = "import sys\n"
                 "if '%1' not in sys.path:\n"
                 "    sys.path.append('%1')\n"
                 "print sys.path";
  code = code.arg(path);
  // This intentionally does not use ::execute() to simulate interactions
  // with execute() & the raw Python API by an external library
  PyRun_SimpleString(code.toAscii().data());
}

/**
 * Execute the code with the current interpreter environment in a separate
 * thread
 * @param code
 */
void PythonInterpreter::execute(const Code &code) {
  std::cerr << "PythonInterpreter::execute - In thread " << QThread::currentThread() << "\n";
  QThreadPool::globalInstance()->start(new ExecutePythonScript(code, m_locals));
}
