#ifndef COMPARE_H
#define COMPARE_H

#include "comparethread.h"
#include <QObject>
#include <QMutex>
#include <QTextStream>
class Compare: public QObject
{
    Q_OBJECT
public:
    Compare(QObject *parent = 0);
    ~Compare();

public slots:
    void compareSlot(const QVariantHash& hash);
    void finishCompareSlot(const QVariantList& retlist);
    void print()
    {
        QTextStream(stdout) << "wrt\n";
    }

signals:
    void finishCompareSignal(const QVariantList& retlist);
    void editThreadMemberSignal();
    void sendMsg(const QString& msg);

private:
    Base *m_base;
    QMutex m_mutex;
};

#endif // COMPARE_H
