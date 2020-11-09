#include "Runnable.h"
#include <QDebug>
#include <QThread>
#include <QMetaObject>
#include <QThreadPool>
Runnable::Runnable(QObject * parent):
    m_obj(parent),
    QRunnable()
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    m_base = new Base;
}

Runnable::~Runnable()
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    if (m_base)
    {
        delete m_base;
        m_base = nullptr;
    }
}

void Runnable::run()
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    //进行比较处理过程
    if (CompareRunable::instance()->giveDatahash().size() > 0)
    {
        m_base->compare(CompareRunable::instance()->giveDatahash());
    }
    if (0 != m_base->getData())
    {
        bool retvalue = false;
        QMetaObject::invokeMethod(m_obj, "getDataList", Q_RETURN_ARG(bool, retvalue),Q_ARG(QVariantList, *(m_base->getData())));
        if (!retvalue)
        {
            qDebug().noquote() << u8"王瑞亭错误";
        }
        else
        {
            qDebug().noquote() << u8"王瑞亭正确";
        }
        QThread::msleep(1000);
    }
}


CompareRunable::CompareRunable(QObject *parent):
    QObject(parent)
{
    m_runnable = new Runnable(this);
}

CompareRunable::~CompareRunable()
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
}

void CompareRunable::startCompareSlot(const QVariantHash& hash)
{
    qDebug().noquote() << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    m_hash = hash;
    m_hash.insert("isbool", true);
    if (m_hash.size() > 0)
    {
        emit sendMsg(u8"Runable线程启动");
        QThreadPool::globalInstance()->start(m_runnable);
    }
}

bool CompareRunable::getDataList(QVariantList list)
{
     m_ret_list = list;
     if (m_ret_list.size() > 0)
     {
         emit sendMsg(u8"Runable比较结束返回");
         emit returnRetList(list);
     }
//     return m_ret_list.size() > 0 ? true : false;
     return true;
}
