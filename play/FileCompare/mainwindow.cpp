#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boolresult.h"
#include "common.h"
#include "QThreadCompare.h"
#include "QObjectCompare.h"
#include "QRunnableCompare.h"
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#include <QColor>
#include <QFileDialog>
#include <QDir>
#include <QIcon>
#include <QFont>
#include <QRegExp>
#include <QTextCodec>
#include <QStringList>
#include <QList>
#include <QMapIterator>
#include <QThreadPool>
#include <QDateTime>
#include <QScrollBar>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    m_table_list << tr("fileName") << tr("handwriteTagname")<< tr("parsePath") << tr("handwritePath") << tr("compareResult");
    setWindowIcon(QIcon(":/image/icon.png"));
    initMenu();
    initToolBar();


    m_flag = 1;
    m_synchronize = false;

    m_timer = QPointer<QTimer>(new QTimer(this));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timer_out_slot()));
    connect(ui->pushButtonInfoTip, &QPushButton::clicked, this, [=]()
    {
        static bool flag = false;
        if (flag)
        {
            ui->textEdit->show();
            flag = false;
        }
        else
        {
            ui->textEdit->hide();
            flag = true;
        }
    });

    //继承QThread实现的比较功能
    m_threadCompare = QPointer<QThreadCompare>(new QThreadCompare(this));
    connect(this, &MainWindow::startQThreadCompare, m_threadCompare, &QThreadCompare::startCompareSlot);
    connect(m_threadCompare, &QThreadCompare::finish_compare_thread, this, &MainWindow::finish_compare_main);
    connect(m_threadCompare, &QThreadCompare::finished, this, &MainWindow::threadCompare_finish_slot);
    connect(m_threadCompare, &QThreadCompare::finished, this, &QThread::deleteLater);
    connect(m_threadCompare, &QThreadCompare::sendMsg, this, &MainWindow::show_msg_slot);

    //继承QObject实现的比较功能
    m_objectCompare = QPointer<QObjectCompare>(new QObjectCompare());
    connect(this, &MainWindow::startQObjectCompare, m_objectCompare, &QObjectCompare::compareSlot, Qt::QueuedConnection);
    connect(&m_objectCompareThread, &QThread::finished, this, &MainWindow::objectCompare_finish_slot, Qt::QueuedConnection);
    connect(&m_objectCompareThread, &QThread::finished, m_objectCompare, &QObject::deleteLater, Qt::QueuedConnection);
    connect(m_objectCompare, &QObjectCompare::finishCompareSignal, this, &MainWindow::finish_compare_main, Qt::QueuedConnection);
    connect(m_objectCompare, &QObjectCompare::sendMsg, this, &MainWindow::show_msg_slot, Qt::QueuedConnection);
    m_objectCompare->moveToThread(&m_objectCompareThread);

    //使用QRunnable类实现的比较功能
    m_runnableComapre = QRunnableCompare::instance();
    connect(this, &MainWindow::startQRunnableCompare, m_runnableComapre, &QRunnableCompare::startCompareSlot);
    connect(m_runnableComapre, &QRunnableCompare::returnRetList, this, &MainWindow::finish_compare_main);
    connect(m_runnableComapre, &QRunnableCompare::sendMsg, this, &MainWindow::show_msg_slot);

    connect(this, &MainWindow::sendMsg, this, &MainWindow::show_msg_slot);


    OUT << u8"主线程 id: " << QThread::currentThreadId();

#if 0
    QMapMarkRecorStatus record;
    record[u8"零"] = MarkRecordStatus();
    record[u8"一"] = record.size();
    record[u8"二"] = record.size();
    record[u8"三"] = record.size();
    record[u8"四"] = record.size();
    record[u8"五"] = record.size();
    record[u8"六"] = record.size();
    printQMapMarkRecorStatus(record);
#endif
}

void MainWindow::printQMapMarkRecorStatus(const QMapMarkRecorStatus& record)
{
    if(record.size() < 1)
        return;
    QMapMarkRecorStatus::const_iterator constItera = record.begin();
    while(constItera != record.end())
    {
        OUT << u8"键:   " <<constItera.key() << u8"  值:  " << constItera.value().m_recordNo;
        constItera++;
    }
}

