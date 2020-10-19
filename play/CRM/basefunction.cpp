#include "basefunction.h"
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QTextStream>
#include <QDateTime>
#include <QIODevice>
#include <QDomDocument>
#include <QTreeWidgetItem>
#include <QCoreApplication>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QTime>
#include <QEventLoop>

BaseFunction::BaseFunction()
{

}

bool BaseFunction::parseXmlFile(QTreeWidget *treewidget, const QString &filename)
{
    if(!QFile::exists(filename))
    {
        qDebug()<<tr("%1 not exist").arg(filename);
        return false;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<tr("open %1 failed").arg(filename);
        return false;
    }

    QDomDocument dom;
    QString errmsg=QString::null;
    int row=0;
    int col=0;
    if(!dom.setContent(&file, &errmsg, &row, &col))
    {
        qDebug()<<tr("parse error at %1,%2,%3").arg(row).arg(col).arg(errmsg);
        return false;
    }
    QDomElement root=dom.documentElement();
    if(root.tagName()!= "earth")
    {
        qDebug()<<tr("%1 shuxing error").arg(filename);
        return false;
    }
    parseRootElement(treewidget,root.toElement());
    file.close();
    return true;
}

void BaseFunction::parseRootElement(QTreeWidget *treewidget, const QDomElement &element)
{
    QDomNode child=element.firstChild();
    while(!child.isNull())
    {
        if(child.toElement().tagName()=="Country")
            parseCountryElement(treewidget, child.toElement());
        child=child.nextSibling();
    }
    return;
}

void BaseFunction::parseCountryElement(QTreeWidget *treewidget, const QDomElement &element)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(treewidget);
    QString countryName=element.attribute("name");
    item->setText(0,countryName);

    QDomNode child=element.firstChild();
    while(!child.isNull())
    {
        if(child.toElement().tagName()=="Area")
        {
            parseAreaElement(item, child.toElement());
        }
        child=child.nextSibling();
    }
    return;
}

void BaseFunction::parseAreaElement(QTreeWidgetItem *parent, const QDomElement &element)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    QString areaName=element.attribute("name");
    item->setText(0, areaName);

    QDomNode child=element.firstChild();
    while(!child.isNull())
    {
        if(child.toElement().tagName()=="province")
        {
            parseProvinceElement(item, child.toElement());
        }
        child=child.nextSibling();
    }
}

void BaseFunction::parseProvinceElement(QTreeWidgetItem *parent, const QDomElement &element)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    QString provinceName=element.attribute("name");
    item->setText(0, provinceName);
    return;
}


QSqlDatabase BaseFunction::createdb()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db=QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db=QSqlDatabase::addDatabase("QSQLITE");
    }
    QString filename=qApp->applicationDirPath()+"/./config/CustomerManageSystem.db";
    if(QFile::exists(filename))
    {
        db.setDatabaseName(filename);
        qDebug(u8"获取数据库：CustomerManageSystem.db：内容");
    }
    else
    {
        db.setDatabaseName(qApp->applicationDirPath()+"/data.db");
        qDebug(u8"获取数据库：data.db：内容");
    }
    return db;
}

void BaseFunction::noMoreMemory()
{
    qDebug()<<"Unable to satisfy request for memory";
    abort();
}

void BaseFunction::delay(int mesc)
{
    QTime time=QTime::currentTime().addMSecs(mesc*1000);
    while(QTime::currentTime()<time)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

void BaseFunction::delay_suspend(int mesc)
{
    QTime time=QTime::currentTime();
    QTime currentTime;
    do{
        currentTime=QTime::currentTime();
    }while(time.msecsTo(currentTime)<=(mesc*1000));
}


QSqlDatabase BaseFunction::createSqldb()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    QString dsn="DRIVER={SQL SERVER};SERVER=localhost;DATABASE=master";
    db.setDatabaseName(dsn);
    return db;
}

#if 0
QString BaseFunction::getJianPin(QString str)
{
    QByteArray arr;
    QString jianPin;
    for(int i=0; i<str.size(); i++)
    {
        QString str1 = str.at(i);
        arr = str1.toLocal8Bit();
        if(arr.size()<2)
        {
            jianPin.append(arr);
            continue;
        }
        else
        {
            wchar_t wchr = 0;
            wchr =  (arr[0]  &  0xff)  <<  8;
            wchr |= (arr[1]  &  0xff);
            char ch = get_first_letter(wchr);
            jianPin.append(ch);
        }
    }
    return jianPin.toLower();
}

bool BaseFunction::between(wchar_t start,wchar_t end,wchar_t aim)
{
    if (start <= aim && aim <= end)
    {
        return true;
    }
    return false;
}

char BaseFunction::get_first_letter(wchar_t wchar)
{
    if  (between(0xB0A1,0xB0C4,wchar))  return  'a';
    if  (between(0XB0C5,0XB2C0,wchar))  return  'b';
    if  (between(0xB2C1,0xB4ED,wchar))  return  'c';
    if  (between(0xB4EE,0xB6E9,wchar))  return  'd';
    if  (between(0xB6EA,0xB7A1,wchar))  return  'e';
    if  (between(0xB7A2,0xB8c0,wchar))  return  'f';
    if  (between(0xB8C1,0xB9FD,wchar))  return  'g';
    if  (between(0xB9FE,0xBBF6,wchar))  return  'h';
    if  (between(0xBBF7,0xBFA5,wchar))  return  'j';
    if  (between(0xBFA6,0xC0AB,wchar))  return  'k';
    if  (between(0xC0AC,0xC2E7,wchar))  return  'l';
    if  (between(0xC2E8,0xC4C2,wchar))  return  'm';
    if  (between(0xC4C3,0xC5B5,wchar))  return  'n';
    if  (between(0xC5B6,0xC5BD,wchar))  return  'o';
    if  (between(0xC5BE,0xC6D9,wchar))  return  'p';
    if  (between(0xC6DA,0xC8BA,wchar))  return  'q';
    if  (between(0xC8BB,0xC8F5,wchar))  return  'r';
    if  (between(0xC8F6,0xCBF0,wchar))  return  's';
    if  (between(0xCBFA,0xCDD9,wchar))  return  't';
    if  (between(0xCDDA,0xCEF3,wchar))  return  'w';
    if  (between(0xCEF4,0xD188,wchar))  return  'x';
    if  (between(0xD1B9,0xD4D0,wchar))  return  'y';
    if  (between(0xD4D1,0xD7F9,wchar))  return  'z';
    return  '\0';
}
#endif
