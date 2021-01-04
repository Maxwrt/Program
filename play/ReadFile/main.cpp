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
#include <QRegularExpression>
#include <QTextStream>
#include <QHostInfo>
#include <QHostAddress>
#include <QTimer>
//��ȡtxt�ļ���QString
QString UtReadTxtFileToQString(const QString &filenamestr, const QString &encodestr)
{
    QString textstr=QString::null;
    QFile file(filenamestr);
    if (!file.exists())
    {
        qDebug() << filenamestr << u8"������";
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

bool compare(const QHash<QString, QString>& first, const QHash<QString, QString>& second)
{
    QHash<QString, QString>::const_iterator itfirst = first.begin();
    QHash<QString, QString>::const_iterator itsecond = second.begin();
    return itfirst.key() < itsecond.key();
}

bool compareTwoFormula(QString dbformula, QString fformula)
{
    QStringList dblist = dbformula.split('!', QString::SkipEmptyParts);
    QStringList fflist = fformula.split('!', QString::SkipEmptyParts);
    QList<QHash<QString, QString>> dbparse;
    QList<QHash<QString, QString>> ffparse;
    if (dblist.size() != fflist.size()) //size()��ʾһ���豸��Լ����������
    {
        return false;
    }
    else
    {
        for (int i=0; i<dblist.size(); i++)
        {
            QHash<QString, QString> hash;
            QStringList dbformulalist = dblist.at(i).split(':');

            if (dbformulalist.size() == 2)
            {
                hash.insert(dbformulalist.at(0), dbformulalist.at(1));
                dbparse << hash;
            }
            else
            {
                return false;
            }

            hash.clear();
            QStringList fformulalist = fflist.at(i).split(':');

            if (fformulalist.size() == 2)
            {
                hash.insert(fformulalist.at(0), fformulalist.at(1));
                ffparse << hash;
            }
            else
            {
                return false;
            }
        }
    }
    qSort(dbparse.begin(), dbparse.end(), compare);
    qSort(ffparse.begin(), ffparse.end(), compare);
//    printList(dbparse, 1);
//    printList(ffparse, 0);
    for (int i=0; i<dbparse.size(); i++)
    {
        QHash<QString, QString>::const_iterator it = dbparse.at(i).begin();
        if (it.value() != ffparse.at(i).value(it.key()))
        {
            return false;
        }
    }
    return true;
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


    /**one****************************���Ե������Ƿ�����޸�ָ�����������************************************/
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
    /******************************���Ե������Ƿ�����޸�ָ�����������***************************************/

    /**two************************�������������ڵļ���Ĭ��ֵ���٣�qint64��ֵĬ�Ϸ���0**************************/
    QMap<QString, qint64> map;
    map.insert("one", 1);
    qDebug() << map.value("one") << " : " << map.value("two", -1) << " : " << map["three"];
    /**************************�������������ڵļ���Ĭ��ֵ���٣�qint64��ֵĬ�Ϸ���0*****************************/

    /**three******************************����if~else if�������ĳ�������**********************************/
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
    /*******************************����if~else if�������ĳ�������****************************************/

    /**four**************************************�����������ڲ�************************************************/
    QDateTime datetime(QDate(2020, 9, 4), QTime(21, 9, 9));

    QString str = gbk2string("˫��ͬ��~~~~ף��λ�͹���һ����Ǯ");
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
    /****************************************�����������ڲ�************************************************/
//    std::ofstream fread;
//    fread.open("./heart.txt", std::ios_base::out | std::ios_base::trunc);
//    fread << "wrt";

    std::vector<int> ivector(10);
    ivector.emplace_back(1);

    /****************************************�����麯��************************************************/
    Animal animal("����");
    Cat    cat("è");
    animal.say();
    cat.say();
    OUT << gbk2string(animal.getname());
    OUT << gbk2string(cat.getname());
    /****************************************�����麯��************************************************/

    /****************************************����remove************************************************/
    QString r = "Telephone@@";
    r.remove(QRegularExpression("[aeiou]."));//������ʽ��ʾƥ��aeiou�е�һ����������һ�ַ���ɵ��ַ���
    OUT << r;
    /****************************************����remove************************************************/

    /****************************************����\r(�س�), \n(����), \r\n(�س�+����)**********************/
    QTextStream(stdout) << "this is 1\r";
    QTextStream(stdout) << "this is 2\n";
    QTextStream(stdout) << "this is 3  ";
    QTextStream(stdout) << "this is 4\r\n";
    QStringList list = QString("wrt rwt trw").split(" ");
    OUT << list;
    list.removeAt(0);
    OUT << list;
    OUT << list.join(" ");
    OUT << QString("\"1wrt     su na wrt 111").remove(" ");
    OUT << QString("\"1wrt     su na wrt 111").remove("\"");
    OUT << QString("\"1wrt     su na wrt 111").simplified();

    QStringList list1 = QString("2!3!4!").split('!');
    OUT << "list1's size:" << list1.size();
    OUT << list1;
    OUT << list1.join(" ");

    compareTwoFormula("1:one!2:two!3:three!", "2:two!1:one!3:three");
    QString str1;
    QString str2;
    if (str1 == str2)
    {
        OUT << "wrt";
    }
    else
    {
        OUT << "wrt1";
    }
    QStringList strlist = QString("wrt love suna").split('!');
    OUT << "strlist's size: " << strlist.size() << "    content:    "<<strlist.at(0);

    QStringList list1;
    QStringList list2;
    QStringList list3;
    list1 << "3Ctwo+3" << "2Bone" << "1Athress";
    list2 << "3Ctwo+3" << "2Bone" << "1Athress";
    qSort(list1.begin(), list1.end());
    qSort(list2.begin(), list2.end());

    for (int i=0; i<list1.size(); i++)
    {
        if (list1.at(i).contains('+'))
        {
            OUT << "wrt";
        }
        if (list1.at(i) == list2.at(i))
            OUT << u8"���";
    }

    QStringList list4;
    QStringList list5;
    list4 << "wang" << "rui";
    list5 << "wang" << "rui";
    if (list4 == list5)
    {
        OUT << u8"QStringList���";
    }
    else
    {
        OUT << u8"QStringList�����";
    }
    QString str("H:231=1!L:232=0!");
    QStringList strlist;
    strlist = str.split('!');
    qDebug() << strlist;
    QString str1 = strlist.join('!');
    qDebug() << str1;

    list3 = QStringList() << "wang" << "rui" << "ting";
    qDebug() << list3;
    /****************************************����\r(�س�), \n(����), \r\n(�س�+����)**********************/

    /****************************************************�������õĴ�С���Ƿ�ռ���ڴ�**********************/
    int a1 = 10;
    int &aa = a1;
    OUT << u8"����ĵ�ַ:    "<<&a1 << u8"����Ĵ�С: "<<sizeof(a1);
    OUT << u8"���õĵ�ַ:    "<<&aa << u8"���õĴ�С: "<<sizeof(&aa);
    /****************************************************�������õĴ�С���Ƿ�ռ���ڴ�**********************/

    QTextStream read(stdin);
    while (true)
    {
        printMenu();
        QString what =  read.readLine().trimmed();
        if (!what.isEmpty())
        {
            if (what == QStringLiteral("getip"))
            {
                while (true)
                {
                    int count = 0;
                    foreach (QHostAddress address, QHostInfo::fromName(QHostInfo::localHostName()).addresses())
                    {
                        if (address.protocol() == QAbstractSocket::IPv4Protocol)
                        {
                            OUT << QDateTime::currentDateTime().toString("yyyy_MM_dd hh:mm ")<<u8"����IP: " << address.toString();
                            break;
                        }
                    }
                    Sleep(1000 * 60 * 2);
                    count++;
                    if (count > 2)
                        break;
                }
            }
            else if (what == QStringLiteral("getname"))
            {
                OUT << u8"����������: "<<QHostInfo::localHostName();
            }
            else if (what == QStringLiteral("quit"))
            {
                break;
            }
            else
            {
                OUT << QString(u8"û��%1��ѡ�����������").arg(what);
            }
        }
    }
    OUT << u8"�˳�";
#endif
    qDebug() << QString("\xE4\xB8\xA4") << "  size:   " << QString("\xE4\xB8\xA4").size();
    qDebug() << QString("��") << "   size: " << QString("��").size();

    return a.exec();
}
