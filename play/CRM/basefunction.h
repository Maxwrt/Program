#ifndef BASEFUNCTION_H
#define BASEFUNCTION_H
#include <QString>
#include <QObject>
#include <QDomDocument>
#include <QTreeWidget>
#include <QSqlDatabase>
#include <iostream>
#include <sstream>
#include <string>
#include <QDebug>
class BaseFunction: public QObject
{
public:
    static bool parseXmlFile(QTreeWidget *treewidget, const QString& filename);
    static void noMoreMemory();
    static void delay_suspend(int mesc);
    static void delay(int mesc);
    static QSqlDatabase createdb();
    static QSqlDatabase createSqldb();

#if 0
    static bool between(wchar_t start,wchar_t end,wchar_t aim);
    static char get_first_letter(wchar_t wchar);
    static QString getJianPin(QString str);
#endif

    template<typename resultT>
    static resultT stringToNumber(std::string str)
    {
        std::istringstream istring(str);
        resultT val;
        istring>>val;
        return val;
    }

    template<typename argT>
    static std::string NumberToString(argT val)
    {
        std::ostringstream ostring;
        ostring<<val;
        return ostring.str();
    }

protected:
    BaseFunction();

private:
    static void parseRootElement(QTreeWidget *treewidget, const QDomElement& element);
    static void parseCountryElement(QTreeWidget *treewidget, const QDomElement& element);
    static void parseAreaElement(QTreeWidgetItem *parent, const QDomElement& element);
    static void parseProvinceElement(QTreeWidgetItem *parent, const QDomElement& element);
};



#endif // BASEFUNCTION_H