MainWindow::~MainWindow()
{
    stopThread();
    delete ui;
    OUT << u8"~MainWindow解构";
}

void MainWindow::objectCompare_finish_slot()
{
    OUT << u8"QObjectCompare比较完成";
}

void MainWindow::threadCompare_finish_slot()
{
    OUT << u8"QThreadCompare比较完成";
}

void MainWindow::show_msg_slot(const QString& msg)
{
    if (msg.isEmpty())
        return;
    QScrollBar *verticalBar = ui->textEdit->verticalScrollBar();
    bool down = false;
    if (verticalBar && verticalBar->value() == verticalBar->maximum())
        down = true;
    ui->textEdit->append(msg);
    if (down)
        verticalBar->setValue(verticalBar->maximum());
}

void MainWindow::stopThread()
{
    if (m_objectCompareThread.isRunning())
    {
        m_objectCompareThread.quit();
        m_objectCompareThread.wait();
        sendMsg(u8"解构窗口中，m_objectCompareThread线程退出");
    }

    if (m_threadCompare->isRunning())
    {
        m_threadCompare->stopThread();
        m_threadCompare->wait();
        sendMsg(u8"解构窗口中，m_threadCompare线程退出");
    }
}

void MainWindow::initMenu()
{
    ui->menu->addAction(ui->actOpen);
    ui->menu->addAction(ui->actSave);
    ui->menu->addAction(ui->actExit);
    ui->menu->addAction(ui->actOpenFile);
}

void MainWindow::initToolBar()
{
    ui->mainToolBar->addAction(ui->actOpen);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actSave);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actOpenFile);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actExit);
}

void MainWindow::timer_out_slot()
{
    if(ui->progressBar->value()>=100)
    {
        ui->progressBar->reset();
    }
    int value = ui->progressBar->value();
    if(value > ui->progressBar->maximum())
        value = 0;
    value++;
    ui->progressBar->setValue(value);
}

void MainWindow::on_pushButtonCompare_clicked()
{
    if (!m_data_hash.isEmpty())
        m_data_hash.clear();

    m_dir = ui->lineEditDir->text();
    if(m_dir.isEmpty())
    {
        QMessageBox::information(this, tr("Tip"), tr("lineEditFile is empty, please choose one dir"), tr("ok"));
        return;
    }

    m_filename = ui->lineEditFile->text();
    if(m_filename.isEmpty())
    {
        QMessageBox::information(this, tr("Tip"), tr("lineEditFile is empty, please choose one file"), tr("ok"));
        return;
    }

    if(!m_timer->isActive())
        m_timer->start(200);

    ui->progressBar->reset();
    ui->progressBar->show();

    m_data_hash.insert("file", m_filename);
    m_data_hash.insert("dir",  m_dir);
    m_data_hash.insert("bool", m_synchronize);

    switch(m_flag)
    {
    case 1:
        m_objectCompareThread.start();
        sendMsg(u8"m_objectCompareThread线程启动");
        emit startQObjectCompare(m_data_hash);
        sendMsg(u8"发射startQObjectCompare信号到QObjectCompare");
        break;

    case 2:
        emit startQThreadCompare(m_data_hash);
        sendMsg(u8"发射startQThreadCompare信号到QThreadCompare");
        break;

    case 4:
        emit startQRunnableCompare(m_data_hash);
        sendMsg(u8"发射startQRunnableComapre信号到QRunnableCompare");
        break;

    default:
        break;
    }
}

