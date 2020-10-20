#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QTreeWidget>
#include <QVector>
#include <QLabel>
#include <QSqlDatabase>
#include <QFileSystemWatcher>
#include "dlgitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QVariantHash userHash, QWidget *parent = 0);
    ~MainWindow();

    void ShowWindow();

private slots:
    void onMenuOpen(bool checked);
    void onMenuSave(bool checked);

    void on_btnSearch_clicked(bool checked);        //搜索按钮，关键字过滤
    void on_btnAdd_clicked(bool checked);           //添加
    void on_btnDelete_clicked(bool checked);        //删除
    void on_btnExport_clicked(bool checked);        //导出
    void on_btnEditUsers_clicked(bool checked);     //编辑用户信息
    void showQDialog(bool checked);

    void slotAddItem(PCustomer item);   //DlgItem里添加记录后需要不关闭对话框，因此发个信号
    void comboBoxCurrentTextChangedSlot(const QString &arg1);   //按单位类别过滤
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous); //改变选择区域
    void on_tableView_doubleClicked(const QModelIndex &index);  //数据一行双击修改
    void on_fileChanged(const QString path);
    void on_directoryChanged(const QString path);
    void contextMenuEvent(QContextMenuEvent* e);

private:
    QString Type2String(int type);
    QString Area2String(int area);
    QString Province2String(int province);
    PCustomer FindItem(QString name);
    bool isExist(PCustomer p);
    void DeleteItem(QString name);

    void InitMenu();
    void InitModel();
    void InitTable();
    void InitTreeWidget();
    void AddItem(PCustomer item);
    void ClearData();
    void InitData();
    void OpenDb();
    void SaveToDb(const QString& fileName);
    bool SaveCustomersToDb();
    bool SaveUsersToDb();
    void InsertToDb(PCustomer item);
    void DeleteFromDb(QString name);
    void PrintCustomer();
    void copyCustomer(PCustomer old_, PCustomer new_);
    bool compareCustomers(PCustomer old_, PCustomer new_);
    void printDBDrivers();
    void updateLoginCount();
    inline const char* classname(){return typeid(this).name();}

    void setRedRow(const QString& key);
    void editUser();
    void initWidgets();
    void initSignalSlot();
private:
    Ui::MainWindow *ui;
    QStandardItemModel* mModel; //tableview的model
    QVector<PCustomer> mCustomerItems;  //所有客户数据
    QVector<PUser> mUserItems;  //所有用户数据

    QStringList mAllType;       //所有单位类型
    QStringList mAllArea;       //所有区域
    QStringList mAllProvince;   //所有省份
    QVariantHash muserHash;     //用户信息

    QString mFilterType;        //单位类型过滤
    QString mFilterArea;        //地域过滤
    QString mFilterProvince;    //省份过滤
    QString mUnkonwn;           //其他未知元素
    QStringList mheaders;       //表头数据
    QFileSystemWatcher mfilewatcher;
    QString mLoginTime;
    QSqlDatabase mDB;
};

#endif // MAINWINDOW_H
