/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef QRunnableCompare_H
#define QRunnableCompare_H

#include <QRunnable>
#include <QObject>
#include <QMutex>
#include <QVariantHash>
#include <QPointer>
#include <QMutex>


class Compare;
class Runnable : public QRunnable
{
public:
    Runnable(QObject * parent = 0);
    ~Runnable();

protected:
    virtual void run();

private:
    QObject *m_obj;
    QPointer<Compare> m_compare;
    QMutex m_mutex;
};

class QRunnableCompare: public QObject
{
    Q_OBJECT
public:
    static QRunnableCompare* instance()
    {
        static QRunnableCompare* ptr = nullptr;
        if (ptr == nullptr)
        {
            ptr = new QRunnableCompare(0);
        }
        return ptr;
    }
    QVariantHash giveDatahash()
    {
        return m_hash;
    }
    Q_INVOKABLE   void getDataList(QVariantList list);

public slots:
    void startCompareSlot(const QVariantHash& hash);


signals:
    void sendMsg(const QString& msg);
    void returnRetList(const QVariantList& retlist);

private:
    QRunnableCompare(QObject *parent = 0);
    ~QRunnableCompare();

private:
    Runnable *m_runnable;
    QVariantHash m_hash;
    QVariantList m_ret_list;
    QMutex m_mutex;
};

#endif // QRunnableCompare_H
