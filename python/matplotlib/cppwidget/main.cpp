#include "Python.h"
#include "MainWindow.h"

#include <QApplication>

int main(int argc, char** argv) {
  Py_SetProgramName(argv[0]);
  Py_Initialize();
  QApplication app(argc, argv);
  MainWindow mainwindow;
  mainwindow.show();
  int status = app.exec();
  Py_Finalize();
  return status;
}
