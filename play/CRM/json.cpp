#include "json.h"
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QTextStream>
json::json(const QString& fileName)
{
    m_FileName = fileName;
}

bool json::parseJsonFile(const QString& fileName)
{
    if(!QFile::exists(fileName))
    {
        qDebug().noquote()<<QString("文件%1不存在");
        return false;
    }
    QString data;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        data = file.readAll();
        file.close();
    }
    QJsonDocument jsonDocument;
    QJsonParseError jsonerror;
    jsonDocument = QJsonDocument::fromJson(data.toUtf8(), &jsonerror);
    if(jsonerror.error != QJsonParseError::NoError)
    {
        qDebug()<<u8"json格式错误";
        return false;
    }
    else
    {
        QJsonObject root = jsonDocument.object();
        QJsonObject tableObject = root.value("table").toObject();
        for(int i=0; i<tableObject.size(); i++)
        {
            QJsonValue userValue = tableObject.value("User");
            if(userValue.isArray())
            {
                QJsonArray userArray = userValue.toArray();
                for(int j=0; j<userArray.size();j++)
                {
                   m_UserList<<userArray.at(i).toString();
                }
            }
        }
    }
    return true;
}
