#include "base.h"
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#include <QStringList>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QByteArray>
#include <QMessageBox>
#include <QHeaderView>
#include <QFileInfo>

Base::Base()
{
    readText();
    createDB();
}

QString Base::buildLogDir()
{
    QString dirName = QDir::currentPath()+"/log/";
    if(!QDir().exists(dirName))
    {
        QDir dir;
        dir.mkdir(dirName);
    }
    QString fileName;
    fileName = QString("%1%2.log").arg(dirName).arg(QDateTime::currentDateTime().toString("yyyy_MM_dd"));
    return fileName;
}

void Base::removeFile(QString fileName)
{
    QFileInfo fileInfo(fileName);
    QDir dir=fileInfo.dir();
    QFileInfoList fileInfoList = dir.entryInfoList();
    for(int i=0; i<fileInfoList.count();i++)
    {
        QFileInfo file = fileInfoList.at(i);
        if(file.isFile())
        {
            if(file.lastModified().daysTo(QDateTime::currentDateTime())>30 || file.size()>2*10*1024*1024)
            {
                dir.remove(file.fileName());
            }
        }
    }
}

void Base::log(QtMsgType type, const QMessageLogContext &content, const QString &msg)
{
    if(msg.isEmpty())
        return;
    QString fileName;
    fileName = buildLogDir();

    removeFile(fileName);
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream write(&file);
        QString errorFile=QString(content.file).mid(QString(content.file).lastIndexOf("\\"));
        QString msgStr;
        int errorLine=content.line;
        QString dateStr = QDateTime::currentDateTime().toString("yyyy_MM_dd hh:mm:ss zzz");
        switch(type)
        {
        case QtDebugMsg:
            msgStr += dateStr + QString(" %1 %2: ").arg(errorFile).arg(errorLine) + msg + "\r\n";
            break;
        case QtWarningMsg:
            msgStr += dateStr + QString(" %1 %2: ").arg(errorFile).arg(errorLine) + msg + "\r\n";
            break;
        case QtCriticalMsg:
            msgStr += dateStr + QString(" %1 %2: ").arg(errorFile).arg(errorLine) + msg + "\r\n";
            break;
        case QtFatalMsg:
            msgStr += dateStr + QString(" %1 %2: ").arg(errorFile).arg(errorLine) + msg + "\r\n";
            break;
        case QtInfoMsg:
            msgStr += dateStr + QString(" %1 %2: ").arg(errorFile).arg(errorLine) + msg + "\r\n";
            break;
        }
        if(!msgStr.isEmpty())
        {
            write<<msgStr;
        }
        file.close();
    }
    return;
}


bool Base::createDB()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
    }
    m_db.setDatabaseName("./data.db");
    return true;
}

QVariantList Base::selectTable(const QString sql, const QString tableName)
{
    QStringList columnList;
    if(tableName == "staff")
    {
        columnList = m_staff_head_list;
    }
    else if(tableName == "boy")
    {
        columnList = m_boy_head_list;
    }
    else if(tableName == "girl")
    {
        columnList = m_girl_head_list;
    }
    else if(tableName == "age")
    {
        columnList = m_age_head_list;
    }
    QVariantList dataList;
    if(m_db.isValid() && m_db.open())
    {
        QSqlQuery query;
        query.prepare(sql);
        if(query.exec())
        {
            QVariantHash hash;
            while(query.next())
            {
                for(int i=0; i<columnList.count(); i++)
                {
                    hash.insert(columnList.at(i), query.value(columnList.at(i)).toString());
                }
                if(hash.count()>0)
                {
                    dataList<<hash;
                    hash.clear();
                }
            }
        }
        else
        {
            qDebug().noquote()<<query.lastError();
        }
        m_db.close();
    }

    return dataList;
}


QVariantList Base::readText()
{
    QVariantList allTableInfo;
    QString fileName="./data.txt";
    QFile file(fileName);
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream read(&file);
            QVariantHash hash;

            while(!read.atEnd())
            {
                QString msg = read.readLine().simplified();
                if(msg.isEmpty())
                    continue;
                QStringList fields = msg.split(';');
                for(int i=0; i<fields.count(); i++)
                {
                    QString field = fields.at(i);
                    QStringList content = field.split('=');
                    if(content.count()>1)
                        hash.insert(content.at(0), content.at(1));
                }
                if(hash.count()>0)
                {
                    allTableInfo<<hash;
                    if(hash.value("table").toString()=="apartment")
                        m_apartment_list<<hash;
                    if(hash.value("table").toString()=="staff")
                        m_staff_head_list<<hash.value("desc").toString();
                    if(hash.value("table").toString()=="boy")
                        m_boy_head_list<<hash.value("desc").toString();
                    if(hash.value("table").toString()=="girl")
                        m_girl_head_list<<hash.value("desc").toString();
                    if(hash.value("table").toString()=="age")
                        m_age_head_list<<hash.value("desc").toString();
                    hash.clear();
                }
            }
        }
        else
        {
            qDebug().noquote()<<QString("open %1 failed").arg(fileName);
        }
    }
    else
    {
        qDebug()<<QString("%1 not exists").arg(fileName);
    }
    return allTableInfo;
}

