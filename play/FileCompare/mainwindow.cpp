#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boolresult.h"
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
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->pushButtonSynchronize->setEnabled(false);
    ui->pushButtonSynchronize1->setEnabled(false);
    m_table_list << tr("fileName") << tr("handwriteTagname")<< tr("parsePath") << tr("handwritePath") << tr("compareResult");
    setWindowIcon(QIcon(":/image/icon.png"));
    initMenu();
    initToolBar();

    m_isthread = false;
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timer_out_slot()));
    m_synchronize = false;
    m_thread = new Thread(this);
    connect(this, &MainWindow::startCompareToThread, m_thread, &Thread::startCompareSlot);
    connect(m_thread, &Thread::finish_compare_thread, this, &MainWindow::finish_compare_main);
    connect(m_thread, &Thread::finished, this, &MainWindow::ThreadFinishSlot);
    connect(m_thread, &Thread::finished, this, &QThread::deleteLater);
    connect(this, &MainWindow::editStartCompare, m_thread, &Thread::editStartCompareSlot);

    m_compare = new Compare();
    connect(this, &MainWindow::startCompare, m_compare, &Compare::compareSlot, Qt::QueuedConnection);
    connect(&m_compare_thread, &QThread::finished, this, &MainWindow::CompareThreadFinishSlot, Qt::QueuedConnection);
    connect(&m_compare_thread, &QThread::finished, m_compare, &QObject::deleteLater, Qt::QueuedConnection);
    connect(m_compare, &Compare::finishCompareSignal, this, &MainWindow::finish_compare_main, Qt::QueuedConnection);
    m_compare->moveToThread(&m_compare_thread);
    m_compare_thread.start();

    qDebug().noquote()<<u8"���߳� id: "<<QThread::currentThreadId();
    QMapMarkRecorStatus record;
    record[u8"��"] = MarkRecordStatus();
    record[u8"һ"] = record.size();
    record[u8"��"] = record.size();
    record[u8"��"] = record.size();
    record[u8"��"] = record.size();
    record[u8"��"] = record.size();
    record[u8"��"] = record.size();
    printQMapMarkRecorStatus(record);
}

void MainWindow::printQMapMarkRecorStatus(const QMapMarkRecorStatus& record)
{
    if(record.size() < 1)
        return;
    QMapMarkRecorStatus::const_iterator constItera = record.begin();
    while(constItera != record.end())
    {
        qDebug().noquote() << "key:   " <<constItera.key() << "  value:  " << constItera.value().m_recordNo;
        constItera++;
    }
}

MainWindow::~MainWindow()
{
    stopThread();
    delete ui;
    qDebug().noquote()<<tr("~MainWindow destruct");
}

void MainWindow::CompareThreadFinishSlot()
{
    qDebug().noquote()<<tr("info: m_compare_thread exit");
}

void MainWindow::ThreadFinishSlot()
{
    qDebug().noquote()<<tr("info: m_thread exit");
}

void MainWindow::stopThread()
{
    if (m_compare_thread.isRunning())
    {
        m_compare_thread.quit();
        m_compare_thread.wait();
        qDebug().noquote()<<tr("m_compare_thread over");
    }

    if (m_thread->isRunning())
    {
        m_thread->stopThread();
        m_thread->wait();
        qDebug().noquote() << "m_thread over";
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
    if(!m_timer->isActive())
        m_timer->start(200);
    ui->progressBar->reset();
    ui->progressBar->show();
    m_dir = ui->lineEditDir->text();
    if(m_dir.isEmpty())
    {
        if(m_timer->isActive())
            m_timer->stop();
        ui->progressBar->hide();
        QMessageBox::information(this, tr("Tip"), tr("lineEditFile is empty, please choose one dir"), tr("ok"));
        return;
    }

    m_filename = ui->lineEditFile->text();
    if(m_filename.isEmpty())
    {
        if(m_timer->isActive())
            m_timer->stop();
        ui->progressBar->hide();
        QMessageBox::information(this, tr("Tip"), tr("lineEditFile is empty, please choose one file"), tr("ok"));
        return;
    }

    QVariantHash hash;
    hash.insert("file", m_filename);
    hash.insert("dir",  m_dir);
    hash.insert("bool", m_synchronize);
    m_data_hash = hash;
    if(!m_isthread)
    {
        emit startCompare(hash);
        qDebug().noquote()<<tr("emit startCompare signal");
    }
    else
    {
        emit startCompareToThread(hash);
        qDebug().noquote()<<tr("emit startCompareToThread signal");
    }
}

void MainWindow::finish_compare_main(const QVariantList& retlist)
{
    if(retlist.count() > 0)
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
            QMessageBox::information(this, u8"��ʾ", errmsg + QString(u8"���飡"), u8"ȷ��");
            return;
        }
        updateTable();
        if(m_synchronize)
        {
            qDebug().noquote()<<tr("synchronize over");
            m_synchronize = false;
            m_data_hash.insert("bool", m_synchronize);
        }
        if(m_isthread)
        {
            ui->pushButtonSynchronize1->setEnabled(true);
            m_isthread = false;
        }
        else
        {
            ui->pushButtonSynchronize->setEnabled(true);
        }
    }
    else
    {
        if(m_timer->isActive())
        {
            m_timer->stop();
            ui->progressBar->hide();
        }
        qDebug().noquote()<<tr("compare result is empty");
        QMessageBox::information(this, u8"��ʾ", u8"�ȽϽ��Ϊ��", u8"ȷ��");
    }
    if(m_timer->isActive())
    {
        m_timer->stop();
        ui->progressBar->hide();
    }
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
            errmsg += tr(u8"�ļ�%1�ǿյ�\n").arg(fileName);
            uniqueFileHash.insert(fileName, fileName);
        }
    }
    return errmsg;
}

void MainWindow::on_pushButtonSynchronize_clicked()
{
    m_synchronize = true;
    on_pushButtonCompare_clicked();
}

void MainWindow::on_pushButtonCompare1_clicked()
{
    if(m_thread->isRunning())
    {
        qDebug().noquote()<<tr("m_thread is runing");
        emit editStartCompare(m_data_hash);
        return;
    }
    m_thread->start();
    m_isthread = true;
    on_pushButtonCompare_clicked();
}

void MainWindow::on_pushButtonSynchronize1_clicked()
{
    m_isthread = true;
    m_synchronize = true;
    on_pushButtonCompare_clicked();
}

void MainWindow::on_pushButtonDelete_clicked()
{
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
            write << tr("fileName") << "\t" << tr("handwriteTagname") << "\t" \
                  << tr("parsePath") << "\t" << tr("handwritePath") << "\t" \
                  << tr("compareResult")<< "\n";
            if(m_ret_data.count()>0)
            {
                for(int i=0; i<m_ret_data.count(); i++)
                {
                    QVariantHash hash = m_ret_data.at(i).toHash();
                    write<<hash.value("fileName").toString()<<"\t";
                    write<<hash.value("handwriteTagname").toString()<<"\t";
                    write<<hash.value("parsePath").toString()<<"\t";
                    write<<hash.value("handwritePath").toString()<<"\t";
                    if(hash.value("isSame").toBool())
                    {
                        write<<tr("same")<<"\n";
                    }
                    else
                    {
                        write<<tr("different")<<"\n";
                    }
                }
            }
            file.close();
        }
    }
    else
    {
        qDebug().noquote()<<tr("don't choose one file");
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

    m_model = new QStandardItemModel(this);
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
        qDebug().noquote()<<tr("compare result is empty, please check");
    }
}

void MainWindow::on_actExit_triggered()
{
    close();
}
