#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include <QMainWindow>

#include <memory>

// ------------------------------------------------------------------------------
class Ui_MainWindow;

namespace Python {
class MplFigureCanvas;
}

// ------------------------------------------------------------------------------
class MainWindow : public QMainWindow {

  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
  ~MainWindow();

private:
  std::unique_ptr<Ui_MainWindow> m_ui;
  Python::MplFigureCanvas *m_plotCanvas;
};

#endif // MAINWINDOW_H_
