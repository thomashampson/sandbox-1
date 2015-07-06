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
  void execute(const Code & code) const;
  void sysPathAppend(const QString & path) const;
  ///@}

  ///@{
  ///@name Low-level API
  PyObject *toByteCode(const char *src) const;
  PyObject *executeByteCode(PyObject *codeObject, PyObject *context = nullptr) const;
  ///@}

private:
  PyObject *m_locals;
};

#endif // PYTHONINTERPRETER_H
