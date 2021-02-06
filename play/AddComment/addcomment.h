/****************************************************************************
** ʱ�䣺2021.01.14
** ���ߣ�����ͤ
** ���ܣ�*��ע��*
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
                "** ��Ȩ����: %1\n"\
                "** �汾��: %2\n"\
                "** �ļ���: %3\n"\
                "** ʱ��: %4\n"\
                "** ����: %5\n"\
                "** ����: %6\n"\
                "** ����: \n"\
                "** �޸ļ�¼: \n"\
                "****************************************************************************/\n")
#define PATH "./"
#define TIME (QDateTime::currentDateTime().toString("yyyy.mm.dd"))
#define AUTHOR (QString::fromLocal8Bit("С��ͬѧ"))
#define FUNCTION (QString::fromLocal8Bit("��������"))
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
