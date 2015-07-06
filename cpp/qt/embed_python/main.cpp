#include <QtCore>
#include <QtGui>

#include "mainwindow.h"

/* signal example */
#include <csignal>     /* signal, raise, sig_atomic_t */
#include <execinfo.h>     /* signal, raise, sig_atomic_t */
#include <iostream>

/**
 * Print a backtrace to stderr when a SIGSEGV is received
 */
void custom_signal_handler(int) {
  QStringList stacktrace;
  stacktrace.append("\n********* SEGMENTATION FAULT *********\n"
                    "BACKTRACE:\n");
  void *trace[32];
  int size = backtrace(trace,32);
  char **strings = backtrace_symbols(trace, size);
  for( int i = 0; i < size; i++ ){
    stacktrace.append(strings[i]);
  }
  stacktrace.append("\n**************************************\n\n");
  std::cerr << stacktrace.join("\n").toStdString();
  exit(-1);
}

int main(int argc, char *argv[])
{
  signal (SIGSEGV, custom_signal_handler);

  QApplication app(argc, argv);
  app.setOrganizationName("GlobalInc");
  app.setApplicationName("Embedded Python");
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
