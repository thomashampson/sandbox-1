#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "MplFigureCanvas.h"

// -----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), m_ui(new Ui_MainWindow),
      m_plotCanvas(new Python::MplFigureCanvas(111, this)) {
  setCentralWidget(m_plotCanvas);

  std::vector<double> x(10, 5.0);
  auto axes = m_plotCanvas->axes();
  axes.plot(x, x, "ro");
  m_plotCanvas->draw();
}

// -----------------------------------------------------------------------------
// required in cpp file due to forward declaration of interface
MainWindow::~MainWindow() {}
