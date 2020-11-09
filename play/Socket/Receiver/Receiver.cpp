#include "Receiver.h"
#include <QtWidgets>
#include <QtNetwork>
Receiver::Receiver(QWidget *parent):
    QDialog(parent)
{
    groupAddress = QHostAddress("239.255.43.21");

    statusLabel = new QLabel(tr("Listening for multicasted messages"));
    quitButton = new QPushButton(tr("&Quit"));

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 45453, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Multicast Receiver"));
}

void Receiver::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        statusLabel->setText(tr("Receiver datagram:\"%1\"").arg(datagram.data()));
    }
}

/**
 * udp单播(unicast)：单播只能是发送方往接收放指定的IP端口发送数据
 * udp组播(multicast)需要具备的条件：1.接收方设置组播属性及组播号  2 发送方往接收方定义的组播地址发送数据包
 *                  3.服务器客户端端口号需要一致
 * 广播(broadcast)
 *
 */
