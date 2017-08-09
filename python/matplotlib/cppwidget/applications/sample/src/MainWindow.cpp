#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "MplFigureCanvas.h"

// -----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), m_ui(new Ui_MainWindow),
      m_plotCanvas(new Python::MplFigureCanvas(111, this)) {
  setCentralWidget(m_plotCanvas);

  std::vector<double> x(10);
  double value(0.0);
  std::generate_n(std::begin(x), 10, [&value]() { return value++; });
  auto axes = m_plotCanvas->axes();
  axes.plot(x, x, "r-");
  value = 0.0;
  std::generate_n(std::begin(x), 10, [&value]() { return 2 + value++; });
  axes.plot(x, x, "bo");
  m_plotCanvas->draw();
}

// -----------------------------------------------------------------------------
// required in cpp file due to forward declaration of interface
MainWindow::~MainWindow() {}
