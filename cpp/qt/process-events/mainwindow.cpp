#include "mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>

/// Worker
void Worker::run() {
  qDebug() << "Run thread: " << QThread::currentThread();
  emit display();
}

/// Constructor
MainWindow::MainWindow() {
  auto button = new QPushButton("Run");
  setCentralWidget(button);
  connect(button, &QPushButton::clicked,
          this, &MainWindow::run);
};


// Run slot
void MainWindow::run() {
  auto worker = new Worker;
  connect(worker, &Worker::display,
          this, &MainWindow::display);
  QThreadPool::globalInstance()->start(worker);
}


void MainWindow::display() {
  qDebug() << "Display thread: " << QThread::currentThread();
}
