#ifndef COMPARE_H
#define COMPARE_H

#include "comparethread.h"
#include <QObject>
#include <QMutex>

class Compare: public QObject
{
    Q_OBJECT
public:
    Compare();
    ~Compare();

public slots:
    void compareSlot(const QVariantHash& hash);
    void finishCompareSlot(const QVariantList& retlist);

signals:
    void finishCompareSignal(const QVariantList& retlist);
    void editThreadMemberSignal();

private:
    Base *m_base;
    QMutex m_mutex;
};

#endif // COMPARE_H
