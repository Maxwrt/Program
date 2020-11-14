#include "QRunnableCompare.h"
#include "common.h"
#include "Compare.h"
#include "boolresult.h"
#include <QDebug>
#include <QThread>
#include <QMetaObject>
#include <QThreadPool>

Runnable::Runnable(QObject * parent):
    m_obj(parent),
    QRunnable()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    m_compare = QPointer<Compare>(new Compare);
}

Runnable::~Runnable()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    if (m_compare)
    {
        delete m_compare;
        m_compare = 0;
    }
}

void Runnable::run()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();

    //进行比较处理过程
    if (QRunnableCompare::instance()->giveDatahash().size() > 0)
    {
        m_compare->compareStart(QRunnableCompare::instance()->giveDatahash());
    }
    if (0 != m_compare->getData())
    {
        bool retvalue = false;
        QMetaObject::invokeMethod(m_obj, "getDataList", Q_RETURN_ARG(bool, retvalue),Q_ARG(QVariantList, *(m_compare->getData())));
        if (!retvalue)
        {
            OUT << u8"王瑞亭错误";
        }
        else
        {
            OUT << u8"王瑞亭正确";
        }
        QThread::msleep(1000);
    }
}


QRunnableCompare::QRunnableCompare(QObject *parent):
    QObject(parent)
{
    m_runnable = new Runnable(this);
}

QRunnableCompare::~QRunnableCompare()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
}

void QRunnableCompare::startCompareSlot(const QVariantHash& hash)
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    m_hash = hash;
    m_hash.insert("isbool", true);
    if (m_hash.size() > 0)
    {
        emit sendMsg(u8"Runable线程启动");
        QThreadPool::globalInstance()->start(m_runnable);
    }
}

bool QRunnableCompare::getDataList(QVariantList list)
{
     m_ret_list = list;
     if (m_ret_list.size() > 0)
     {
         emit sendMsg(u8"Runable比较结束返回");
         emit returnRetList(list);
     }
     return m_ret_list.size() > 0 ? true : false;
}
