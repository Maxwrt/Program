#ifndef COMPARETHREAD_H
#define COMPARETHREAD_H

//#include "boolresult.h"
#include <QObject>
#include <QVariantHash>
#include <QMap>
#include <QDomElement>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QThread>
class BoolResult;
class Base: public QObject
{
    Q_OBJECT
public:
    Base(QObject *parent = 0);
//    ~Base()
//    {
//        QTextStream(stdout) << "function:   " << __FUNCTION__ << " id:   "<< QThread::currentThreadId() << "\n";
//    }
    void compare(const QVariantHash& hash);

signals:
    void finishCompare(const QVariantList& retlist);
    void finishCompareToThread(const QVariantList& retlist);

private:
    void printMap(const QMap<QString, QVariantHash>& map);
    void compareAll(const QVariantList& rawDataList);
    QVariantHash compareOne(const QVariantHash& hash);
    QString parseXml(const QString& fileName, const QString& tagName, const QString& rightPath = QString::null);
    QString parseTargetTagName(const QDomElement& element, const QString& tagName, const QString& rightPath = QString::null);

private:
    BoolResult readTextFile(const QString& fileName);
    QVariantList m_raw_data;
    QMap<QString, QVariantHash> m_raw_map;
    QMap<QString, QString> m_map;
    QVariantList m_ret_data;
    QDomDocument m_doc;
    bool m_synchronize;
    QFile m_file;
    QString m_dir;
};

#endif // COMPARETHREAD_H
