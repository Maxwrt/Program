#include "Receiver.h"
#include "common.h"
#include "ui_Receiver.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScrollBar>

Receiver::Receiver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Receiver)
{
    ui->setupUi(this);
    m_UdpReceiver = new QUdpSocket(this);
    m_UdpReceiver->bind(QHostAddress::AnyIPv4, 9999);
    ui->textEdit_history->installEventFilter(this);
    connect(m_UdpReceiver, &QUdpSocket::readyRead, this, [=](){DealReceiveMsg();});
    connect(ui->pushButtonSend, &QPushButton::clicked, this, [=]()->void
    {
        SendData();
    });
}

Receiver::~Receiver()
{
    delete ui;
}

void Receiver::DealReceiveMsg()
{
    if (m_UdpReceiver->hasPendingDatagrams())
    {
        QHostAddress peerIP;
        quint16 peerPort;
        char buf[1024];
        m_UdpReceiver->readDatagram(buf, sizeof(buf), &peerIP, &peerPort);
        if (!QString(buf).isEmpty())
        {
            bool downflag = false;
            QScrollBar *scrollbar = ui->textEdit_history->verticalScrollBar();
            if(scrollbar && scrollbar->value() == scrollbar->maximum())
                downflag=true;
            ui->textEdit_history->append(QString(buf));
            if(downflag)
                scrollbar->setValue(scrollbar->maximum());
        }
    }
}

void Receiver::SendData()
{
    QString peerIP = ui->lineEdit_ip->text();
    QString peerPort = ui->lineEdit_port->text();
    if (peerIP.isEmpty() || peerPort.isEmpty())
    {
        QMessageBox::information(this, u8"提示", u8"IP地址或端口为空", u8"确定");
        return;
    }

    if (!IsIP(peerIP))
    {
        QMessageBox::information(this, u8"提示", u8"IP地址格式不对", u8"确定");
        return;
    }

    QByteArray data = ui->textEdit_data->placeholderText().toLocal8Bit();
    if (!data.isEmpty())
    {
        m_UdpReceiver->writeDatagram(data, QHostAddress(peerIP), peerPort.toInt());
        ui->textEdit_data->clear();
    }
}

void Receiver::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    if (m_UdpReceiver->isOpen())
    {
        m_UdpReceiver->disconnectFromHost();
        m_UdpReceiver->close();
    }
    close();
}

bool Receiver::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->textEdit_history)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyevent = static_cast<QKeyEvent*>(event);
            if (keyevent->key() == Qt::Key_Enter)
            {
                SendData();
            }

            if (keyevent->key() == Qt::Key_Escape)
            {
                closeEvent(0);
            }
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}
