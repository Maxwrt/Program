#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <QRunnable>
#include <QObject>
#include <QMutex>
#include <QVariantHash>
#include <QPointer>
#include "comparethread.h"

class Runnable : public QRunnable
{
public:
    Runnable(QObject * parent = 0);
    ~Runnable();

protected:
    virtual void run();

private:
    QObject *m_obj;
    QPointer<Base> m_base;
    QMutex m_mutex;
};

class CompareRunable: public QObject
{
    Q_OBJECT
public:
    static CompareRunable* instance()
    {
        static CompareRunable* ptr = nullptr;
        if (ptr == nullptr)
        {
            ptr = new CompareRunable(0);
        }
        return ptr;
    }
    QVariantHash giveDatahash()
    {
        return m_hash;
    }

public slots:
    void startCompareSlot(const QVariantHash& hash);
    bool getDataList(QVariantList list);


signals:
    void sendMsg(const QString& msg);
    void returnRetList(const QVariantList& retlist);

private:
    CompareRunable(QObject *parent = 0);
    ~CompareRunable();

private:
    Runnable *m_runnable;
    QVariantHash m_hash;
    QVariantList m_ret_list;
};

#endif // RUNNABLE_H
