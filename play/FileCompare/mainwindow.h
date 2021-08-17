/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include "QObjectCompare.h"
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
#include <QPointer>
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

class QObjectCompare;
class QRunnableCompare;
class QThreadCompare;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showNormal();

signals:
    void startQThreadCompare(const QVariantHash& hash);
    void startQObjectCompare(const QVariantHash& hash);
    void startQRunnableCompare(const QVariantHash& hash);
    void sendMsg(const QString & msg);
    void deleteQObject(bool flag);

public slots:
    bool showData(const QVariantList* retdata);

private slots:
    void on_pushButtonCompare_clicked();
    void on_pushButtonSynchronize_clicked();
    void on_pushButtonCompare1_clicked();
    void on_pushButtonSynchronize1_clicked();
    void on_pushButtonCompare2_clicked();
    void on_pushButtonSynchronize2_clicked();
    void on_actOpen_triggered();
    void on_actSave_triggered();
    void on_actExit_triggered();
    void on_actOpenFile_triggered();
    void timer_out_slot();
    bool finish_compare_main(const QVariantList& retlist);
    void objectCompare_finish_slot();
    void threadCompare_finish_slot();
    void show_msg_slot(const QString& msg);

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
    QPointer<QStandardItemModel> m_model;
    QStringList m_table_list;
    QPointer<QTimer> m_timer;
    QThread m_objectCompareThread;
    QObjectCompare *m_objectCompare;
    bool m_synchronize;
    short unsigned int m_flag;  //最低1位标识QObject,次级一位标识QThread,再次级一位标识QRunnable
    QPointer<QThreadCompare> m_threadCompare;
    QRunnableCompare *m_runnableComapre;
};

#endif // MAINWINDOW_H
