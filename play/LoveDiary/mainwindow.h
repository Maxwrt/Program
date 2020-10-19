#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTimer>
#include <QVariantHash>
#include <QDateTime>
#include "agreementdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QVariantHash& logHash, QWidget *parent = 0);
    ~MainWindow();
    void Show();
private:
    void Init();
    void InitSignalSlot();

private:
    Ui::MainWindow *ui;
    QVariantHash m_loginUserHash;
    QDateTime m_loveDateTime;
    QTimer m_timer;
    const int m_numDigits;
    AgreementDialog *m_AgreementDialog;
};

#endif // MAINWINDOW_H
