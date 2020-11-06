#include <QApplication>
#include "Receiver.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Receiver receiver;
    receiver.show();
    return a.exec();
}
