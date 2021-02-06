#include "addcomment.h"
#include "common.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>

AddComment::AddComment(const QString& path, const QString& time, const QString& author, const QString& function, QObject *parent)
    : m_path(path),
      m_touchtime(time),
      m_author(author),
      m_function(function),
      QObject(parent)
{
    m_copyright = QString::fromLocal8Bit("小王同学");
    m_version = QString("1.0.0");
}

void AddComment::PrintMenu()
{
    QTextStream(stdout) << QString::fromLocal8Bit("1. print(打印菜单)\n");
    QTextStream(stdout) << QString::fromLocal8Bit("2. check(检查参数)\n");
    QTextStream(stdout) << QString::fromLocal8Bit("2. vim  (编辑参数)\n");
    QTextStream(stdout) << QString::fromLocal8Bit("3. add  (添加注释)\n");
    QTextStream(stdout) << QString::fromLocal8Bit("3. del  (删除注释)\n");
    QTextStream(stdout) << QString::fromLocal8Bit("4. tips (提示信息)\n");
    QTextStream(stdout) << QString::fromLocal8Bit("5. init6 (退出程序)\n");
}

bool AddComment::LoadFiles(const QString& path)
{
    QFileInfo fileinfo(path);
    if (fileinfo.isDir())
    {
        foreach (auto item, QDir(path).entryInfoList(QDir::Dirs | QDir::Files |QDir::NoDotAndDotDot, QDir::Time))
        {
            if (item.isDir())
                LoadFiles(item.absoluteFilePath());
            else if (item.isFile())
            {
                if (item.fileName().endsWith(".h"))
                    m_filelist << item.absoluteFilePath();
            }
        }
    }
    else if(fileinfo.isFile())
    {
        if (fileinfo.fileName().endsWith(".h"))
            m_filelist << fileinfo.absoluteFilePath();
    }
    return m_filelist.count() > 0;
}

bool AddComment::Start(OPRTTYPE type)
{
    DoWork();
    return Comment(type);
}

void AddComment::DoWork()
{
    if (m_path.isEmpty())
        return;

    bool ret = false;
    ret = LoadFiles(m_path);
    if (!ret)
    {
        OUT << QString::fromLocal8Bit("无有效文件");
        QCoreApplication::instance()->exit(0);
    }
    else
    {
        OUT << QString::fromLocal8Bit("加载文件成功");
    }
}

bool AddComment::Comment(OPRTTYPE type)
{
    if (m_filelist.count() < 1)
        return false;

    bool success = true;
    for (auto item : m_filelist)
    {
        QFile file(item);
        m_filename = file.fileName();
        if (file.exists())
        {
            if (file.open(QFile::ReadWrite))
            {
                QTextStream stream(&file);
                QString data;
                QString alldata;
                switch(type)
                {
                case add:
                    alldata = stream.readAll();
                    if (alldata.startsWith("/*****"))
                    {
                        file.close();
                        continue;
                    }
                    stream.seek(0);
                    stream << QString(COMMENT).arg(m_copyright).arg(m_version).arg(m_filename) \
                                              .arg(m_touchtime).arg(m_author).arg(m_function);
                    stream << alldata;
                    break;
                case del:
                    while(!stream.atEnd())
                    {
                        data = stream.readLine();
                        if(data.endsWith("*****/"))
                        {
                            stream.seek(stream.pos());
                            break;
                        }
                    }
                    data = stream.readAll();
                    stream << data;

                    break;
                default:
                    OUT << QString::fromLocal8Bit("未知操作");
                    break;
                }
            }
            else
            {
                success = false;
                OUT << QString::fromLocal8Bit("打开文件%1失败").arg(item);
            }
            file.close();
        }
        else
        {
            success = false;
            OUT << QString::fromLocal8Bit("%1不存在").arg(item);
        }
    }
    return success;
}
