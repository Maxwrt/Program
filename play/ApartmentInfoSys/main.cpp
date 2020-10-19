#include "mainwindow.h"
#include "base.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(Base::log);
    MainWindow w;
    w.showWindow();

    return a.exec();
}
