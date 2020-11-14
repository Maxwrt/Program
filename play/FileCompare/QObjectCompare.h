#ifndef QObjectCompare_H
#define QObjectCompare_H

#include <QObject>
#include <QMutex>
#include <QTextStream>
#include <QPointer>


class Compare;
class QObjectCompare: public QObject
{
    Q_OBJECT
public:
    QObjectCompare(QObject *parent = 0);
    ~QObjectCompare();

public slots:
    void compareSlot(const QVariantHash& hash);
    void finishCompareSlot(const QVariantList& retlist);
    void print()
    {
        QTextStream(stdout) << "test\n";
    }

signals:
    void finishCompareSignal(const QVariantList& retlist);
    void editThreadMemberSignal();
    void sendMsg(const QString& msg);

private:
    QPointer<Compare> m_compare;
    QMutex m_mutex;
};

#endif // QObjectCompare_H
