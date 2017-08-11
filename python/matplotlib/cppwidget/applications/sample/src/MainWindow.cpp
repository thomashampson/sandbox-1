#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "MplPlotWidget.h"

// -----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), m_ui(new Ui_MainWindow),
      m_mplPlot(new Python::MplPlotWidget(211, this)) {
  setCentralWidget(m_mplPlot);

  std::vector<double> x(10);
  double value(0.0);

  std::generate_n(std::begin(x), 10, [&value]() { return value++; });
  m_mplPlot->plot(x, x, "r-");
  value = 0.0;


  m_mplPlot->addSubPlot(212);
  std::generate_n(std::begin(x), 10, [&value]() { return 2 + value++; });
  m_mplPlot->plot(x, x, "bo");

//  m_mplPlot->draw();
}

// -----------------------------------------------------------------------------
// required in cpp file due to forward declaration of interface
MainWindow::~MainWindow() {}
