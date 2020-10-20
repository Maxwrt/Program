#include "mainwindow.h"
#include "common.h"
#include "ui_mainwindow.h"
#include "basefunction.h"
#include "dialoguser.h"
#include <QListView>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QRegExpValidator>
#include <QHeaderView>
#include <QSplitter>
#include <QFile>
#include <QStringList>
#include <QStatusBar>
#include <QDate>
#include <QModelIndexList>
#include <QContextMenuEvent>
#include <iostream>
#include <memory>
#include <QComboBox>
#include <QIODevice>
#include <QTextStream>

MainWindow::MainWindow(QVariantHash userHash,QWidget *parent) :
    QMainWindow(parent),
    muserHash(userHash),
    ui(new Ui::MainWindow)
{
    initWidgets();
    InitData();
    OpenDb();
    InitTable();
    InitMenu();
    initSignalSlot();
    editUser();
}

void MainWindow::initWidgets()
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/config/myapp.ico"));
    setWindowTitle(tr("Client Manage System"));

    ui->tabWidget->count();
    ui->tabWidget->removeTab(1);
    ui->tabWidget_2->removeTab(1);
    ui->comboBox->setView(new QListView(this));
    ui->comboBox->addItems(mAllType);
    ui->comboBox->setCurrentIndex(0);
    ui->tabWidget->setTabBarAutoHide(true);
    ui->tabWidget->setStyleSheet("border:none");
    ui->tabWidget->setCurrentIndex(0);
    ui->btnExport->setText(tr("Export"));
    ui->btnEditUsers->setText(u8"编辑用户");
    //setWindowFlags(Qt::CustomizeWindowHint);
}

void MainWindow::initSignalSlot()
{
    connect(&mfilewatcher, SIGNAL(fileChanged(QString)), SLOT(on_fileChanged(QString)));
    connect(ui->actAppend, SIGNAL(triggered(bool)),      SLOT(on_btnAdd_clicked(bool)));
    connect(ui->actDelete, SIGNAL(triggered(bool)),      SLOT(on_btnDelete_clicked(bool)));
    connect(ui->actExport, SIGNAL(triggered(bool)),      SLOT(on_btnExport_clicked(bool)));
    connect(ui->actClose,  SIGNAL(triggered(bool)),      SLOT(close()));
    connect(ui->comboBox,  SIGNAL(currentTextChanged(QString)), SLOT(comboBoxCurrentTextChangedSlot(QString)));
}

void MainWindow::InitData()
{
    mDB = Createdb(QStringLiteral("/config/CustomerManageSystem.db"));
    mfilewatcher.addPath(qApp->applicationDirPath() % QStringLiteral(""));
    QString fileName("./config/table.txt");
    if(!QFile::exists(fileName))
    {
        qDebug()<<QString(u8"文件%1不存在").arg(fileName);
        return;
    }
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream read(&file);
        QString distinguish = QString::null;
        while(!read.atEnd())
        {
            QString str = read.readLine();
            if(str.contains("#"))
            {
                distinguish = str;
                continue;
            }
            if(distinguish.contains("tableCustomer"))
            {
                mheaders+=str.split(";");
            }
            else if(distinguish.contains("allType"))
            {
                mAllType+=str.split(";");
            }
            else if(distinguish.contains("allArea"))
            {
                mAllArea+=str.split(";");
            }
            else if(distinguish.contains("allProvince"))
            {
                mAllProvince+=str.split(";");
            }
        }
        file.close();
    }
    else
    {
        qDebug()<<QString(u8"打开文件%1失败").arg(fileName);
    }
    mFilterType = "";
    mFilterArea = "";
    mFilterProvince = "";
}

