#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QColor>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_treeItemChanged = false;
    m_timer = new QTimer(this);
    m_findPosition = 0;
    ui->StaffProgressBar->hide();
    ui->labelInfo->hide();
    QIcon icon(":/images/person.png");
    setWindowIcon(icon);
    setWindowTitle(u8"职工信息检查");

    m_base = new Base();

    m_util = new Util();
    connect(this, SIGNAL(loadDataSignal(const QString)), m_util, SLOT(loadDataSlot(const QString)));
    connect(m_util, SIGNAL(loadDataFinishSignal()), this, SLOT(loadDataFinishSlot()));
    m_util->moveToThread(&m_thread);
    m_thread.start();

    connect(m_timer, SIGNAL(timeout()), this,SLOT(timeOutSlot()));
    connect(ui->ApartmentSearchButton, SIGNAL(clicked(bool)), this, SLOT(locateDepartmentSlot()));
    connect(ui->ApartmentTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(treeItemChangeSlot()));
    connect(ui->StaffSearchButton, SIGNAL(clicked(bool)), this, SLOT(tableSearchSlot()));
    connect(ui->StaffCloseButton,SIGNAL(clicked(bool)),this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    qDebug().noquote()<<u8"构造函数被执行";
    if(m_thread.isRunning())
    {
        qDebug().noquote()<<u8"杀死m_thread";
        m_thread.quit();
        m_thread.wait();
    }
    if(m_util)
        delete m_util;
    if(m_base)
        delete m_base;
    delete ui;
}

void MainWindow::showWindow()
{
    initTree();
    initTable();
    showNormal();
    if(!m_timer->isActive())
    {
        m_timer->start(500);
    }
}

void MainWindow::tableSearchSlot()
{
    QString id = ui->StaffLineEdit->text();
    if(id.isEmpty())
    {
        QMessageBox::information(this, QString(u8"提示信息"), QString(u8"工号不能为空"), QMessageBox::Yes);
        return;
    }
    bool findFlag=false;
    for(int i=0; i<m_staff_model->rowCount(); i++)
    {
        QString tableIdStr=m_staff_model->index(i, 1).data().toString();
        if(tableIdStr == id)
        {
            m_staff_model->setData(m_staff_model->index(i,1), QColor(0,255,0), Qt::ForegroundRole);
            findFlag=true;
            break;
        }
    }
    if(!findFlag)
    {
        QMessageBox::information(this, QString(u8"提示信息"), QString(u8"没有工号为%1的职工").arg(id), QMessageBox::Yes);
    }
    return;
}

void MainWindow::locateDepartmentSlot()
{
    QString departStr = ui->ApartmentLineEdit->text();
    if(departStr.isEmpty())
    {
        QMessageBox::information(this, tr("提示信息"), tr("搜索框内容为空"), QMessageBox::Yes, QMessageBox::No);
        return;
    }
    bool findFlag = false;
    QString jianPin = m_base->getHanZiJianPin(departStr);
    for(int i=m_findPosition; i<m_treeStrList.count();i++)
    {
        QString str = m_treeStrList.at(i);
        if(str.contains(jianPin))
        {
            QTreeWidgetItem* item = m_treeItemHash.value(jianPin);
            if(item != NULL)
            {
                ui->ApartmentTreeWidget->setCurrentItem(item);
                findFlag = true;
                m_findPosition=i;
            }
        }
    }

    if(!findFlag)
    {
        for(int i=0; i<m_findPosition; i++)
        {
            QString str = m_treeStrList.at(i);
            if(str.contains(jianPin))
            {
                QTreeWidgetItem* item = m_treeItemHash.value(jianPin);
                if(item != NULL)
                {
                    ui->ApartmentTreeWidget->setCurrentItem(item);
                    findFlag = true;
                    m_findPosition=i+1;
                }
            }
        }
    }
    if(!findFlag)
        QMessageBox::information(this, tr("提示信息"), tr("%1 不存在").arg(departStr), QMessageBox::Yes, QMessageBox::No);
    return;
}

void MainWindow::treeItemChangeSlot()
{
    QTreeWidgetItem* item = ui->ApartmentTreeWidget->currentItem();
    if(item==NULL || item==rootitem)
        return;
    m_currentTreeItemHash=item->data(0, Qt::UserRole).toHash();
    ui->StaffProgressBar->show();
    ui->labelInfo->show();
    m_treeItemChanged = true;
}

void MainWindow::initTree()
{
    rootitem = new QTreeWidgetItem(ui->ApartmentTreeWidget);
    rootitem->setText(0, (u8"部门列表"));
    ui->ApartmentTreeWidget->setHeaderHidden(true);
    ui->ApartmentTreeWidget->expandAll();
    QVariantHash hash;
    QVariantList list = m_base->getApartList();
    if(list.count()>0)
    {
        for(int i=0; i<list.count(); i++)
        {
            hash = list.at(i).toHash();
            if(hash.value("table") == "apartment")
            {
                QTreeWidgetItem* item = new QTreeWidgetItem(rootitem);
                item->setText(0, hash.value("desc").toString());
                item->setData(0, Qt::UserRole, hash);
                QString str = hash.value("desc").toString();
                QString jianpin =m_base->getHanZiJianPin(str);
                m_treeStrList<<jianpin;
                m_treeItemHash.insert(jianpin, item);
            }
        }
    }
    if(rootitem->childCount()>0)
    {
        QTreeWidgetItem* item = rootitem->child(0);
        ui->ApartmentTreeWidget->setCurrentItem(item);
        ui->ApartmentTreeWidget->resizeColumnToContents(0);
    }
}

void MainWindow::initTable()
{
    m_staff_model = m_base->createTable(ui->StaffTableView, "staff");
    m_boy_model = m_base->createTable(ui->BoyTableView, "boy");
    m_girl_model = m_base->createTable(ui->GirlTableView, "girl");
    m_age_model = m_base->createTable(ui->AgeTableView, "age");
}


void MainWindow::delay(int mesc)
{
    QTime time=QTime::currentTime().addMSecs(mesc*1000);
    while(QTime::currentTime()<time)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}
void MainWindow::timeOutSlot()
{
    int value=ui->StaffProgressBar->value()+10;
    if(value>ui->StaffProgressBar->maximum())
        value=0;
    ui->StaffProgressBar->setValue(value);
    if(m_treeItemChanged)
    {
        QString departName= m_currentTreeItemHash.value("desc").toString();
        emit loadDataSignal(departName);
    }
}

void MainWindow::loadDataFinishSlot()
{
    m_staff_list = m_util->getStafList();
    m_base->updateTable(m_staff_model, ui->StaffTableView, m_staff_list, "staff");

    m_boy_list = m_util->getBoyList();
    m_base->updateTable(m_boy_model, ui->BoyTableView, m_boy_list, "boy");

    m_girl_list = m_util->getGirlList();
    m_base->updateTable(m_girl_model, ui->GirlTableView, m_girl_list, "girl");


    m_age_list = m_util->getAgeList();
    m_base->updateTable(m_age_model, ui->AgeTableView, m_age_list, "age");

    ui->StaffProgressBar->hide();
    ui->labelInfo->hide();
    m_treeItemChanged = false;

}
