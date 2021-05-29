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
 * udp����(unicast)������ֻ���Ƿ��ͷ������շ�ָ����IP�˿ڷ�������
 * udp�鲥(multicast)��Ҫ�߱���������
 *                  1.���շ������鲥���Լ��鲥��
 *                  2.���ͷ������շ�������鲥��ַ�������ݰ�
 *                  3.�������ͻ��˶˿ں���Ҫһ��
 * �㲥(broadcast)
 *
 * ʹ��UDPЭ�������Ϣ�Ĵ���֮ǰ����Ҫ�������ӡ����仰˵���ǿͻ����������������Ϣ���ͻ���ֻ��Ҫ������������ip��ַ�Ͷ˿ںţ�
 * Ȼ����Ϣ��װ��һ�������͵ı����в��ҷ��ͳ�ȥ�����ڷ��������Ƿ���ڣ������ܷ��յ��ñ��ģ��ͻ��˸������ùܡ�
 * ����������������֮��Ķ˶Զ�ͨ�ţ��㲥����һ�����������������������������ϵ�����ͨ�š������͹㲥���������ˣ�
 * Ҫô��һ����������ͨ�ţ�Ҫô�������������ϵ���������ͨ�š�ʵ������£�������Ҫ��һ���ض�����������ͨ�ţ�
 * �����������������ϵ���������������Ƕಥ����;��ͨ���������۵�udp�ĳ�����һ��һ�ĵ�������
 * ���ڹ㲥�������е����������������һ�����ݸ��������ڶಥ����Ϣֻ�Ƿ��͵�һ���ಥ��ַ������֪ʶ�����ݷַ�����Щ��ʾ��Ҫ���շ��͵��öಥ��ַ�����ݵ�������
 * ֻ��UDP�׽�������㲥��ಥ���㲥UDP�뵥��UDP���������IP��ַ��ͬ���㲥ʹ�ù㲥��ַ255.255.255.255������Ϣ���͵���ͬһ�㲥�����ϵ�ÿ��������
 * ֵ��ǿ�����ǣ����ع㲥��Ϣ�ǲ��ᱻ·����ת������Ȼ����ʮ���������ģ���Ϊ���·����ת���˹㲥��Ϣ����ô�Ʊػ���������̱������Ҳ��ΪʲôIPЭ�������߹���û�ж��廥������Χ�Ĺ㲥���ơ�
 * �㲥��ַͨ��������������Ϸ�д���ͬһ������������֮�佻��״̬��Ϣ�ȡ�
 * ��ʵ�㲥����˼�壬����������������е���˵�������ǹ㲥����Ҫָ�������ߵĶ˿ںŵģ���Ϊ�����ܽ����ߵ����ж˿ڶ��������㲥��
 */
