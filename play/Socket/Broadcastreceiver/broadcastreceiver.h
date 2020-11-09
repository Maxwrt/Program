#ifndef BROADCASTRECEIVER_H
#define BROADCASTRECEIVER_H

#include <QWidget>
#include <QObject>

class QLabel;
class QPushButton;
class QUdpSocket;
class QAction;
class Broadcastreceiver : public QWidget
{
    Q_OBJECT
public:
    Broadcastreceiver(QWidget *parent = 0);

private slots:
    void processPendingDatagrams();

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    QUdpSocket *udpSocket;
};

#endif // BROADCASTRECEIVER_H
