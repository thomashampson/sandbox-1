#include "MainWindow.h"
#include "MplPlot.h"
#include "ui_mainwindow.h"

// -----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
  : QMainWindow(parent, flags), m_ui(new Ui_MainWindow) {
  setCentralWidget(new MplPlot(this));
}

// -----------------------------------------------------------------------------
//required in cpp file due to forward declaration of interface
MainWindow::~MainWindow() {
}
