#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "MplFigureCanvas.h"

// -----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
  : QMainWindow(parent, flags), m_ui(new Ui_MainWindow) {
  setCentralWidget(new Python::MplFigureCanvas(this));
}

// -----------------------------------------------------------------------------
//required in cpp file due to forward declaration of interface
MainWindow::~MainWindow() {
}
