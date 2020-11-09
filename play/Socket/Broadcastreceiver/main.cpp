#include <QApplication>
#include "broadcastreceiver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Broadcastreceiver broadcastreceiver;
    broadcastreceiver.show();
    return a.exec();
}
