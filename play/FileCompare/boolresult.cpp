#include "boolresult.h"
#include "common.h"
BoolResultPrivate::BoolResultPrivate()
{
    QString hanzi = QStringLiteral("ÍõÈðÍ¤");
    hanzi = GetJianPin(hanzi);
}

BoolResultPrivate::~BoolResultPrivate()
{

}

BoolResult::BoolResult()
{
    m_pdata = QSharedPointer<BoolResultPrivate>(new BoolResultPrivate());
    m_pdata->m_flag = false;
    m_pdata->m_msg = QString::null;
    m_pdata->m_ret = 0;
}

BoolResult::BoolResult(bool flag, int ret, QString msg)
{
    m_pdata = QSharedPointer<BoolResultPrivate>(new BoolResultPrivate());
    m_pdata->m_flag = flag;
    m_pdata->m_msg = msg;
    m_pdata->m_ret = ret;
}

BoolResult::BoolResult(const BoolResult& other)
{
    m_pdata = QSharedPointer<BoolResultPrivate>(new BoolResultPrivate());
    m_pdata->m_flag = other.m_pdata->m_flag;
    m_pdata->m_msg = other.m_pdata->m_msg;
    m_pdata->m_ret = other.m_pdata->m_ret;
}

BoolResult::BoolResult(bool flag)
{
    m_pdata = QSharedPointer<BoolResultPrivate>(new BoolResultPrivate());
    m_pdata->m_flag = flag;
    m_pdata->m_msg = QString::null;
    m_pdata->m_ret = 0;
}

BoolResult::~BoolResult()
{
//    if(m_pdata)
//    {
//        delete m_pdata;
//        m_pdata = nullptr;
//    }
}

BoolResult& BoolResult::operator =(const BoolResult& other)
{
    if(this == &other)
    {
        return *this;
    }
    m_pdata->m_flag = other.m_pdata->m_flag;
    m_pdata->m_msg = other.m_pdata->m_msg;
    m_pdata->m_ret = other.m_pdata->m_ret;
    return *this;
}

void BoolResult::setDataMember(const bool& flag, const int& ret, const QString& msg)
{
    m_pdata->m_flag = flag;
    m_pdata->m_msg = msg;
    m_pdata->m_ret = ret;
}
