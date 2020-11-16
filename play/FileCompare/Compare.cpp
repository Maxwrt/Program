#include "Compare.h"
#include "boolresult.h"
#include "common.h"
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <QIODevice>
#include <QStringList>
#include <QDomDocument>
#include <QDomNode>
#include <QMessageBox>
#include <QMapIterator>
#include <QFileInfo>
#include <QThread>

Compare::Compare(QObject *parent)
    :QObject(parent)
{
    m_synchronize = false;
}

BoolResult Compare::compareStart(const QVariantHash& hash)
{
    OUT << "file:    " << __FILEW__ <<" function:    " << __FUNCTION__ << " id:   "<< QThread::currentThreadId();
    if (!m_ret_data.isEmpty())
    {
        m_ret_data.clear();
    }

    BoolResult ret;
    if(hash.count()>0)
    {
        QString fileName = hash.value("file").toString();
        m_dir = hash.value("dir").toString();
        m_synchronize = hash.value("bool").toBool();
        if(fileName.isEmpty())
        {
            OUT << tr("received fileName is empty, please check");
            return u8"记录信息的文件为空，请检查";
        }
        if(!m_synchronize)
        {
            ret = readTextFile(fileName);
        }
        else
        {
            OUT << tr("synchronized data");
        }
        compareAll(m_raw_data);
    }
    else
    {
        OUT << tr("received hash is empty, please check");
        return u8"参数hash的为空，请检查";
    }
    if(!hash.value("isbool", false).toBool())
        emit finishCompare(m_ret_data);
    else
        emit finishCompareToThread(m_ret_data);

    return true;
    //printMap(m_raw_map);
}

BoolResult Compare::readTextFile(const QString& fileName)
{
    if(!QFile::exists(fileName))
    {
        QMessageBox::information(NULL, QObject::tr("Tip"), QString(tr("file %1 not exist")).arg(fileName), QObject::tr("ok"));
        return false;
    }

//    QFileInfo fileInfo(fileName);
//    if(fileInfo.size() == 0)
//    {
//        QMessageBox::information(NULL, QObject::tr("Tip"), QString(tr("文件 %1 大小为0")).arg(fileName), QObject::tr("ok"));
//        return false;
//    }
    m_raw_data.clear();
    m_raw_map.clear();
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream read(&file);
        QString contentAll = read.readAll();
        QStringList lineList = contentAll.split("\n", QString::SkipEmptyParts);
        qSort(lineList.begin(), lineList.end());
        if(lineList.count() > 0)
        {
            for(int i=0; i<lineList.count(); i++)
            {
                QString line = lineList.at(i);
                if(line.isEmpty())
                    continue;
                line = line.simplified();
                QStringList fieldList = line.split(";");
                if(fieldList.count()>2)
                {
                    QVariantHash hash;
                    hash.insert("fileName", QVariant(m_dir % QStringLiteral("/") % fieldList.at(0)));
                    hash.insert("handwriteTagname", fieldList.at(1));
                    hash.insert("handwritePath", fieldList.at(2));
                    m_raw_data<<hash;
                    m_raw_map.insert(line, hash);
                }
            }
        }
        file.close();
    }
    else
    {
        OUT << QString(tr("open file %1 fail")).arg(fileName);
    }

    return m_raw_data.count()>0;
}

void Compare::compareAll(const QVariantList& rawDataList)
{
    if(rawDataList.count() > 0)
    {
        m_ret_data.clear();
        m_map.clear();
        for(int i=0; i<rawDataList.count(); i++)
        {
            QVariantHash hash;
            hash = rawDataList.at(i).toHash();
            hash = compareOne(hash);
            m_ret_data<<hash;
        }
        OUT << u8"比较结束";
    }
    else
    {
        OUT << tr("can't read raw dara or have compared you may compare repeatly");
    }
}

