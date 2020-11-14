#include "QObjectCompare.h"
#include "Compare.h"
#include "common.h"
#include "boolresult.h"
#include <QThread>

QObjectCompare::QObjectCompare(QObject *parent)
    :QObject(parent)
{
    m_compare = QPointer<Compare>(new Compare(this));
    connect(m_compare, SIGNAL(finishCompare(const QVariantList& )), this, SLOT(finishCompareSlot(const QVariantList&)));
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
}

QObjectCompare::~QObjectCompare()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    if (m_compare)
    {
        OUT << QString::fromLocal8Bit("在~Compare中释放m_compare");
        delete m_compare;
        if (0 == m_compare)
        {
            OUT << QString::fromLocal8Bit("m_compare已经被QPointer置0");
        }
    }
}

void QObjectCompare::compareSlot(const QVariantHash& hash)
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    m_mutex.lock();
    m_compare->compareStart(hash);
    m_mutex.unlock();
}

void QObjectCompare::finishCompareSlot(const QVariantList& retlist)
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    emit sendMsg(u8"QObjectCompare线程比较返回");
    emit finishCompareSignal(retlist);
}
