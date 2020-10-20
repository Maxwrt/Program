#include "dialoguser.h"
#include "common.h"
#include "ui_dialoguser.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QVariantHash>
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
DialogUser::DialogUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUser)
{
    ui->setupUi(this);
    createDB();
    InitHeadList();
    setText();
    updateTable();
}

DialogUser::~DialogUser()
{
    qDebug().noquote()<<u8"DialogUser析构调用";
    m_db.close();
    delete ui;
}

void DialogUser::setText()
{
    ui->btnDelete->setText(u8"删除");
    ui->btnInsert->setText(u8"添加");
    ui->btnUpdate->setText(u8"更新");
}

void DialogUser::createDB()
{
    m_db = Createdb(QStringLiteral("/config/LoveDiary.db"));
    if(m_db.isOpen() || m_db.open())
    {
        QString create_table_sql = QStringLiteral("create table if not exists users(username varchar(11) primary key, \
                                    password varchar(11) not null, \
                                    isroot boolean, datestring varchar(20), \
                                    sex varchar(5), loginCount int, latestlogintime varchar(20), remarks varchar(20))");
        QSqlQuery query_sql;
        query_sql.prepare(create_table_sql);
        if(!query_sql.exec())
        {
            qDebug()<<query_sql.lastError();
            return ;
        }
    }
}

void DialogUser::selectdb()
{
    if(m_db.open())
    {
        QString select_sql = QStringLiteral("select * from users");
        QSqlQuery qsql;
        qsql.prepare(select_sql);
        if(qsql.exec())
        {
            while(qsql.next())
            {
                QVariantHash hash;
                hash.insert("username", qsql.value(0).toString());
                hash.insert("password", qsql.value(1).toString());
                hash.insert("isroot", qsql.value(2).toBool());
                hash.insert("datestring", qsql.value(3).toString());
                hash.insert("sex",qsql.value(4).toString());
                hash.insert("loginCount", qsql.value(5).toInt());
                hash.insert("latestlogintime",qsql.value(6).toString());
                hash.insert("remarks", qsql.value(7).toString());
                m_userList<<hash;
                m_usernameList<<qsql.value(0).toString();
            }
        }
    }
    else
    {
        qDebug().noquote()<<u8"打开users.db失败"<<m_db.lastError();
    }
}

void DialogUser::InitHeadList()
{
    QString filename(QStringLiteral("./config/table.txt"));
    if(!QFile::exists(filename))
    {
        qDebug().noquote()<<QString(u8"文件%1不存在").arg(filename);
        return;
    }

    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream read(&file);
        QString content;
        while(!read.atEnd())
        {
            QString str = read.readLine();
            if(str.contains("#"))
            {
                content = str;
                continue;
            }
            if(content.contains("tableUser"))
            {
                m_headList += str.split(";");
            }
        }
        file.close();
    }
}


void DialogUser::on_btnInsert_clicked()
{
    QModelIndex index=ui->tableWidget->currentIndex();
    if(index.isValid())
    {
        QString username=ui->tableWidget->item(index.row(), 0)->text();
        QString password=ui->tableWidget->item(index.row(), 1)->text();
        QString isroot=ui->tableWidget->item(index.row(), 2)->text();

        if(username.isEmpty() || password.isEmpty())
        {
            QMessageBox::information(this, u8"提示", u8"用户名或密码为空", u8"确定");
            return;
        }
        bool flag=false;
        if(isroot==u8"是")
        {
            flag=true;
        }
        QString datestring=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString sex=ui->tableWidget->item(index.row(), 3)->text();
        QString loginCount=ui->tableWidget->item(index.row(), 4)->text();
        QString remarks=ui->tableWidget->item(index.row(), 7)->text();
        if(m_usernameList.contains(username))
        {
            QMessageBox::information(this, u8"提示", tr(u8"%1已经存在").arg(username), u8"确定");
            if(index.row()>m_usernameList.count())
            ui->tableWidget->removeRow(index.row());
            return;
        }
        if(m_db.open())
        {
            QString insert_sql=QStringLiteral("insert into users(username, password, isroot, datestring, sex, loginCount, remarks) values('%1', '%2', '%3', '%4', '%5', '%6', '%7')");
            insert_sql=insert_sql.arg(username).arg(password).arg(flag).arg(datestring).arg(sex).arg(loginCount.toInt()).arg(remarks);
            QSqlQuery qsql;
            qsql.prepare(insert_sql);
            if(qsql.exec())
            {
                qDebug().noquote()<<QString(u8"插入%1成功").arg(username);
                infomation(ui->btnInsert, u8"添加成功");
                ui->btnInsert->setText(u8"添加");
                ui->tableWidget->item(index.row(), 5)->setText(datestring);
                m_usernameList<<username;
                QVariantHash hash;
                hash.insert("username",username);
                hash.insert("password", password);
                hash.insert("isroot", flag);
                hash.insert("datestring", datestring);
                hash.insert("sex", sex);
                hash.insert("loginCount", loginCount);
                hash.insert("remarks", remarks);
                m_userList<<hash;
            }
            else
            {
                qDebug().noquote()<<m_db.lastError();
            }
        }
//        updateTable();
    }
    else
    {
        qDebug().noquote()<<u8"索引无效";
    }
}

