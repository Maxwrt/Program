#include "util.h"
#include "base.h"
#include <QDebug>
Util::Util()
{

}

void Util::loadDataSlot(const QString &departName)
{
    bool retFlag = loadData(departName);
    if(retFlag)
    {
        emit loadDataFinishSignal();
    }
}

bool Util::loadData(const QString &departName)
{
    Base base;
    QString sql=QString(u8"select * from staff where 所属部门='%1'").arg(departName);
    m_staff_list = base.selectTable(sql ,"staff");

    sql = QString(u8"select * from boy where 所属部门='%1'").arg(departName);
    m_boy_list = base.selectTable(sql, "boy");

    sql = QString(u8"select * from girl where 所属部门='%1'").arg(departName);
    m_girl_list = base.selectTable(sql, "girl");

    sql=QString(u8"select * from age where 所属部门='%1'").arg(departName);
    m_age_list = base.selectTable(sql ,"age");
    return true;
}
