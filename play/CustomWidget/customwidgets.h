/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QObject>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpinBox>
#include <QRegExpValidator>
#include <QValidator>
#include <QString>
#include <QtWidgets/QWidget>

class MyTextEdit: public QPlainTextEdit
{
    Q_OBJECT
public:

};

class HexSpinBox: public QSpinBox
{
public:
    HexSpinBox(QWidget *parent = 0);

protected:
    QValidator::State validate(QString &input, int &pos) const;
    int valueFromText(const QString &text) const;
    QString textFromValue(int val) const;

private:
    QRegExpValidator *validator;
};

#endif // CUSTOMWIDGETS_H
