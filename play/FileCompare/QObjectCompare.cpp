#include "QObjectCompare.h"
#include "Compare.h"
#include "common.h"
#include "boolresult.h"
#include <QThread>

QObjectCompare::QObjectCompare()
    :QObject(0)
{
    m_compare = QPointer<Compare>(new Compare(this));
    connect(m_compare, SIGNAL(finishCompare(const QVariantList& )), this, SLOT(finishCompareSlot(const QVariantList&)));
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
}

QObjectCompare::~QObjectCompare()
{
    OUT << u8"~QObjectCompare �����߳� id: "<< QThread::currentThreadId();
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
    OUT << "file:    " << __FILEW__ << " function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    emit sendMsg(u8"QObjectCompare�̱߳ȽϷ���");
    emit finishCompareSignal(retlist);
}