void MainWindow::editUser()
{
    mLoginTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    if(muserHash.value("isroot").toBool())
    {
        ui->labelTipInfo_2->setText(QString(u8"管理员:%1,您好！砍把子*****这是您第%2次使用系统").arg(muserHash.value("username").toString()).arg(muserHash.value("loginCount").toInt()+1));
        ui->btnEditUsers->show();
    }
    else
    {
        ui->labelTipInfo_2->setText(QString(u8"用户:%1,你好！小弟").arg(muserHash.value("username").toString()));
        ui->btnEditUsers->hide();
    }
    //更新数据库中用户的登陆次数
    updateLoginCount();
}

void MainWindow::updateLoginCount()
{
    if(mDB.open())
    {
        QString update_sql="update users set loginCount='%1',latestlogintime='%2' where username='%3'";
        update_sql=update_sql.arg(muserHash.value("loginCount").toInt()+1).arg(mLoginTime).arg(muserHash.value("username").toString());
        QSqlQuery query;
        query.prepare(update_sql);
        if(query.exec())
        {
            qDebug().noquote()<<u8"更新loginCount成功";
        }
        else
        {
            qDebug().noquote()<<u8"更新loginCount失败";
        }

        QString select_sql="select * from users";
        query.prepare(select_sql);
        if(query.exec())
        {
            while(query.next())
            {
                PUser item = new User;
                item->username = query.value("username").toString();
                item->password = query.value("password").toString();
                item->isroot = query.value("isroot").toBool();
                item->datestring = query.value("datestring").toString();
                item->sex = query.value("sex").toString();
                item->loginCount = query.value("loginCount").toInt();
                item->latestlogintime = query.value("latestlogintime").toString();
                mUserItems.push_back(item);
            }
        }
        mDB.close();
    }
}

void MainWindow::printDBDrivers()
{
    QStringList drivers=QSqlDatabase::drivers();
    foreach (QString driver, drivers) {
        qDebug().noquote() << driver << " ";
    }
}

void MainWindow::on_fileChanged(const QString path)
{
    qDebug().noquote() << QString(u8"%1 发生了变化").arg(path);
}

void MainWindow::on_directoryChanged(const QString path)
{
    Q_UNUSED(path);
}

MainWindow::~MainWindow()
{
    ClearData();
    delete ui;
}

void MainWindow::ShowWindow()
{
    InitTreeWidget();
    show();
}

void MainWindow::on_btnExport_clicked(bool checked)
{
    Q_UNUSED(checked);
    QDate date = QDate::currentDate();

    QString filename = QStringLiteral("./log/") % date.toString("yyyy_MM_dd")  % QStringLiteral("_data.txt");

    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<tr("start export");
        QTextStream awrite(&file);
        QString datastr;
        for(int i=0; i<mModel->columnCount();i++)
        {
            datastr += mModel->headerData(i, Qt::Horizontal).toString() % QStringLiteral("   ");
        }
        awrite << datastr << "\n";
        for(int i=0; i<mModel->rowCount(); i++)
        {
            datastr.clear();
            for(int j=0;j<mModel->columnCount();j++)
            {
                datastr += mModel->item(i, j)->text() % QStringLiteral("\t");
            }
            datastr+="\n";
            awrite<<datastr;
        }
        file.close();
        QFont font("Microsoft YaHei",10,75);
        ui->labelTipInfo->setFont(font);
        ui->labelTipInfo->setStyleSheet("QLabel{color:red;}");
        ui->labelTipInfo->setText(tr("Export Success"));
        BaseFunction::delay(1);
        ui->labelTipInfo->clear();
    }
    else
    {
        qDebug()<<tr("open %1 failed").arg(filename);
    }
}

void MainWindow::InitTreeWidget()
{
    QString filename("./config/province.xml");
    if(!QFile::exists(filename))
    {
        qDebug().noquote()<<QString(u8"%1不存在").arg(filename);
        return;
    }
    if(!BaseFunction::parseXmlFile(ui->treeWidget, filename))
    {
        qDebug()<<tr("parse xmlfile failed,please check");
        return;
    }
    ui->treeWidget->setHeaderHidden(true);
    ui->treeWidget->expandAll();
    ui->treeWidget->setCurrentItem(ui->treeWidget->itemAt(0,0));
}