QStandardItemModel* Base::createTable(QTableView *tableView, const QString& tableName)
{
    QStandardItemModel *tablemodel = new QStandardItemModel(tableView);
    tableView->setModel(tablemodel);
    if(m_staff_head_list.count()>0 && tableName == "staff")
    {
        tablemodel->setHorizontalHeaderLabels(m_staff_head_list);
    }
    else if(m_boy_head_list.count()>0 && tableName == "boy")
    {
        tablemodel->setHorizontalHeaderLabels(m_boy_head_list);
    }
    else if(m_girl_head_list.count()>0 && tableName == "girl")
    {
        tablemodel->setHorizontalHeaderLabels(m_girl_head_list);
    }
    else if(m_age_head_list.count()>0 && tableName == "age")
    {
        tablemodel->setHorizontalHeaderLabels(m_age_head_list);
    }
    tableView->horizontalHeader()->setStretchLastSection(true);
    if(tableName == "staff")
    {
        ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate();
        tableView->setItemDelegateForColumn(0, readOnlyDelegate);
    }
    return tablemodel;
}

bool Base::updateTable(QStandardItemModel *tablemodel, QTableView *tableView,const QVariantList &dataList,const QString &tableName)
{
    tablemodel->setRowCount(0);
    QStringList columnList;
    if(tableName == "staff")
    {
        columnList = m_staff_head_list;
    }
    else if(tableName == "boy")
    {
        columnList = m_boy_head_list;
    }
    else if(tableName == "girl")
    {
        columnList = m_girl_head_list;
    }
    else if(tableName == "age")
    {
        columnList = m_age_head_list;
    }

    if(dataList.count() > 0 && columnList.count()>0)
    {
        if(tablemodel->rowCount()<dataList.count())
            tablemodel->setRowCount(dataList.count());
        QVariantHash hash;
        for(int i=0; i<dataList.count(); i++)
        {
            hash=dataList.at(i).toHash();
            for(int j=0; j<columnList.count(); j++)
            {
                tablemodel->setData(tablemodel->index(i,j),hash.value(columnList.at(j)));
            }
        }
        return true;
    }
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->resizeColumnsToContents();
    return false;
}


QString Base::getHanZiJianPin(QString str)
{
    QString retstr;
    if(str.isEmpty())
    {
        qDebug().noquote()<<QString("%1 is empty").arg(str);
        return retstr;
    }

    retstr = getJianPin(str);
    return retstr;
}

QString Base::getJianPin(const  QString &hanzistr)
{
    QString retstr;
    for (int i=0; i<hanzistr.length(); i++)
    {
        QString str = hanzistr.at(i);
        QByteArray arr = str.toLocal8Bit();
        wchar_t wchr;

        if(arr.size() == 1)
        {
            retstr.append(arr);
        }
        else if(arr.size() == 2)
        {
            wchr = (arr.at(0) & 0xff) << 8;
            wchr |= (arr.at(1) & 0xff);

            char c = convert(wchr);
            if(c != 0)
            {
                retstr.append(c);
            }
        }
    }
    return retstr.toLower();
}

char Base::convert(wchar_t n)
{
    if(In(0xB0A1,0xB0C4,n))   return   'A';
    if(In(0XB0C5,0XB2C0,n))   return   'B';
    if(In(0xB2C1,0xB4ED,n))   return   'C';
    if(In(0xB4EE,0xB6E9,n))   return   'D';
    if(In(0xB6EA,0xB7A1,n))   return   'E';
    if(In(0xB7A2,0xB8c0,n))   return   'F';
    if(In(0xB8C1,0xB9FD,n))   return   'G';
    if(In(0xB9FE,0xBBF6,n))   return   'H';
    if(In(0xBBF7,0xBFA5,n))   return   'J';
    if(In(0xBFA6,0xC0AB,n))   return   'K';
    if(In(0xC0AC,0xC2E7,n))   return   'L';
    if(In(0xC2E8,0xC4C2,n))   return   'M';
    if(In(0xC4C3,0xC5B5,n))   return   'N';
    if(In(0xC5B6,0xC5BD,n))   return   'O';
    if(In(0xC5BE,0xC6D9,n))   return   'P';
    if(In(0xC6DA,0xC8BA,n))   return   'Q';
    if(In(0xC8BB,0xC8F5,n))   return   'R';
    if(In(0xC8F6,0xCBF0,n))   return   'S';
    if(In(0xCBFA,0xCDD9,n))   return   'T';
    if(In(0xCDDA,0xCEF3,n))   return   'W';
    if(In(0xCEF4,0xD188,n))   return   'X';
    if(In(0xD1B9,0xD4D0,n))   return   'Y';
    if(In(0xD4D1,0xD7F9,n))   return   'Z';
    return   '\0';
}

bool Base::In(wchar_t start, wchar_t end, wchar_t code)
{
    if(code >= start && code <= end)
        return true;
    return false;
}
