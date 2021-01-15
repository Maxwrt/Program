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
{}

void AddComment::PrintMenu()
{
    QTextStream(stdout) << QString::fromLocal8Bit("1. print(p)打印菜单\n");
    QTextStream(stdout) << QString::fromLocal8Bit("2. check(c)检查参数\n");
    QTextStream(stdout) << QString::fromLocal8Bit("2. vim  (v)编辑参数\n");
    QTextStream(stdout) << QString::fromLocal8Bit("3. fire (f)开始执行\n");
    QTextStream(stdout) << QString::fromLocal8Bit("4. tips (t)提示信息\n");
    QTextStream(stdout) << QString::fromLocal8Bit("5. exit (e)退出程序\n");
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

bool AddComment::Start()
{
    DoWork();
    return WriteComment();
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

bool AddComment::WriteComment()
{
    if (m_filelist.count() < 1)
        return false;

    bool success = true;
    for (auto item : m_filelist)
    {
        QFile file(item);
        if (file.exists())
        {
            if (file.open(QFile::ReadWrite))
            {
                QTextStream stream(&file);
                QString alldata = stream.readAll();
                if (alldata.startsWith("/*****"))
                {
                    file.close();
                    continue;
                }
                stream.seek(0);
                stream << QString(COMMENT).arg(m_touchtime).arg(m_author).arg(m_function);
                stream << alldata;
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
