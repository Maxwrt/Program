#include "compare.h"
#include <QDebug>
#include <QThread>
Compare::Compare(QObject *parent)
    :QObject(parent)
{
    m_base = QPointer<Base>(new Base(this));
    connect(m_base, SIGNAL(finishCompare(const QVariantList& )), this, SLOT(finishCompareSlot(const QVariantList&)));
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
}

Compare::~Compare()
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    if (m_base)
    {
        qDebug().noquote() << QString::fromLocal8Bit("��~Compare���ͷ�m_base");
        delete m_base;
        if (nullptr == m_base)
        {
            qDebug().noquote() << QString::fromLocal8Bit("m_base�Ѿ���QPointer��0");
        }
//        m_base = nullptr; QPointer ���m_base��0
    }
}

void Compare::compareSlot(const QVariantHash& hash)
{
    emit sendMsg(u8"Compare�߳�����");
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    m_mutex.lock();
    m_base->compare(hash);
    m_mutex.unlock();
}

void Compare::finishCompareSlot(const QVariantList& retlist)
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    qDebug().noquote()<<tr("Compare receive compare over signal");
    emit finishCompareSignal(retlist);
    emit sendMsg(u8"Compare�̱߳ȽϷ���");
}
