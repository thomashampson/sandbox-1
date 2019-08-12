#include <QApplication>
#include <QIcon>
#include <QPainter>
#include <QPushButton>
#include <QtDebug>

class MyButton : public QPushButton {
public:
  MyButton() : QPushButton() {}
  MyButton(QIcon icon, QWidget *parent = nullptr) : QPushButton(parent), m_icon(icon) {
  }

  void paintEvent(QPaintEvent *e) {
    QPushButton::paintEvent(e);
    QPainter painter(this);
    m_icon.paint(&painter, 0, 0, 64, 64);
  }

private:
  QIcon m_icon;
};


int main(int argc, char** argv) {
  if(argc != 2) {
    qCritical() << "Usage: " << argv[0] << " filename";
    return 1;
  }
  QApplication app(argc, argv);

  QIcon buttonIcon(argv[1]);

  MyButton exit(buttonIcon);
  exit.connect(&exit, &QPushButton::clicked, &app, &QApplication::exit);
  exit.show();

  return app.exec();
}
