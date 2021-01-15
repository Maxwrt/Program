/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef JSON_H
#define JSON_H
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QStringList>
class json
{
public:
    json(const QString& fileName);

private:
    bool parseJsonFile(const QString& fileName);
private:
    QJsonObject m_JsonObject;
    QStringList m_UserList;
    QString m_FileName;
};

#endif // JSON_H
