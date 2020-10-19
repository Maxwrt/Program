#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "comparethread.h"
#include "thread.h"
#include "compare.h"
#include <QMainWindow>
#include <QVariantList>
#include <QVariantHash>
#include <QString>
#include <QStandardItemModel>
#include <QStringList>
#include <QTimer>
#include <QFile>
#include <QThread>
#include <QMap>
namespace Ui {
class MainWindow;
}

enum RecordStatus
{
    same_records = 0,
    add_records,
    delete_records,
    modified_records
};

struct MarkRecordStatus
{
    qint64 m_recordNo;
    RecordStatus m_status;
    MarkRecordStatus()
    {
        m_recordNo = 0;
        m_status = RecordStatus::same_records;
    }

    MarkRecordStatus(qint64 recordNo)
    {
        m_recordNo = recordNo;
        m_status = RecordStatus::same_records;
    }
};

typedef QMap<QString, MarkRecordStatus> QMapMarkRecorStatus;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showNormal();


signals:
    void startCompare(const QVariantHash& hash);
    void startCompareToThread(const QVariantHash& hash);
    void editStartCompare(const QVariantHash& hash);
private slots:
    void on_pushButtonCompare_clicked();
    void on_pushButtonSynchronize_clicked();
    void on_pushButtonCompare1_clicked();
    void on_pushButtonSynchronize1_clicked();
    void on_pushButtonDelete_clicked();
    void on_actOpen_triggered();
    void on_actSave_triggered();
    void on_actExit_triggered();
    void on_actOpenFile_triggered();
    void timer_out_slot();
    void finish_compare_main(const QVariantList& retlist);
    void CompareThreadFinishSlot();
    void ThreadFinishSlot();

private:
    void initMenu();
    void initToolBar();
    void createTable();
    void updateTable();
    void setTableWidth();
    void stopThread();
    QString parseCompareResult();
    void printQMapMarkRecorStatus(const QMapMarkRecorStatus& record);

private:
    Ui::MainWindow *ui;
    QVariantList m_raw_data;
    QVariantList m_ret_data;
    QString m_filename;
    QString m_dir;
    QVariantHash m_data_hash;
    QStandardItemModel *m_model;
    QStringList m_table_list;
    QTimer *m_timer;
    QThread m_compare_thread;
    Compare *m_compare;
    bool m_synchronize;
    bool m_isthread;
    Thread *m_thread;
};

#endif // MAINWINDOW_H