bool MainWindow::finish_compare_main(const QVariantList& retlist)
{
    if (retlist.size() > 0)
    {
        m_ret_data = retlist;
        QString errmsg = parseCompareResult();
        if(!errmsg.isEmpty())
        {
            if(m_timer->isActive())
            {
                m_timer->stop();
                ui->progressBar->hide();
            }
            QMessageBox::information(this, u8"提示", errmsg + QString(u8"请检查！"), u8"确定");
            return false;
        }
        updateTable();

        switch(m_flag)
        {
        case 1:
            ui->pushButtonSynchronize->setEnabled(true);
            break;
        case 2:
            ui->pushButtonSynchronize1->setEnabled(true);
            break;
        case 4:
            ui->pushButtonSynchronize2->setEnabled(true);
            break;
        default:
            break;
        }

        if (m_objectCompareThread.isRunning())
        {
            m_objectCompareThread.quit();
            m_objectCompareThread.wait();
            if (m_objectCompareThread.isFinished())
            {
                sendMsg(u8"m_objectCompareThread退出");
            }
        }

        if (m_threadCompare->isRunning())
        {
            m_threadCompare->stopThread();
            if (m_threadCompare->isFinished())
            {
                sendMsg(u8"m_threadCompare退出");
            }
        }

    }
    else
    {
        if(m_timer->isActive())
        {
            m_timer->stop();
            ui->progressBar->hide();
        }
        QMessageBox::information(this, u8"提示", u8"比较结果为空", u8"确定");
        return false;
    }
    if(m_timer->isActive())
    {
        m_timer->stop();
        ui->progressBar->hide();
    }
    m_synchronize = false; //默认先进行比较，在进行比对
    m_flag = 1; //默认使用QObject进行比较
    return true;
}

QString MainWindow::parseCompareResult()
{
    QString errmsg = QString::null;
    QHash<QString, QString> uniqueFileHash;
    for(int i=0; i<m_ret_data.count(); i++)
    {
        QVariantHash hash = m_ret_data.at(i).toHash();
        QString fileName = hash.value("fileName").toString();
        if(hash.value("parsePath").toString().isEmpty() && !uniqueFileHash.contains(fileName))
        {
            errmsg += QString(u8"文件%1是空的\r\n").arg(fileName);
            uniqueFileHash.insert(fileName, fileName);
        }
    }
    return errmsg;
}

void MainWindow::on_pushButtonSynchronize_clicked()
{
    m_flag = 1;
    m_synchronize = true;
    on_pushButtonCompare_clicked();
}

void MainWindow::on_pushButtonCompare1_clicked()
{
    if(m_threadCompare->isRunning())
    {
        OUT << u8"m_threadCompare线程在运行";
        return;
    }
    m_threadCompare->start();
    m_flag = 2;
    on_pushButtonCompare_clicked();
}

void MainWindow::on_pushButtonSynchronize1_clicked()
{
    m_flag = 2;
    m_synchronize = true;
    OUT << u8"m_threadCompare线程开始同步";
    on_pushButtonCompare_clicked();
}

void MainWindow::on_pushButtonCompare2_clicked()
{
    m_flag = 4;
    on_pushButtonCompare_clicked();
}

void MainWindow::on_pushButtonSynchronize2_clicked()
{
    m_flag = 4;
    m_synchronize = true;
    OUT << u8"m_runnableComapre线程开始同步";
    on_pushButtonCompare_clicked();
}
void MainWindow::on_pushButtonDelete_clicked()
{
    OUT << u8"清空数据";
    ui->lineEditDir->clear();
    ui->lineEditFile->clear();
    m_model->setRowCount(0);
}

void MainWindow::on_actOpen_triggered()
{
    QString dir = QString::null;
    dir = QFileDialog::getExistingDirectory(this, tr("open dir"), QDir::currentPath());
    if(!dir.isEmpty())
    {
        ui->lineEditDir->setText(dir);
    }
    else
    {
        QMessageBox::information(this, tr("Tip"), tr("please choose one dir"), tr("ok"));
    }
}

void MainWindow::on_actOpenFile_triggered()
{
    QString fileName = QString::null;
    fileName = QFileDialog::getOpenFileName(this, tr("open file"), QDir::currentPath(), tr("textfile(*.txt)"));
    if(!fileName.isEmpty())
    {
        ui->lineEditFile->setText(fileName);
        m_filename = fileName;
    }
    else
    {
        QMessageBox::information(this, tr("Tip"), tr("please choose one file"), tr("ok"));
    }
}