void MainWindow::InitMenu()
{
    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(tr("Open..."), this, SLOT(onMenuOpen(bool)));
    file->addAction(tr("Save"), this, SLOT(onMenuSave(bool)));
    file->addAction(tr("Insert"), this, SLOT(showQDialog(bool)));
    QList<QAction*>actions=file->actions();
    for(int i=0; i<actions.count(); i++)
    {
        QAction* action=actions.at(i);
        if(action->text()==tr("Open..."))
            action->setShortcut(QKeySequence("CTRL+o"));
        if(action->text()==tr("Save"))
            action->setShortcut(QKeySequence("CTRL+s"));
        if(action->text()==tr("Insert"))
        {
            action->setShortcut(QKeySequence("CTRL+i"));
        }
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent* e)
{
    QMenu* menu=new QMenu();
    menu->addAction(ui->actAppend);
    menu->addAction(ui->actDelete);
    menu->addSeparator();
    menu->addAction(ui->actExport);
    menu->addAction(ui->actClose);
    menu->exec(e->globalPos());
    delete menu;
}

void MainWindow::PrintCustomer()
{
    if(mCustomerItems.isEmpty())
    {
        qDebug()<<"mItem is empty,no client data";
    }
    else
    {
        for(int i=0;i<mCustomerItems.size();i++)
        {
            PCustomer p = mCustomerItems.at(i);
            qDebug() << "Company: " << p->name << " type: " << Type2String(p->type) << " area" << Area2String(p->area) << " province:   " << Province2String(p->province);
        }
    }
    return;
}

void MainWindow::InitModel()
{
    mModel->removeRows(0,mModel->rowCount());
    for(int i=0;i<mCustomerItems.size();i++)
    {
        PCustomer p = mCustomerItems[i];
        QString sArea = Area2String(p->area);
        QString sProvince = Province2String(p->province);
        QString sType = Type2String(p->type);

        //区域过滤
        if(!mFilterArea.isEmpty())
        {
            if(mFilterArea != sArea)
            {
                continue;
            }
        }
        //省份过滤
        if(!mFilterProvince.isEmpty())
        {
            if(mFilterProvince != sProvince)
            {
                continue;
            }
        }
        //其他位置元素，不写表格
        if(!mUnkonwn.isEmpty())
        {
            break;
        }
        //单位类别过滤
        if(!mFilterType.isEmpty())
        {
            if(mFilterType != sType)
            {
                continue;
            }
        }

        QList<QStandardItem*> items;
        QStandardItem* item1 = new QStandardItem(p->name);
        QStandardItem* item2 = new QStandardItem(Type2String(p->type));
        QStandardItem* item3 = new QStandardItem(Area2String(p->area));
        QStandardItem* item4 = new QStandardItem(Province2String(p->province) );
        QStandardItem* item5 = new QStandardItem(p->city);
        QStandardItem* item6 = new QStandardItem(p->address);
        QStandardItem* item7 = new QStandardItem(p->site);
        QStandardItem* item8 = new QStandardItem(p->research);
        QStandardItem* item9 = new QStandardItem(p->remark);
        items.append(item1);
        items.append(item2);
        items.append(item3);
        items.append(item4);
        items.append(item5);
        items.append(item6);
        items.append(item7);
        items.append(item8);
        items.append(item9);
        mModel->appendRow(items);
    }
    mFilterArea.clear();
    mFilterProvince.clear();
    mFilterType.clear();
}

void MainWindow::InitTable()
{
    QTableView* t=ui->tableView;
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);			//不能编辑
    t->setSelectionBehavior(QAbstractItemView::SelectRows);			//一次选中整行
    t->setAlternatingRowColors(true);
    t->horizontalHeader()->setStretchLastSection(true);
    t->resizeColumnsToContents();
    QString strTreeStyle = "QTableView::item {height: 25px}";
    t->setStyleSheet(strTreeStyle);

    mModel=new QStandardItemModel(this);
    mModel->setHorizontalHeaderLabels(mheaders);

    InitModel();
    t->setModel(mModel);
    for(int i=0;i<mheaders.size();i++)
    {
        if(i==0)
        {
            t->horizontalHeader()->resizeSection(i,200);
        }
        else if(i==1)
        {
            t->horizontalHeader()->resizeSection(i,80);
        }
        else if(i>=2 && i<=4)
        {
            t->horizontalHeader()->resizeSection(i,60);
        }
        else
        {
            t->horizontalHeader()->resizeSection(i,150);
        }
    }

    QModelIndex selIndex = mModel->index(0,0,t->rootIndex());
    t->setCurrentIndex(selIndex);
}

