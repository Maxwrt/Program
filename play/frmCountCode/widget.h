/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include <QList>
#include <QWidget>
#include <QStringList>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    enum class OpType :int
    {
      openfile=0,
      opendir
    };
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void ShowWidget();

private slots:
    void on_pushButton_clear_clicked();
    void on_pushButton_exportfile_clicked();

private:
    void Init();
    void InitTableWidget();
    void InitOtherWidget();
    bool CheckFile(const QString& filename);
    void CountCode(const QString& filename);
    void CountCode(const QStringList& filelist, OpType type, QString dir = QString());
    void CountCode(const QString& filename, int &codeline, int &commentline, int &blankline);

private:
    Ui::Widget *ui;
    QStringList mlistFiles;
    QStringList mheadList;
    QString mfileFilter;
    QStringList  mcolumnWidth;
};

#endif // WIDGET_H
