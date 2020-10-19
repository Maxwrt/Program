#ifndef THREAD_H
#define THREAD_H

#include "comparethread.h"
#include <QThread>
#include <QVariantHash>
#include <QMutex>
#include <QVariantList>

class Thread: public QThread
{
    Q_OBJECT
public:
    Thread(QObject *parent = 0);
    ~Thread();
    void stopThread();

public slots:
    void startCompareSlot(const QVariantHash& hash);
    void receiveBaseSlot(const QVariantList& retlist);
    void editStartCompareSlot(const QVariantHash& hash);

signals:
    void finish_compare_thread(const QVariantList& retlist);
private:
    void compare();

private:
    void run() Q_DECL_OVERRIDE;
    QVariantHash m_hash;
    Base *m_base;
    bool m_stop;
    bool m_start_compare;
    QMutex m_mutex;
};


#endif // THREAD_H
