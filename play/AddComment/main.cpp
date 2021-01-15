#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include "addcomment.h"
#include "common.h"
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    SetAppLogName(QStringLiteral("AddComment"));
    qInstallMessageHandler(AppLog);

    QString path = "D:\\2020\\WRT\\Program\\play";
    QString time = QDateTime::currentDateTime().toString("yyyy.MM.dd");
    QString author = QString::fromLocal8Bit("王瑞亭");
    QString function = QString::fromLocal8Bit("**");

    if (argc > 1)
    {
        if (argc < 3)
            path = argv[1];
        else if (argc < 4)
            time = argv[2];
        else if (argc < 5)
            author = argv[3];
        else if (argc < 6)
            function = argv[4];
    }

    AddComment::PrintMenu();

    while(true)
    {
        QTextStream read(stdin);
        QTextStream(stdout) << QString::fromLocal8Bit("靓仔@ATCCS01A#");
        QString operate = read.readLine();
        if ((QStringLiteral("print") == operate) || QStringLiteral("p") == operate)
            AddComment::PrintMenu();
        else if (QStringLiteral("exit") == operate || QStringLiteral("e") == operate)
        {
                QTextStream(stdout) << QString::fromLocal8Bit("关机，下次见");
                break;
        }
        else if (QStringLiteral("fire") == operate || QStringLiteral("f") == operate)
        {
            AddComment::Init(path, time, author, function);
            if(AddComment::Init()->Start())
                QTextStream(stdout) << QString::fromLocal8Bit("写入注释成功");
        }
        else if (QStringLiteral("vim") == operate || QStringLiteral("v") == operate)
        {
            QTextStream(stdout) << QString::fromLocal8Bit("参数顺序：path->time->author->function\n");
            QTextStream(stdout) << QString::fromLocal8Bit("靓仔@ATCCS01A#");
            QStringList argv = read.readLine().split(' ', QString::SkipEmptyParts);
            int count = argv.count();
            if (count>1)
                path = argv[0];
            else if (count>2)
                time = argv[1];
            else if (argc>3)
                author = argv[2];
            else if (argc>4)
                function = argv[3];
            else
                ;
        }
        else if (QStringLiteral("check") == operate || QStringLiteral("c") == operate)
            QTextStream(stdout) << "time:" << time << " author:" << author << " function:" << function << "\n";
        else if (QStringLiteral("tips") == operate || QStringLiteral("t") == operate)
            QTextStream(stdout) << QString::fromLocal8Bit("用法：AddComment  Path[File] Time Author Function"\
                                                          "例子：AddComment  C:/wrt/Program/[C:/wrt/Program/test.h] 2021.01.13 小王同学 添加注释\n");
        else
        {
            QTextStream(stdout) << QString::fromLocal8Bit("输入选项不合法\n");
            AddComment::PrintMenu();
        }
    }
    app.exec();
    return 0;
}

