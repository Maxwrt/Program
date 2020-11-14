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

    //���бȽϴ������
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
            OUT << u8"����ͤ����";
        }
        else
        {
            OUT << u8"����ͤ��ȷ";
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
        emit sendMsg(u8"Runable�߳�����");
        QThreadPool::globalInstance()->start(m_runnable);
    }
}

bool QRunnableCompare::getDataList(QVariantList list)
{
     m_ret_list = list;
     if (m_ret_list.size() > 0)
     {
         emit sendMsg(u8"Runable�ȽϽ�������");
         emit returnRetList(list);
     }
     return m_ret_list.size() > 0 ? true : false;
}