void MainWindow::AddItem(PCustomer item)
{
    mCustomerItems.push_back(item);
}

void MainWindow::ClearData()
{
    for(int i=0;i<mCustomerItems.size();i++)
    {
        PCustomer p = mCustomerItems[i];
        if(p)
        {
            delete p;
            p = NULL;
        }
    }
    for(int i=0;i<mUserItems.size();i++)
    {
        PUser p = mUserItems[i];
        if(p)
        {
            delete p;
            p = NULL;
        }
    }
    mCustomerItems.clear();
}

void MainWindow::OpenDb()
{
    if(mDB.open())
    {
        qDebug().noquote()<<tr("Database Opened");

        QSqlQuery sql_query;
        QString create_table_sql = "create table if not exist Customer(name varchar(100) primary key, \
                type int ,\
                area int,\
                province int,\
                city varchar(20),\
                address varchar(100),\
                site varchar(200),\
                contact varchar(500),\
                buy varchar(200),\
                research varchar(100),\
                remark varchar(200))";
        sql_query.prepare(create_table_sql);
        sql_query.exec();

        QString select_all_sql = "select * from Customer";
        //查询所有记录
        sql_query.prepare(select_all_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                PCustomer p = new Customer;
                p->name = sql_query.value(0).toString();
                p->type = sql_query.value(1).toInt();
                p->area = sql_query.value(2).toInt();
                p->province = sql_query.value(3).toInt();
                p->city = sql_query.value(4).toString();
                p->address = sql_query.value(5).toString();
                p->site = sql_query.value(6).toString();
                p->contact = sql_query.value(7).toString();
                p->buy = sql_query.value(8).toString();
                p->research = sql_query.value(9).toString();
                p->remark = sql_query.value(10).toString();
                mCustomerItems.push_back(p);
            }
        }
        mDB.close();
    }
    else
    {
        qDebug().noquote()<<u8"打开数据库失败";
        qDebug().noquote()<<mDB.lastError();
    }
}
bool MainWindow::SaveCustomersToDb()
{
    QSqlQuery sql_query;
    QString create_sql = "create table if not exists Customer (name varchar(100) primary key, \
            type int ,\
            area int,\
            province int,\
            city varchar(20),\
            address varchar(100),\
            site varchar(200),\
            contact varchar(500),\
            buy varchar(200),\
            research varchar(100),\
            remark varchar(200))";
    QString insert_sql = "insert into Customer values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11')";

    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug()<<QObject::tr("Customer Table Create failed");
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        for(int i=0;i<mCustomerItems.size();i++)
        {
            PCustomer p = mCustomerItems[i];
            QString str;
            str = insert_sql.arg(p->name).arg(p->type).arg(p->area).arg(p->province).arg(p->city).arg(p->address).arg(p->site).arg(p->contact).arg(p->buy).arg(p->research).arg(p->remark);
            sql_query.prepare(str);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
                return false;
            }
        }
    }
    return true;
}

