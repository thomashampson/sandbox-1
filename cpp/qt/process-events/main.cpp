/*
 * Demo project to explore processEvents impl
 * in the presence of multiple threads
 */
#include <QApplication>
#include <QDebug>
#include <QThread>
#include "mainwindow.h"


int main(int argc, char **argv) {
  QApplication app(argc, argv);
  qDebug() << "Application thread: " << QThread::currentThread();
  MainWindow topWindow;
  topWindow.show();
  return app.exec();
}
