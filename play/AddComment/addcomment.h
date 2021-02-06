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
                "** 版权所有: %1\n"\
                "** 版本号: %2\n"\
                "** 文件名: %3\n"\
                "** 时间: %4\n"\
                "** 作者: %5\n"\
                "** 功能: %6\n"\
                "** 其他: \n"\
                "** 修改记录: \n"\
                "****************************************************************************/\n")
#define PATH "./"
#define TIME (QDateTime::currentDateTime().toString("yyyy.mm.dd"))
#define AUTHOR (QString::fromLocal8Bit("小王同学"))
#define FUNCTION (QString::fromLocal8Bit("作用描述"))
#define PRINT QTextStream(stdout)

class AddComment : public QObject
{
    Q_OBJECT

public:
    enum OPRTTYPE
    {
      add = 0,
      del
    };
    static QPointer<AddComment> Inst(const QString& path = PATH,\
                                     const QString& time = TIME,\
                                     const QString& author = AUTHOR,\
                                     const QString& function = FUNCTION)
    {
        static QPointer<AddComment> ptr = QPointer<AddComment>(new AddComment(path, time, author, function));
        return ptr;
    }

    static void PrintMenu();
    ~AddComment()
    {
        if(AddComment::Inst())
            delete AddComment::Inst();
    }

    bool Start(OPRTTYPE type);

signals:

public slots:

private:
    explicit AddComment(const QString& path, const QString& time, const QString& author, const QString& function, QObject *parent = 0);
    bool LoadFiles(const QString& path);
    void DoWork();
    bool Comment(OPRTTYPE type = add);

private:
    QString m_copyright;
    QString m_version;
    QString m_filename;
    QString m_touchtime;
    QString m_author;
    QString m_function;
    QString m_other;
    QString m_editrecord;
    QString m_path;
    QStringList m_filelist;
};

#endif // ADDCOMMENT_H