bool MainWindow::SaveUsersToDb()
{
    QString create_table_sql = "create table if not exists users(username varchar(11) primary key, \
                                password varchar(11) not null, \
                                isroot boolean, datestring varchar(20), \
                                sex varchar(5), loginCount int, latestlogintime varchar(20))";
    QString insert_sql = "insert into users values('%1', '%2', '%3', '%4', '%5', '%6', '%7')";
    QSqlQuery query_sql;
    query_sql.prepare(create_table_sql);
    if(!query_sql.exec())
    {
        qDebug()<<query_sql.lastError();
        return false;
    }
    for(int i=0; i<mUserItems.size(); i++)
    {
        PUser p= mUserItems.at(i);
        QString str;
        str = insert_sql.arg(p->username).arg(p->password).arg(p->isroot).arg(p->datestring) \
                     .arg(p->sex).arg(p->loginCount).arg(p->latestlogintime);
        query_sql.prepare(str);
        if(!query_sql.exec())
        {
            qDebug()<<query_sql.lastError();
            return false;
        }
    }
    return true;
}

void MainWindow::SaveToDb(const QString& fileName)
{
    QFileInfo fileInfo(fileName);

    QSqlDatabase newDB;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        newDB=QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        newDB=QSqlDatabase::addDatabase("QSQLITE");
    }
    newDB.setDatabaseName(fileInfo.absoluteFilePath());
    if(newDB.open())
    {
        qDebug()<<"Database Opened";
        bool ret = SaveCustomersToDb();
        if(!ret)
        {
            qDebug().noquote()<<u8"保存客户表失败";
        }
        ret = SaveUsersToDb();
        if(!ret)
        {
            qDebug().noquote()<<u8"保存用户表失败";
        }
    }
    else
    {
        qDebug().noquote()<<u8"打开数据库失败";
    }
    newDB.close();
}

void MainWindow::InsertToDb(PCustomer p)
{
    if(mDB.open())
    {
        QSqlQuery sql_query;
        QString sql = QStringLiteral("insert into Customer values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11')");    //插入数据
        sql = sql.arg(p->name).arg(p->type).arg(p->area).arg(p->province).arg(p->city).arg(p->address).arg(p->site)   \
              .arg(p->contact).arg(p->buy).arg(p->research).arg(p->remark);
        sql_query.prepare(sql);
        if(!sql_query.exec())
        {
            qDebug().noquote()<<sql_query.lastError();
        }
        else
        {
            qDebug().noquote()<<QStringLiteral("insert record success");
        }
    }
    mDB.close();
}


void MainWindow::DeleteFromDb(QString name)
{
    if(mDB.open())
    {
        QSqlQuery sql_query;
        QString sql = QString(QStringLiteral("delete from Customer where name='%1'")).arg(name);
        sql_query.prepare(sql);
        if(!sql_query.exec())
        {
            qDebug().noquote()<<sql_query.lastError();
        }
        else
        {
            qDebug().noquote()<<tr("delete record success");
        }
    }
    mDB.close();
    return;
}

void MainWindow::onMenuOpen(bool checked)
{
    Q_UNUSED(checked);
    QString fileName = QFileDialog::getOpenFileName(this,tr("OpenFile"),"","Database Files(*.db)");
    if (fileName.isNull())
    {
        return;
    }
    if(fileName.indexOf(".db") != -1)
    {
        ClearData();
        OpenDb();
        InitTable();
    }
    return;
}

void MainWindow::onMenuSave(bool checked)
{
    Q_UNUSED(checked);
    QString fileName = QFileDialog::getSaveFileName(this,tr("SaveFile"),"","Database Files(*.db)");
    if (fileName.isNull())
    {
        return;
    }
    SaveToDb(fileName);
}

void MainWindow::on_btnSearch_clicked(bool checked)
{
    Q_UNUSED(checked);
    QString s = ui->lineEdit->text();
    if(s.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("搜索框为空，请填写搜索简拼"), QMessageBox::Yes);
        return;
    }
    setRedRow(s);
}

