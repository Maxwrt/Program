/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef UTIL_H
#define UTIL_H
#include<QSqlDatabase>
#include<QString>
#include<QVariantList>
#include<QStringList>
#include<QStandardItemModel>
#include<QTableView>
#include <QVariantHash>

class Util : public QObject
{
    Q_OBJECT
public:
    Util();
    QVariantList getStafList() {return m_staff_list;}
    QVariantList getBoyList() {return m_boy_list;}
    QVariantList getGirlList() {return m_girl_list;}
    QVariantList getAgeList() {return m_age_list;}
signals:
    void loadDataFinishSignal();
public slots:
    void loadDataSlot(const QString &departName);
private:
    bool loadData(const QString &departName);
private:
    QVariantList m_staff_list;
    QVariantList m_boy_list;
    QVariantList m_girl_list;
    QVariantList m_age_list;
};

#endif // UTIL_H
