#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("GlobalInc");
    app.setApplicationName("Embedded Python");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