void MainWindow::setRedRow(const QString& key)
{
    InitModel();
    bool flag = false;
    for(int i=0; i<mModel->rowCount(); i++)
    {
        QString content = mModel->item(i)->text();
        QString jianPin = GetJianPin(content);
        if(content == key || jianPin.contains(key.toLower()))
        {
            flag = true;
            for(int j=0; j<mModel->columnCount(); j++)
            {
                mModel->setData(mModel->index(i, j), QColor("#ff0000"), Qt::BackgroundColorRole);
            }
        }
    }
    if(!flag)
    {
        QMessageBox::information(this, QStringLiteral("提示"), tr(u8"单位%1不存在，请输入全称再搜索一次").arg(key), QMessageBox::Yes);
    }
}

void MainWindow::on_btnEditUsers_clicked(bool checked)
{
    Q_UNUSED(checked);
    DialogUser dlgUser(this);
    dlgUser.exec();
}

void MainWindow::showQDialog(bool checked)
{

    Q_UNUSED(checked);
    DlgItem dlg(NULL, this);
    connect(&dlg,SIGNAL(sigAddItem(PCustomer)),this,SLOT(slotAddItem(PCustomer)));
    dlg.exec();
}

void MainWindow::on_btnAdd_clicked(bool checked)
{
    showQDialog(checked);
}

void MainWindow::on_btnDelete_clicked(bool checked)
{
    Q_UNUSED(checked);
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if(selectedRows.count()<1)
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请选中要删除的行"), QStringLiteral("确定"));
        return;
    }
    QModelIndex index=selectedRows.at(0);
    int row=index.row();

    for (int i=0; i<selectedRows.count(); i++)
    {
        QString name=mModel->item(row, 0)->text();
        DeleteItem(name);
        mModel->removeRow(row);
        DeleteFromDb(name);
    }
    ui->labelTipInfo->setText(tr("delete success"));
    ui->labelTipInfo->setText("QLabel{color:red;}");
    BaseFunction::delay(1);
    ui->labelTipInfo->clear();
}

bool MainWindow::isExist(PCustomer p)
{
    if(!FindItem(p->name))
    {
        return false;
    }
    else
    {
        QMessageBox::information(this, tr("Info"), tr("%1 is exists").arg(p->name), tr("Ok"));
    }
    return true;
}

void MainWindow::slotAddItem(PCustomer p)
{
    qDebug().noquote()<<QStringLiteral("信号槽函数执行");
    if(isExist(p))
    {
        QMessageBox::information(this, QStringLiteral("提示"), QString("%1已经存在,请重新添加客户信息").arg(p->name), u8"确定");
        return;
    }

    mCustomerItems.push_back(p);

    QList<QStandardItem*> items;
    QStandardItem* item1 = new QStandardItem(p->name);
    QStandardItem* item2 = new QStandardItem(Type2String(p->type));
    QStandardItem* item3 = new QStandardItem(Area2String(p->area));
    QStandardItem* item4 = new QStandardItem(Province2String(p->province) );
    QStandardItem* item5 = new QStandardItem(p->city);
    QStandardItem* item6 = new QStandardItem(p->address);
    QStandardItem* item7 = new QStandardItem(p->site);
    QStandardItem* item8 = new QStandardItem(p->research);
    QStandardItem* item9 = new QStandardItem(p->remark);
    items.append(item1);
    items.append(item2);
    items.append(item3);
    items.append(item4);
    items.append(item5);
    items.append(item6);
    items.append(item7);
    items.append(item8);
    items.append(item9);
    mModel->appendRow(items);
    InsertToDb(p);
    qDebug().noquote() << QStringLiteral("槽函数执行结束");
}

QString MainWindow::Type2String(int n)
{
    return mAllType.at(n);
}

QString MainWindow::Area2String(int n)
{
    return mAllArea.at(n);
}

QString MainWindow::Province2String(int n)
{
    return mAllProvince.at(n);
}

PCustomer MainWindow::FindItem(QString name)
{
    for(int i=0;i<mCustomerItems.size();i++)
    {
        if(mCustomerItems[i]->name == name)
        {
            return mCustomerItems[i];
        }
    }
    return NULL;
}

