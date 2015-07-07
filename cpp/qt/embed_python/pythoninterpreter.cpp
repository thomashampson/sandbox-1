#include "pythoninterpreter.h"
#include "code.h"
#include <Python.h>

#include <QApplication>
#include <QRunnable>
#include <QtConcurrentRun>
#include <QThreadPool>

#include <iostream>

extern "C" {
extern PyThreadState *_PyThreadState_Current;

/// Returns 1 if
bool PyGILState_Check2() {
  PyThreadState *tstate = _PyThreadState_Current;
  return tstate && (tstate == PyGILState_GetThisThreadState());
}
}

namespace {

/// Handle to the threadstate of the thread that called PyInitialize()
PyThreadState *THREADSTATE_INIT = nullptr;

/**
 * Worker task for the asynchronous exec calls
 */
class ExecutePythonScript : public QRunnable {
public:
  ExecutePythonScript(const PythonInterpreter &interpreter, const Code &source)
      : QRunnable(), m_interp(interpreter), m_src(source.str()) {}

  void run() {
    std::cerr << "ExecutePythonScript::run()\n";
    std::cerr << "    This thread state on entry:  "
              << PyGILState_GetThisThreadState() << "\n";
    std::cerr << "    GIL on entry: " << PyGILState_Check2() << "\n";

    auto gilstate = PyGILState_Ensure();
    std::cerr << "    This thread state after acquire: "
              << PyGILState_GetThisThreadState() << "\n";
    std::cerr << "    GIL after acquire: " << PyGILState_Check2() << "\n";

    //    PyThreadState *tcur = (PyThreadState
    //    *)PyGILState_GetThisThreadState();
    //    int current(0);
    //    if (tcur == NULL) {
    //        /* Create a new thread state for this thread */
    //        tcur = PyThreadState_New(THREADSTATE_INIT->interp);
    //        current = 0; /* new thread state is never current */
    //    }
    //    else
    //        current = PyThreadState_IsCurrent(tcur);
    //    if (current == 0) {
    //        PyEval_RestoreThread(tcur);
    //    }

    PyObject *codeObject = m_interp.toByteCode(m_src.toAscii().data());
    PyObject *result = m_interp.executeByteCode(codeObject);
    if (!result) {
      PyErr_Clear();
    }

    PyGILState_Release(gilstate);
    std::cerr << "    This thread state after release: "
              << PyGILState_GetThisThreadState() << "\n";
    std::cerr << "    GIL after release: " << PyGILState_Check2() << "\n";
  }

private:
  const PythonInterpreter &m_interp;
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
  Py_Initialize();
  PyEval_InitThreads();
  THREADSTATE_INIT = PyGILState_GetThisThreadState();
  std::cerr << "PythonInterpreter starting. Main Thread state - "
            << THREADSTATE_INIT << "\n";

  // Store the main module as context for execution
  PyObject *mainModule = PyImport_AddModule("__main__");
  m_locals = PyDict_Copy(PyModule_GetDict(mainModule));

  // Set a null threadstate to ensure the acquire call doesn't deadlock
  // PyEval_SaveThread();
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
  // QThreadPool::globalInstance()->start(new ExecutePythonScript(*this, code));
  std::cerr << "PythonInterpreter::execute() - GIL: " << PyGILState_Check2()
            << "\n";

  PyThreadState *tstate = nullptr;
  if (PyGILState_Check2()) {
    tstate = PyEval_SaveThread();
  }
  ExecutePythonScript pythonScript(*this, code);
  auto future = QtConcurrent::run(pythonScript, &ExecutePythonScript::run);
  while (future.isRunning()) {
    QApplication::processEvents();
  }
  if (tstate) {
    PyEval_RestoreThread(tstate);
  }
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
 * @param codeObject A code object, usually the result of a Py_CompileString
 * call
 * @param context An optional Py_DICT type describing the current environment
 * context. If null
 * the default context of the main interpreter is used.
 */
PyObject *PythonInterpreter::executeByteCode(PyObject *codeObject,
                                             PyObject *context) const {
  if (!context)
    context = PyDict_Copy(m_locals);
  auto *result = PyEval_EvalCode((PyCodeObject *)codeObject, context, context);
  if (!context)
    Py_DECREF(context);
  return result;
}
