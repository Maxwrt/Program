#include "thread.h"
#include "boolresult.h"
#include <QDebug>
#include <QMutexLocker>
#include <QCoreApplication>

Thread::Thread(QObject *parent)
    :QThread(parent)
{
    m_base = new Base(this);
    m_stop = false;
    m_start_compare = false;
    connect(m_base, SIGNAL(finishCompareToThread(const QVariantList&)), this, SLOT(receiveBaseSlot(const QVariantList&)));
}

Thread::~Thread()
{
    qDebug().noquote() << u8"~QThread 所在线程 id:%1"<<QThread::currentThreadId();
}

void Thread::run()
{
    while (1)
    {
        if(m_stop)
        {
            break;
        }
        m_mutex.lock();
        if(m_start_compare)
        {
            qDebug().noquote() << tr("Thread start compare");
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
    qDebug().noquote() << tr("Thread run exit");
}

void Thread::compare()
{
    m_base->compare(m_hash);
    m_start_compare = false;
    m_hash.clear();
}

void Thread::stopThread()
{
    QMutexLocker lock(&m_mutex);
    m_stop = true;
}

void Thread::editStartCompareSlot(const QVariantHash& hash)
{
    QMutexLocker lock(&m_mutex);
    m_start_compare = true;
    m_hash = hash;
    m_hash.insert("isbool", true);
}

void Thread::startCompareSlot(const QVariantHash& hash)
{
    QMutexLocker lock(&m_mutex);
    m_start_compare = true;
    m_hash = hash;
    m_hash.insert("isbool", true);
}

void Thread::receiveBaseSlot(const QVariantList& retlist)
{
    qDebug().noquote()<<tr("Thread receive compare over signal");
    emit finish_compare_thread(retlist);
}

