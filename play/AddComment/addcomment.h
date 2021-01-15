/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：*加注释*
****************************************************************************/
#ifndef ADDCOMMENT_H
#define ADDCOMMENT_H
#include <QObject>
#include <QPointer>
#include <QString>
#include <QStringList>
#include <QDateTime>

#define COMMENT QString::fromLocal8Bit(\
                "/****************************************************************************\n"\
                "** 时间：%1\n"\
                "** 作者：%2\n"\
                "** 功能：%3\n"\
                "****************************************************************************/\n")
#define PATH "./"
#define TIME (QDateTime::currentDateTime().toString("yyyy.mm.dd"))
#define AUTHOR (QString::fromLocal8Bit("小王同学"))
#define FUNCTION (QString::fromLocal8Bit("作用描述"))

class AddComment : public QObject
{
    Q_OBJECT
public:
    static QPointer<AddComment> Inst(const QString& path = PATH,\
                                     const QString& time = TIME,\
                                     const QString& author = AUTHOR,\
                                     const QString& function = FUNCTION)
    {
        static AddComment *ptr = QPointer<AddComment>(new AddComment(path, time, author, function));
        return &ptr;
    }

    static void PrintMenu();
    ~AddComment()
    {
        if(AddComment::Inst())
            delete AddComment::Inst();
    }

    bool Start();

signals:

public slots:

private:
    explicit AddComment(const QString& path, const QString& time, const QString& author, const QString& function, QObject *parent = 0);
    bool LoadFiles(const QString& path);
    void DoWork();
    bool WriteComment();

private:
    QString m_touchtime;
    QString m_author;
    QString m_function;
    QString m_path;
    QStringList m_filelist;
};

#endif // ADDCOMMENT_H
