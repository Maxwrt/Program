#include "Receiver.h"
#include <QtWidgets>
#include <QtNetwork>
Receiver::Receiver(QWidget *parent):
    QDialog(parent)
{
    statusLabel = new QLabel(tr("Listening for multicasted messages"));
    quitButton = new QPushButton(tr("&Quit"));

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 45453, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(QHostAddress("239.255.43.21"));

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
 * udp单播(unicast)：单播只能是发送方往接收方指定的IP端口发送数据
 * udp组播(multicast)需要具备的条件：
 *                  1.接收方设置组播属性及组播号
 *                  2.发送方往接收方定义的组播地址发送数据包
 *                  3.服务器客户端端口号需要一致
 * 广播(broadcast)
 *
 * 使用UDP协议进行信息的传输之前不需要建立连接。换句话说就是客户端向服务器发送信息，客户端只需要给出服务器的ip地址和端口号，
 * 然后将信息封装到一个待发送的报文中并且发送出去。至于服务器端是否存在，或者能否收到该报文，客户端根本不用管。
 * 单播用于两个主机之间的端对端通信，广播用于一个主机对整个局域网上所有主机上的数据通信。单播和广播是两个极端，
 * 要么对一个主机进行通信，要么对整个局域网上的主机进行通信。实际情况下，经常需要对一组特定的主机进行通信，
 * 而不是整个局域网上的所有主机，这就是多播的用途。通常我们讨论的udp的程序都是一对一的单播程序。
 * 对于广播，网络中的所有主机都会接收一份数据副本。对于多播，消息只是发送到一个多播地址，网络知识将数据分发给哪些表示想要接收发送到该多播地址的数据的主机。
 * 只有UDP套接字允许广播或多播。广播UDP与单播UDP的区别就是IP地址不同，广播使用广播地址255.255.255.255，将消息发送到在同一广播网络上的每个主机。
 * 值得强调的是：本地广播信息是不会被路由器转发。当然这是十分容易理解的，因为如果路由器转发了广播信息，那么势必会引起网络瘫痪。这也是为什么IP协议的设计者故意没有定义互联网范围的广播机制。
 * 广播地址通常用于在网络游戏中处于同一本地网络的玩家之间交流状态信息等。
 * 其实广播顾名思义，就是想局域网内所有的人说话，但是广播还是要指明接收者的端口号的，因为不可能接受者的所有端口都来收听广播。
 */
