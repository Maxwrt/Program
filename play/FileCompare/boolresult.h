/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef BOOLRESULT_H
#define BOOLRESULT_H

#include <QString>
#include <QSharedPointer>

class BoolResultPrivate
{
public:
    BoolResultPrivate();
    ~BoolResultPrivate();
    friend class BoolResult;

private:
    bool m_flag;
    QString m_msg;
    int  m_ret;
};


class BoolResult
{
public:
    BoolResult();
    BoolResult(bool flag, int ret, QString msg);
    BoolResult(const BoolResult& other);
    BoolResult(bool flag);
//    BoolResult(QString msg);
    ~BoolResult();

    BoolResult& operator =(const BoolResult& other);
    void setDataMember(const bool& flag, const int& ret, const QString& msg);

    inline bool& getFlag() const
    {
        return m_pdata->m_flag;
    }

    inline int& getRet() const
    {
        return m_pdata->m_ret;
    }

    inline QString& getMsg() const
    {
        return m_pdata->m_msg;
    }

    inline operator bool()
    {
        return m_pdata->m_flag;
    }

private:
    QSharedPointer<BoolResultPrivate> m_pdata;
};

#endif // BOOLRESULT_H
