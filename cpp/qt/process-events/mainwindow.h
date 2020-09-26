#include <QMainWindow>
#include <QRunnable>

/// Worker
class Worker : public QObject,
               public QRunnable {
Q_OBJECT

public:
  void run() override;

signals:
  void display();
};


class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

private slots:
  void run();
  void display();
};
