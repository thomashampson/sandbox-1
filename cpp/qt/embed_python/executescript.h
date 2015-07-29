#ifndef EXCUTESCRIPT_H
#define EXCUTESCRIPT_H

#include <QRunnable>
#include <QString>

class Code;
class PythonInterpreter;

/**
 * Worker task for the asynchronous exec calls
 */
class ExecuteScript : public QRunnable {

public:
  ExecuteScript(PythonInterpreter &interpreter, const Code &source);

  void run();

private:
  PythonInterpreter &m_interp;
  QString m_src;
};

#endif // EXCUTESCRIPT_H
