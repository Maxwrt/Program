#include <QApplication>
#include "broadcastsender.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Broadcastsender broadcastsender;
    broadcastsender.show();
    return a.exec();
}
