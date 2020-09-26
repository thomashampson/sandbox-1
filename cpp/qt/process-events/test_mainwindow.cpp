<<<<<<< HEAD
#include "test_mainwindow.h"
#include "mainwindow.h"

#include <QtTest/QtTest>

void TestMainWindow::run() {
  MainWindow mainwindow;
  QTest::mouseClick(mainwindow.centralWidget(), Qt::LeftButton);
}

QTEST_MAIN(TestMainWindow)
//#include "testqstring.moc"
||||||| constructed merge base
=======
#include "test_mainwindow.h"
#include "mainwindow.h"

#include <QtTest/QtTest>

void TestMainWindow::run() {
  MainWindow mainwindow;
  QTest::mouseClick(mainwindow.centralWidget(), Qt::LeftButton);
}

QTEST_MAIN(TestMainWindow)
>>>>>>> Add Qt example running async signal call
