/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTimer>
#include <QVariantHash>
#include <QDateTime>
#include <QSqlDatabase>
#include <QLabel>
#include <QPushButton>
#include <QSqlDatabase>
#include <QKeyEvent>
#include "agreementdialog.h"
#include "picture.h"
#include "dialoguser.h"
#include <QThread>
#include <QPointer>
#include <QSharedPointer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QSqlDatabase& db, const QVariantHash& logHash, QWidget *parent = 0);
    ~MainWindow();
    void Show();

private:
    void Init();
    void InitSignalSlot();
    void EditUser();
    void UpdateLoginCount();

private:
    Ui::MainWindow *ui;
    QVariantHash m_UserHash;
    QDateTime m_loveDateTime;
    QString m_LoginTime;
    QTimer m_timer;
    const int m_numDigits;
    QSqlDatabase m_db;
    QLabel *m_labelTipInfo;
    QPointer<AgreementDialog> m_AgreementDialog;
    QPointer<Picture> m_picture;
    QPointer<DialogUser> m_dlgUser;
    QThread  m_thread;
};

#endif // MAINWINDOW_H
