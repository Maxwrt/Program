#ifndef BASE_H
#define BASE_H

#include <QStandardItemModel>
#include <QVariantList>
#include <QTableView>
#include <QSqlDatabase>
#include <QItemDelegate>
class ReadOnlyDelegate:public QItemDelegate
{
public:
    ReadOnlyDelegate(QWidget *parent=NULL):QItemDelegate(parent){}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(parent);
        Q_UNUSED(option);
        Q_UNUSED(index);
        return NULL;
    }
};
class Base
{
public:
    Base();

    static void log(QtMsgType type, const QMessageLogContext &content, const QString &msg);
    static void removeFile(QString fileName);
    QStandardItemModel* createTable(QTableView *tableView, const QString& tableName);
    bool updateTable(QStandardItemModel *tablemodel, QTableView *tableView,const QVariantList &dataList,const QString &tableName);
    QString getHanZiJianPin(QString str);
    QVariantList getApartList(){return m_apartment_list;}
    QVariantList selectTable(const QString sql,const QString tableName);
private:
    QVariantList readText();
    bool createDB();
    static QString buildLogDir();
    char convert(wchar_t n);
    bool In(wchar_t start, wchar_t end, wchar_t code);
    QString getJianPin(const  QString &hanzistr);

private:
    QSqlDatabase m_db;
    QVariantList m_apartment_list;
    QStringList m_staff_head_list;
    QStringList m_boy_head_list;
    QStringList m_girl_head_list;
    QStringList m_age_head_list;
};

#endif // BASE_H