void DialogUser::on_btnDelete_clicked()
{
    QModelIndex index=ui->tableWidget->currentIndex();
    QString username=ui->tableWidget->item(index.row(), 0)->text();
    ui->tableWidget->removeRow(index.row());
    if(m_db.open())
    {
        QString delete_sql = QStringLiteral("delete from users where username='%1'");
        delete_sql=delete_sql.arg(username);

        QSqlQuery qsql(delete_sql);
        if(qsql.exec())
        {
            qDebug().noquote()<<QString(u8"删除%1成功").arg(username);
            m_usernameList.removeOne(username);
            for(int i=0; i<m_userList.count(); i++)
            {
                QVariantHash hash=m_userList.at(i).toHash();
                if(hash.value("username")==username)
                {
                    m_userList.removeAt(i);
                    infomation(ui->btnDelete, u8"删除成功");
                    ui->btnDelete->setText(u8"删除");
                    break;
                }
            }
        }
        else
        {
            qDebug().noquote()<<m_db.lastError();
        }
    }
}

void DialogUser::infomation(QPushButton *button, const QString &msg)
{
    button->setStyleSheet(QStringLiteral("QPushButton{color:red;}"));
    button->setText(msg);
    Sleep(2000);
    button->setStyleSheet(QStringLiteral("QPushButton{color:black;}"));
}

void DialogUser::on_btnUpdate_clicked()
{
    QModelIndex index=ui->tableWidget->currentIndex();
    if(index.isValid())
    {
        QString username=ui->tableWidget->item(index.row(), 0)->text();
        if(!m_usernameList.contains(username, Qt::CaseInsensitive))
        {
            QMessageBox::information(this, u8"提示", u8"不能修改用户名",u8"确定");
            for(int i=0; i<m_usernameList.count(); i++)
            {
                QString item=ui->tableWidget->item(i,0)->text();
                bool isexist=false;
                int j;
                for(j=0; j<m_usernameList.count(); j++)
                {
                    if(item == m_usernameList.at(j))
                    {
                        isexist=true;
                        break;
                    }
                }
                if(!isexist)
                {
                    if(j>=m_usernameList.count())
                        j=j-1;
                    ui->tableWidget->item(index.row(), 0)->setText(m_usernameList.at(j));
                }
            }

            return;
        }

        QString password=ui->tableWidget->item(index.row(), 1)->text();
        QString isroot=ui->tableWidget->item(index.row(), 2)->text();
        bool flag=false;
        if(isroot==u8"是")
        {
            flag=true;
        }
        QString remarks=ui->tableWidget->item(index.row(), 7)->text();
        QString sex=ui->tableWidget->item(index.row(), 3)->text();
        QString loginCount=ui->tableWidget->item(index.row(), 4)->text();

        if(m_db.open())
        {
            QString update_sql = QStringLiteral("update users set password='%2',  isroot='%3', sex='%4', loginCount='%5', remarks='%6' where username='%1'");
            update_sql=update_sql.arg(username).arg(password).arg(flag).arg(sex).arg(loginCount.toInt()).arg(remarks);
            QSqlQuery qsql;
            qsql.prepare(update_sql);
            if(qsql.exec())
            {
                qDebug().noquote()<<QString(u8"更新%1成功").arg(username);
                infomation(ui->btnUpdate, u8"更新成功");
                ui->btnUpdate->setText(u8"更新");

            }
            else
            {
                qDebug().noquote()<<m_db.lastError();
            }
        }
    }
    else
    {
        qDebug().noquote()<<u8"索引无效";
    }
}

void DialogUser::updateTable()
{
    ui->tableWidget->clear();
    m_userList.clear();
    m_usernameList.clear();
    selectdb();
    if(m_userList.count()>0)
    {
        ui->tableWidget->setColumnCount(m_headList.count());
        ui->tableWidget->setHorizontalHeaderLabels(m_headList);
        ui->tableWidget->setRowCount(m_userList.count()+10);

        for(int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(""));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(""));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(""));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(""));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(""));
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget->setItem(i, 5, item);

            item=new QTableWidgetItem("");
            item->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget->setItem(i, 6, item);
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(""));
        }

        for(int i=0; i<m_userList.count(); i++)
        {
            QVariantHash hash = m_userList.at(i).toHash();
            if(hash.count()>= m_headList.count())
            {
                ui->tableWidget->item(i, 0)->setText(hash.value("username").toString());
                ui->tableWidget->item(i, 1)->setText(hash.value("password").toString());
                QString text=QString::null;
                if(hash.value("isroot").toBool())
                    text=u8"是";
                else
                    text=u8"否";
                ui->tableWidget->item(i,2)->setText(text);
                ui->tableWidget->item(i,3)->setText(hash.value("sex").toString());
                ui->tableWidget->item(i,4)->setText(hash.value("loginCount").toString());
                ui->tableWidget->item(i,5)->setText(hash.value("datestring").toString());
                ui->tableWidget->item(i,6)->setText(hash.value("latestlogintime").toString());
                ui->tableWidget->item(i,7)->setText(hash.value("remarks").toString());
            }
        }
        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        qDebug().noquote()<<u8"用户表格更新";
    }
    else
    {
        qDebug().noquote()<<u8"无用户";
    }
}
