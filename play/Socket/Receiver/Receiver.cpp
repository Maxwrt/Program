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
 * udp����(unicast)������ֻ���Ƿ��ͷ������շ�ָ����IP�˿ڷ�������
 * udp�鲥(multicast)��Ҫ�߱���������1.���շ������鲥���Լ��鲥��  2 ���ͷ������շ�������鲥��ַ�������ݰ�
 *                  3.�������ͻ��˶˿ں���Ҫһ��
 * �㲥(broadcast)
 *
 */