void MainWindow::on_actSave_triggered()
{
    if(m_model->rowCount() <= 0)
    {
        QMessageBox::information(this, tr("save file"), tr("please check file firstly!"), tr("ok"));
        return;
    }
    QString fileName = QString::null;
    fileName = QFileDialog::getSaveFileName(this, tr("save file"), QDir::currentPath(), u8"text file(*.txt)");
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream write(&file);
            write.setCodec("UTF-8");
            write << tr("fileName\t")
                  << tr("handwriteTagname\t")
                  << tr("parsePath\t")
                  << tr("handwritePath\t")
                  << tr("compareResult\r\n");
            if(m_ret_data.count()>0)
            {
                for(int i=0; i<m_ret_data.count(); i++)
                {
                    QVariantHash hash = m_ret_data.at(i).toHash();
                    write << hash.value("fileName").toString() << "\t";
                    write << hash.value("handwriteTagname").toString() << "\t";
                    write << hash.value("parsePath").toString() << "\t";
                    write << hash.value("handwritePath").toString() << "\t";
                    if(hash.value("isSame").toBool())
                    {
                        write<<tr("same")<<"\r\n";
                    }
                    else
                    {
                        write<<tr("different")<<"\r\n";
                    }
                }
            }
            file.close();
        }
    }
    else
    {
        OUT<<tr("don't choose one file");
    }
}

void MainWindow::showNormal()
{
    createTable();
    show();
}

void MainWindow::createTable()
{
    QTableView *t = ui->tableView;
    t->setSelectionBehavior(QAbstractItemView::SelectRows);
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    t->setAlternatingRowColors(true);
    t->horizontalHeader()->setStretchLastSection(true);
    t->resizeColumnsToContents();
    t->setTextElideMode(Qt::ElideMiddle);

    m_model = QPointer<QStandardItemModel>(new QStandardItemModel(this));
    m_model->setColumnCount(m_table_list.count());
    m_model->setHorizontalHeaderLabels(m_table_list);
    t->setModel(m_model);
}

void MainWindow::setTableWidth()
{
    for(int i=0; i<m_model->columnCount(); i++)
    {
        if(i=0)
        {
            ui->tableView->setColumnWidth(i, 200);
            continue;
        }
        ui->tableView->setColumnWidth(i, 150);
    }
}

bool MainWindow::showData(const QVariantList* retdata)
{
    return finish_compare_main(*retdata);
}

void MainWindow::updateTable()
{
    m_model->setRowCount(0);
    if(m_ret_data.count()>0)
    {
        for(int i=0; i<m_ret_data.count(); i++)
        {
            m_model->setRowCount(m_ret_data.size() + 10);
            QVariantHash hash = m_ret_data.at(i).toHash();
            m_model->setData(m_model->index(i, 0), hash.value("fileName").toString(), Qt::DisplayRole);
            QString str = hash.value("handwriteTagname").toString();
            m_model->setData(m_model->index(i, 1), str, Qt::DisplayRole);
            m_model->setData(m_model->index(i, 2), hash.value("parsePath").toString(),Qt::DisplayRole);
            m_model->setData(m_model->index(i, 3), hash.value("handwritePath").toString(), Qt::DisplayRole);
            if(hash.value("isSame").toBool())
            {
                m_model->setData(m_model->index(i, 4), tr("same"), Qt::DisplayRole);
                m_model->setData(m_model->index(i, 4), QColor("#000000"), Qt::ForegroundRole);
            }
            else
            {
                m_model->setData(m_model->index(i, 4), tr("different"), Qt::DisplayRole);
                m_model->setData(m_model->index(i, 4), QColor("#ff0000"), Qt::ForegroundRole);
            }

            if(hash.value("isExist").toBool())
            {
                for(int j=0; j<m_model->columnCount()-1; j++)
                {
                    m_model->setData(m_model->index(i, j), QColor("#ff0000"), Qt::BackgroundRole);
                }
            }
        }
        m_ret_data.clear();
    }
    else
    {
        OUT << u8"比较结果为空，请检查";
    }
}

void MainWindow::on_actExit_triggered()
{
    close();
}
