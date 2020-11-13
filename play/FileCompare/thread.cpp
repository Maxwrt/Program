#include "thread.h"
#include "boolresult.h"
#include <QDebug>
#include <QMutexLocker>
#include <QCoreApplication>
#include <QTextStream>
Thread::Thread(QObject *parent)
    :QThread(parent)
{
    m_base = QPointer<Base>(new Base(this));
    m_stop = false;
    m_start_compare = false;
    connect(m_base, SIGNAL(finishCompareToThread(const QVariantList&)), this, SLOT(receiveBaseSlot(const QVariantList&)));
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
}

Thread::~Thread()
{
    qDebug().noquote() << u8"~QThread 所在线程 id: "<< QThread::currentThreadId();
    if (m_base)
    {
        delete m_base;
        m_base = nullptr;
    }
}

void Thread::run()
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    while (1)
    {
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
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    m_base->compare(m_hash);
    m_start_compare = false;
    m_hash.clear();
}

void Thread::stopThread()
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    QMutexLocker lock(&m_mutex);
    m_stop = true;
}

void Thread::editStartCompareSlot(const QVariantHash& hash)
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    QMutexLocker lock(&m_mutex);
    m_start_compare = true;
    m_hash = hash;
    m_hash.insert("isbool", true);
}

void Thread::startCompareSlot(const QVariantHash& hash)
{
    emit sendMsg(u8"Thread线程启动");
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    QMutexLocker lock(&m_mutex);
    m_start_compare = true;
    m_hash = hash;
    m_hash.insert("isbool", true);
}

void Thread::receiveBaseSlot(const QVariantList& retlist)
{
    emit sendMsg(u8"Thread线程比较返回");
    qDebug().noquote()<<tr("Thread receive compare over signal");
    emit finish_compare_thread(retlist);
}

