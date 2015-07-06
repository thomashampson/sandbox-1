#include "pythoninterpreter.h"
#include "code.h"
#include <Python.h>

#include <QRunnable>
#include <QThreadPool>

#include <iostream>

namespace {

/**
 * Worker task for the asynchronous exec calls
 */
class ExecutePythonScript : public QRunnable {
public:
  ExecutePythonScript(const PythonInterpreter &interpreter, const Code &source)
    : QRunnable(), m_interp(interpreter), m_src(source.str()) {}

  void run() {
    std::cerr << "ExecutePythonScript::run() - In thread " << QThread::currentThread() << "\n";
    auto *pythreadState = PyThreadState_New(PyInterpreterState_Head());
    PyEval_AcquireThread(pythreadState);

    std::cerr << "Current Python threadstate " << PyThreadState_Get() << "\n";
    PyObject *codeObject = m_interp.toByteCode(m_src.toAscii().data());
    PyObject *result = m_interp.executeByteCode(codeObject);
    if (!result) {
      PyErr_Clear();
    }

    PyEval_ReleaseThread(pythreadState);
  }

private:
  const PythonInterpreter & m_interp;
  QString m_src;
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
 * Execute the code with the current interpreter environment in a separate
 * thread
 * @param code
 */
void PythonInterpreter::execute(const Code &code) const {
  std::cerr << "PythonInterpreter::execute - In thread " << QThread::currentThread() << "\n";
  QThreadPool::globalInstance()->start(new ExecutePythonScript(*this, code));
}

/**
 * Update the sys.path attribute if the string is not empty and is not already
 * present.
 * Note the path does not have to exist
 * @param path Directory to add to sys.path
 */
void PythonInterpreter::sysPathAppend(const QString &path) const {
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
 * @param codeObject A code object, usually the result of a Py_CompileString call
 * @param context An optional Py_DICT type describing the current environment context. If null
 * the default context of the main interpreter is used.
 */
PyObject *PythonInterpreter::executeByteCode(PyObject *codeObject, PyObject *context) const {
  if(!context) context = m_locals;
  return PyEval_EvalCode((PyCodeObject *)codeObject, context, context);
}
