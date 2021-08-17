#include "QRunnableCompare.h"
#include "common.h"
#include "Compare.h"
#include "boolresult.h"
#include <QDebug>
#include <QThread>
#include <QMetaObject>
#include <QThreadPool>
#include <QTextStream>

Runnable::Runnable(QObject * parent):
    m_obj(parent),
    QRunnable()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    m_compare = QPointer<Compare>(new Compare(0));
}

Runnable::~Runnable()
{
    QTextStream(stdout) << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
#if 1
    if (m_compare)
    {
        delete m_compare;
    }
#endif
}

void Runnable::run()
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();

    //进行比较处理过程
    QMutexLocker ml(&m_mutex);
    if (QRunnableCompare::instance()->giveDatahash().size() > 0)
    {
        m_compare->compareStart(QRunnableCompare::instance()->giveDatahash());
    }

    if (0 != m_compare->getData())
    {
        QVariantList datalist = *(m_compare->getData());
        QMetaObject::invokeMethod(m_obj, "getDataList", Qt::QueuedConnection, Q_ARG(QVariantList, datalist));
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
    QTextStream(stdout) << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
}

void QRunnableCompare::startCompareSlot(const QVariantHash& hash)
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    QMutexLocker ml(&m_mutex);
    m_hash = hash;
    m_hash.insert("isbool", true);
    if (m_hash.size() > 0)
    {
        emit sendMsg(u8"Runable线程启动");
        QThreadPool::globalInstance()->start(m_runnable);
    }
}

void QRunnableCompare::getDataList(QVariantList list)
{
     m_ret_list = list;
     if (m_ret_list.size() > 0)
     {
         emit sendMsg(u8"Runable比较结束返回");
         emit returnRetList(list);
     }
     else
     {
         OUT << u8"获取比较结果数据失败";
     }
}
