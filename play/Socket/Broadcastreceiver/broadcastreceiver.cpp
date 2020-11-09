#include "broadcastreceiver.h"
#include <QUdpSocket>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

Broadcastreceiver::Broadcastreceiver(QWidget *parent):
    QWidget(parent)
{
    statusLabel = new QLabel(tr("Listening for broadcasted messages"), this);
    statusLabel->setWordWrap(true);
    resize(400, 400);
    quitButton = new QPushButton(tr("&Quit"));

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 45454, QUdpSocket::ShareAddress);

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
    setWindowTitle(tr("Broadcast Receiver"));
}

void Broadcastreceiver::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        statusLabel->setText(tr("Received datagram: \"%1\"")
                             .arg(datagram.data()));
    }
}
