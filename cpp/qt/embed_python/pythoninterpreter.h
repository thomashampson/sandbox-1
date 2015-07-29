#ifndef PYTHONINTERPRETER_H
#define PYTHONINTERPRETER_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <QObject>


//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class Code;
#ifndef PyObject_HEAD
 struct _object;
 typedef _object PyObject;
#endif


class PythonInterpreter : public QObject
{
  Q_OBJECT

public:
  PythonInterpreter(QObject *parent = NULL);
  ~PythonInterpreter();

  ///@{
  ///@name High-level API
  void execute(const Code & code);
  void abort();
  void importMatplotlib() const;
  void saveThreadID(long tid);
  ///@}

  ///@{
  ///@name Low-level API
  PyObject *toByteCode(const char *src) const;
  PyObject *executeByteCode(PyObject *codeObject, PyObject *context = nullptr) const;
  void raiseKeyboardInterrupt() const;
  ///@}

signals:
  void abortScript();

private:
  PyObject *m_locals;
  long m_threadid;
};

#endif // PYTHONINTERPRETER_H