void MainWindow::DeleteItem(QString name)
{
    for(int i=0;i<mCustomerItems.size();i++)
    {
        if(mCustomerItems[i]->name == name)
        {
            mCustomerItems.removeAt(i);
            return;
        }
    }
    return;
}

void MainWindow::comboBoxCurrentTextChangedSlot(const QString &text)
{
    if(text == tr("Alltype"))
    {
        mFilterType = "";
    }
    else
    {
        mFilterType = text;
    }
    QString s = ui->treeWidget->currentItem()->text(0);
    if(s == tr("china"))
    {
        mFilterArea = "";
        mFilterProvince = "";
        mUnkonwn = "";
    }
    else if(mAllArea.contains(s))
    {
        //区域
        mFilterArea = s;
        mFilterProvince = "";
        mUnkonwn = "";
    }
    else if(mAllProvince.contains(s))
    {
        //省份
        mFilterArea = "";
        mFilterProvince = s;
        mUnkonwn = "";
    }
    else
    {
        mUnkonwn = s;
    }
    InitModel();
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem * previous)
{
    Q_UNUSED(previous);
    QString s = current->text(0);
    if(s == tr("china"))
    {
        mFilterArea = "";
        mFilterProvince = "";
        mUnkonwn = "";
    }
    else if(mAllArea.contains(s))
    {
        //区域
        mFilterArea = s;
        mFilterProvince = "";
        mUnkonwn = "";
    }
    else if(mAllProvince.contains(s))
    {
        //省份
        mFilterArea = "";
        mFilterProvince = s;
        mUnkonwn = "";
    }
    else
    {
        mUnkonwn = s;
    }
    QString text=ui->comboBox->currentText();
    if(text == tr("Alltype"))
    {
        mFilterType = "";
    }
    else
    {
        mFilterType = text;
    }
    InitModel();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString name = mModel->item(index.row(),0)->text();

    PCustomer p = FindItem(name);
    if(p)
    {
        PCustomer p_old = new Customer;
        copyCustomer(p_old, p);
        DlgItem dlg(p,this);
        if(QDialog::Accepted == dlg.exec())
        {
            if(!compareCustomers(p_old, p))
            {
                mModel->item(index.row(),0)->setText(p->name);
                mModel->item(index.row(),1)->setText(Type2String(p->type));
                mModel->item(index.row(),2)->setText(Area2String(p->area));
                mModel->item(index.row(),3)->setText(Province2String(p->province));
                mModel->item(index.row(),4)->setText(p->city);
                mModel->item(index.row(),5)->setText(p->address);
                mModel->item(index.row(),6)->setText(p->site);
                mModel->item(index.row(),7)->setText(p->research);
                mModel->item(index.row(),8)->setText(p->remark);

                DeleteFromDb(name);
                InsertToDb(p);
                qDebug().noquote() << QStringLiteral("数据被修改");
            }
            else
            {
                qDebug().noquote() << QStringLiteral("数据无变化");
            }
        }
        delete p_old;
    }
}

void MainWindow::copyCustomer(PCustomer old_, PCustomer new_)
{
    old_->address = new_->address;
    old_->area = new_->area;
    old_->buy = new_->buy;
    old_->city = new_->city;
    old_->contact = new_->city;
    old_->name = new_->name;
    old_->province = new_->province;
    old_->remark = new_->remark;
    old_->research = new_->research;
    old_->site = new_->site;
    old_->type = new_->type;
}
bool MainWindow::compareCustomers(PCustomer old_, PCustomer new_)
{
    if((old_->address != new_->address) || (old_->area != new_->area) || (old_->buy != new_->buy)
            || (old_->city != new_->city) || old_->contact != old_->contact || (old_->name != new_->name)
            || (old_->province != new_->province) || old_->remark != new_->remark || (old_->research != new_->research)
            || (old_->site != new_->site) || (old_->type != new_->type))
    {
        return false;
    }
    return true;
}
