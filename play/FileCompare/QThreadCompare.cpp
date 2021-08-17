#include "QThreadCompare.h"
#include "boolresult.h"
#include "common.h"
#include "Compare.h"
#include <QDebug>
#include <QMutexLocker>
#include <QCoreApplication>
#include <QTextStream>
QThreadCompare::QThreadCompare(QObject *parent)
    :QThread(parent)
{
    m_compare = QPointer<Compare>(new Compare(this));
    m_stop = false;
    m_start_compare = false;
    connect(m_compare, SIGNAL(finishCompareToThread(const QVariantList&)), this, SLOT(receiveBaseSlot(const QVariantList&)));
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
}

QThreadCompare::~QThreadCompare()
{
    OUT << u8"~QThread 所在线程 id: "<< QThread::currentThreadId();
#if 0
    if (m_compare)
    {
        delete m_compare;
        m_compare = 0;
    }
#endif
}

void QThreadCompare::run()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    while (1)
    {
        QTextStream(stdout) << "while";
        m_mutex.lock();
        if(m_start_compare)
        {
            OUT << tr("Thread start compare");
            compare();
        }
        if(m_stop)
        {
            m_mutex.unlock();
            break;
        }
        m_mutex.unlock();
        msleep(1000);
    }
    m_stop = false;
    OUT << u8"QThreadCompare 退出循环";
}

void QThreadCompare::compare()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    m_compare->compareStart(m_hash);
    m_start_compare = false;
    m_hash.clear();
}

void QThreadCompare::stopThread()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    QMutexLocker lock(&m_mutex);
    m_stop = true;
}

void QThreadCompare::editStartCompareSlot(const QVariantHash& hash)
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    QMutexLocker lock(&m_mutex);
    m_start_compare = true;
    m_hash = hash;
    m_hash.insert("isbool", true);
}

void QThreadCompare::startCompareSlot(const QVariantHash& hash)
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    QMutexLocker lock(&m_mutex);
    m_start_compare = true;
    m_hash = hash;
    m_hash.insert("isbool", true);
}

void QThreadCompare::receiveBaseSlot(const QVariantList& retlist)
{
    emit finish_compare_thread(retlist);
}

