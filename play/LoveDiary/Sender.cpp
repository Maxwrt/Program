#include "Sender.h"
#include "common.h"
#include "ui_Sender.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QScrollBar>

Sender::Sender(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sender)
{
    ui->setupUi(this);
    m_UdpSender = new QUdpSocket(this);
    m_UdpSender->bind(QHostAddress::Any, 8888);
    ui->textEdit_history->installEventFilter(this);
    connect(m_UdpSender, &QUdpSocket::readyRead, this, [=](){DealReceiveMsg();});
    connect(ui->pushButtonSend, &QPushButton::clicked, this, [=]()->void
    {
        SendData();
    });
}

Sender::~Sender()
{
    delete ui;
}

void Sender::DealReceiveMsg()
{
    if (m_UdpSender->hasPendingDatagrams())
    {
        QHostAddress peerIP;
        quint16 peerPort;
        char buf[1024];
        m_UdpSender->readDatagram(buf, sizeof(buf), &peerIP, &peerPort);
        if (!QString(buf).isEmpty())
        {
            bool downflag = false;
            QScrollBar *scrollbar = ui->textEdit_history->verticalScrollBar();
            if(scrollbar && scrollbar->value()==scrollbar->maximum())
                downflag=true;
            ui->textEdit_history->append(QString(buf));
            if(downflag)
                scrollbar->setValue(scrollbar->maximum());
        }
    }
}

void Sender::SendData()
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
        m_UdpSender->writeDatagram(data, QHostAddress(peerIP), peerPort.toInt());
        ui->textEdit_data->clear();
    }
}

void Sender::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    if (m_UdpSender->isOpen())
    {
        m_UdpSender->disconnectFromHost();
        m_UdpSender->close();
    }
    close();
}

bool Sender::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->textEdit_history)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyevent = static_cast<QKeyEvent*>(event);
            if (keyevent->key() == Qt::Key_Enter)
            {
                SendData();
                return true;
            }
            if (keyevent->key() == Qt::Key_Escape)
            {
                closeEvent(0);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

