/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef SENDER_H
#define SENDER_H

#include <QDialog>
#include <QUdpSocket>
#include <QCloseEvent>

namespace Ui {
class Sender;
}

class Sender : public QDialog
{
    Q_OBJECT

public:
    explicit Sender(QWidget *parent = 0);
    ~Sender();

private slots:
    void DealReceiveMsg();
    void SendData();

protected:
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::Sender *ui;
    QUdpSocket *m_UdpSender;
};

#endif // SENDER_H
