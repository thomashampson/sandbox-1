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

  void sysPathAppend(const QString & path);
  /// Execute a lump of arbitrary code in the current environment
  void execute(const Code & code);

private:
  PyObject *m_locals;
};

#endif // PYTHONINTERPRETER_H
