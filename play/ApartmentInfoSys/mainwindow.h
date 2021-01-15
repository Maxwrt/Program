/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVariantList>
#include <QStandardItemModel>
#include <QHash>
#include <QThread>
#include <QTreeWidgetItem>
#include <QVariantHash>
#include <QItemDelegate>
#include "util.h"
#include "base.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showWindow();

signals:
    void loadDataSignal(const QString &departName);
private slots:
    void timeOutSlot();
    void locateDepartmentSlot();
    void treeItemChangeSlot();
    void tableSearchSlot();
    void loadDataFinishSlot();
private:
    void initTree();
    void initTable();
    void delay(int mesc);

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    QVariantList m_allDataList;
    QStandardItemModel *m_staff_model;
    QVariantList m_staff_list;
    QStandardItemModel *m_boy_model;
    QVariantList m_boy_list;
    QStandardItemModel *m_girl_model;
    QVariantList m_girl_list;
    QStandardItemModel *m_age_model;
    QVariantList m_age_list;
    QStringList m_treeStrList;
    bool m_treeItemChanged;
    QHash<QString, QTreeWidgetItem*> m_treeItemHash;
    QVariantHash m_currentTreeItemHash;
    QTreeWidgetItem* rootitem;
    int m_findPosition;
    QThread m_thread;
    Util *m_util;
    Base *m_base;
};

#endif // MAINWINDOW_H
