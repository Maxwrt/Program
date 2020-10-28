#include "common.h"
#include "test.cpp"
#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QMap>
#include <QDateTime>
#include <QDate>
#include <cmath>
#include <fstream>
#include <QTime>
#include <vector>
#include <iostream>
//读取txt文件到QString
QString UtReadTxtFileToQString(const QString &filenamestr, const QString &encodestr)
{
    QString textstr=QString::null;
    QFile file(filenamestr);
    if (!file.exists())
    {
        qDebug() << filenamestr << u8"不存在";
        return textstr;
    }
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out.setCodec(encodestr.toLocal8Bit());
        textstr=out.readAll();
        file.close();
    }
    return textstr;
}

void setValue(QStringList::iterator iter)
{
    (*iter) += QString("_oldbak");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#if 0
    QString content = UtReadTxtFileToQString(QStringLiteral("./config/wfrstartui.ini"), QStringLiteral("gb18030"));
    qDebug() << content;

    QStringList alllist = content.split('\n', QString::SkipEmptyParts);
    qDebug() << alllist;

    for(QString line : alllist)
    {
        qDebug() << line;
    }


    /**one****************************测试迭代器是否可以修改指向的容器变量************************************/
    QStringList testlist;
    testlist << "wrt" << "sn" << "jerry" << "tom";
    qDebug() <<"old:    " <<testlist;
    QStringList::iterator iter = testlist.begin();
    while(iter != testlist.end())
    {
        (*iter) += QString("_bak");
        iter++;
    }
    qDebug() << "new one:   "<<testlist;

    iter = testlist.begin();
    while(iter != testlist.end())
    {
        setValue(iter);
        iter++;
    }
    qDebug() << "new two:   "<<testlist;
    /******************************测试迭代器是否可以修改指向的容器变量***************************************/

    /**two************************测试容器不存在的键的默认值多少，qint64的值默认返回0**************************/
    QMap<QString, qint64> map;
    map.insert("one", 1);
    qDebug() << map.value("one") << " : " << map.value("two", -1) << " : " << map["three"];
    /**************************测试容器不存在的键的默认值多少，qint64的值默认返回0*****************************/

    /**three******************************测试if~else if控制语句的程序流向**********************************/
    int one = 1;
    int two = 2;

    if (1 == one)
    {
        qDebug() << "one";
    }
    else if (2 == two)
    {
        qDebug() << "two";
    }
    else
    {
        qDebug() << "other number";
    }
    /*******************************测试if~else if控制语句的程序流向****************************************/
#endif
    /**four**************************************计算两个日期差************************************************/
    QDateTime datetime(QDate(2020, 9, 4), QTime(21, 9, 9));

    QString str = gbk2string("双节同庆~~~~祝各位和国青一样有钱");
    OUT << str.count();
    QString heart = DrawHeart(str, OTHERS, datetime, true);
    QFile file("./heart.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream write(&file);
        write.setCodec("UTF-8");
        write << heart;
        file.close();
    }
    /****************************************计算两个日期差************************************************/
//    std::ofstream fread;
//    fread.open("./heart.txt", std::ios_base::out | std::ios_base::trunc);
//    fread << "wrt";

    std::vector<int> ivector(10);
    ivector.emplace_back(1);

    /****************************************测试虚函数************************************************/
    Animal animal("动物");
    Cat    cat("猫");
    animal.say();
    cat.say();
    OUT << gbk2string(animal.getname());
    OUT << gbk2string(cat.getname());
    /****************************************测试虚函数************************************************/

    return a.exec();
}
