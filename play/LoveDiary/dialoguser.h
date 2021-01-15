/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef DIALOGUSER_H
#define DIALOGUSER_H

#include "basedialog.h"
#include <QDialog>
#include <QVariantList>
#include <QStringList>
#include <QSqlDatabase>
#include <QKeyEvent>
namespace Ui {
class DialogUser;
}

class DialogUser : public BaseDialog
{
    Q_OBJECT

public:
    explicit DialogUser(const QSqlDatabase& db, QWidget *parent = 0);
    ~DialogUser();

private slots:
    void on_btnInsert_clicked();
    void on_btnDelete_clicked();
    void on_btnUpdate_clicked();

private:
    void updateTable();
    void selectdb();
    void InitHeadList();
    void setText();
    void infomation(QPushButton *button, const QString& msg);

private:
    Ui::DialogUser *ui;
    QVariantList m_userList;
    QStringList m_headList;
    QStringList m_usernameList;
    QSqlDatabase m_db;
};

#endif // DIALOGUSER_H
