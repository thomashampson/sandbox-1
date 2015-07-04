#include <QtCore>
#include <QtGui>

#include "mainwindow.h"

/* signal example */
#include <csignal>     /* signal, raise, sig_atomic_t */
#include <execinfo.h>     /* signal, raise, sig_atomic_t */

void custom_signal_handler(int sig) {
  QStringList stacktrace;
  stacktrace.append("\n********* SEGMENTATION FAULT *********\n"
                    "BACKTRACE:\n");
  void *trace[32];
  size_t size = backtrace( trace, 32 );
  char **strings = backtrace_symbols( trace, size );
  for( size_t i = 0; i < size; i++ ){
    stacktrace.append(strings[i]);
  }
  stacktrace.append("\n**************************************\n\n");
  QMessageBox::critical(NULL, "Python Interpreter",
                        stacktrace.join("\n"));
  exit(-1);
}

int main(int argc, char *argv[])
{
  void (*prev_handler)(int);
  prev_handler = signal (SIGSEGV, custom_signal_handler);

  QApplication app(argc, argv);
  app.setOrganizationName("GlobalInc");
  app.setApplicationName("Embedded Python");
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
