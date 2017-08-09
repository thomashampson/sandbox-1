#include "MainWindow.h"

#include <QApplication>

int main(int argc, char** argv) {
  // Initialize Python
  //Py_SetProgramName(argv[0]);

  QApplication app(argc, argv);
  MainWindow mainwindow;
  mainwindow.show();

  int status = app.exec();

  return status;
}
