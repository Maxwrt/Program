#ifndef BROADCASTSENDER_H
#define BROADCASTSENDER_H

#include <QWidget>
#include <QObject>
class QDialogButtonBox;
class QLabel;
class QPushButton;
class QTimer;
class QUdpSocket;
class Broadcastsender : public QWidget
{
    Q_OBJECT
public:
    Broadcastsender(QWidget * parent = 0);

private slots:
    void startBroadCasting();
    void broadCastDatagram();

private:
    QLabel *statusLabel;
    QPushButton *startButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QUdpSocket *udpSocket;
    QTimer *timer;
    int messageNo;
};

#endif // BROADCASTSENDER_H
