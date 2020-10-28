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
    AgreementDialog *m_AgreementDialog;
    Picture *m_picture;
    DialogUser *m_dlgUser;
};

#endif // MAINWINDOW_H
