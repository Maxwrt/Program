#ifndef RECEIVER_H
#define RECEIVER_H

#include <QDialog>
#include <QUdpSocket>

namespace Ui {
class Receiver;
}

class Receiver : public QDialog
{
    Q_OBJECT

public:
    explicit Receiver(QWidget *parent = 0);
    ~Receiver();

private slots:
    void DealReceiveMsg();
    void SendData();

protected:
    void closeEvent(QCloseEvent *event = 0);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::Receiver *ui;
    QUdpSocket *m_UdpReceiver;
};

#endif // RECEIVER_H