QVariantHash Compare::compareOne(const QVariantHash& hash)
{
    QString fileName = hash.value("fileName").toString();
    QString tagName = hash.value("handwriteTagname").toString().remove(QRegExp(QStringLiteral("\\s"))).toLower();
    QString rightPath = hash.value("handwritePath").toString().simplified();


    QString checkPath = parseXml(fileName, tagName, rightPath);
    bool isSame = false;
    if(!checkPath.isEmpty())
    {
        if(checkPath == rightPath)
        {
            isSame = true;
        }
    }
    QFileInfo fileInfo(fileName);
    QString combineString = fileInfo.fileName() % tagName;

    bool isExist = true;
    if(!m_map.contains(combineString))
    {
        m_map.insert(combineString, combineString);
        isExist = false;
    }
    QVariantHash rethash;
    rethash.insert("fileName", fileInfo.fileName());
    rethash.insert("handwriteTagname", tagName);
    rethash.insert("parsePath", checkPath);
    rethash.insert("handwritePath", rightPath);
    rethash.insert("isSame", isSame);
    rethash.insert("isExist", isExist);
    return rethash;
}

QString Compare::parseXml(const QString& fileName, const QString& tagName, const QString& rightPath)
{
    QString checkFile;
    m_file.setFileName(fileName);

    if(m_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString errorStr;
        int errorLine;
        int errorColumn;

        if(!m_doc.setContent(&m_file, false, &errorStr, &errorLine, &errorColumn))
        {
            OUT << tr("Parse error at line %1, column %2: %3:").arg(errorLine).arg(errorColumn).arg(errorStr);
            m_file.close();
            OUT << tr("error! file close");
            return checkFile;
        }
        QDomElement root = m_doc.documentElement();
        if(root.tagName() == QLatin1String("Project"))
        {
            QDomNode child = root.firstChild();
            while(!child.isNull())
            {
                QDomElement element = child.toElement();
                if(element.tagName() == QLatin1String("PropertyGroup"))
                {
                    QString tagNameContent = element.attribute(QStringLiteral("Condition"));
                    if(tagNameContent.toLower().contains(tagName) || tagNameContent == QString())
                    {
                        checkFile = parseTargetTagName(element, tagName, rightPath);
                        if(!checkFile.isEmpty())
                        {
                            break;
                        }
                    }
                }
                child = child.nextSibling();
            }
        }
        if(m_file.isOpen())
        {
            m_file.close();
        }
    }
    return checkFile;
}

QString Compare::parseTargetTagName(const QDomElement& element, const QString& tagName, const QString& rightPath)
{
    QString checkFile;
    QDomNode child = element.firstChild();
    while (!child.isNull())
    {
        QDomElement element = child.toElement();
        if( element.tagName() == QLatin1String("OutputPath") || \
            element.tagName() == QLatin1String("OutDir") &&     \
            element.attribute(QStringLiteral("Condition")).toLower().contains(tagName)
          )
        {
            checkFile = element.text();

            if(!checkFile.isEmpty())
            {
                if(m_synchronize && checkFile != rightPath)
                {
                    m_file.close();

                    QDomNode oldnode = child.firstChild();
                    child.firstChild().setNodeValue(rightPath);
                    QDomNode newnode = child.firstChild();
                    child.replaceChild(newnode, oldnode);

                    if(!m_file.open(QIODevice::WriteOnly))
                    {
                        OUT << tr("open file %1 fail").arg(m_file.fileName());
                        break;
                    }
                    QTextStream write(&m_file);
                    m_doc.save(write, 4);
                    m_file.close();
                    return child.toElement().text();
                }
                break;
            }
        }
        child = child.nextSibling();
    }
    return checkFile;
}
void Compare::printMap(const QMap<QString, QVariantHash>& map)
{
    foreach(QVariantHash hash, map)
    {
        OUT << tr("1:    %1").arg(hash.value("fileName").toString()) \
            << tr("2:    %2").arg(hash.value("handwriteTagname").toString()) \
            << tr("3:    %3").arg(hash.value("handwritePath").toString());
    }
}
