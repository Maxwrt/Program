/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef DLGITEM_H
#define DLGITEM_H

#include <QDialog>
#include <QStringList>
#include <QStandardItemModel>
namespace Ui {
class DlgItem;
}

typedef struct _Customer{
    QString name;
    int type;
    int area;
    int province;
    QString city;
    QString address;
    QString site;
    QString contact;
    QString buy;
    QString research;
    QString remark;
}Customer,*PCustomer;

typedef struct _User{
    QString username;
    QString password;
    bool    isroot;
    QString datestring;
    QString sex;
    int     loginCount;
    QString latestlogintime;
}User, *PUser;

class DlgItem : public QDialog
{
    Q_OBJECT

public:
    explicit DlgItem(PCustomer item,QWidget *parent = 0);
    ~DlgItem();


signals:
    void sigAddItem(PCustomer);

private slots:
    void on_btnAdd_clicked();
    void on_btnCancel_clicked();
    void on_combo2_currentTextChanged(const QString &arg1);
    void closeEvent(QCloseEvent *event);

private:
    void initCombo();
    int String2Province(QString s);
    QString Province2String(int province);
    DlgItem& operator=(const DlgItem dlgItem);

private:
    Ui::DlgItem *ui;
    PCustomer mItem;
    QStringList mAllTypeList;
    QStringList mAllAreaList;
    QStringList mAllProvinceList;
    QStringList headerList;
    QStandardItemModel *mmodel;
};

#endif // DLGITEM_H
