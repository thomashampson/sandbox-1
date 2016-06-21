#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include <QMainWindow>

#include <memory>

// ------------------------------------------------------------------------------
class Ui_MainWindow;

// ------------------------------------------------------------------------------
class MainWindow : public QMainWindow {

Q_OBJECT

public:
  MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
  ~MainWindow();

private:
  std::unique_ptr<Ui_MainWindow> m_ui;
};

#endif //MAINWINDOW_H_
