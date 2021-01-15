/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef VERIFICATIONCODELABEL_H
#define VERIFICATIONCODELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QChar>
#include <QColor>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTextStream>
#include <QPushButton>
#include <QBitmap>
#include <QPointer>
class SignInButton: public QPushButton
{
    Q_OBJECT
public:
    SignInButton(QWidget *parent):QPushButton(parent)
    {
        setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground, true);
    }
    virtual void paintEvent(QPaintEvent *event);
};

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    ImageLabel(QWidget *parent):QLabel(parent){}
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();
};

class VerificationCodeLabel : public QLabel
{
    Q_OBJECT

public:
    VerificationCodeLabel(QWidget *parent=0);
    ~VerificationCodeLabel();
    //返回一个字符串（字母一律都按照大写返回）
    QString getVerificationCode() const;

    QString Text() const
    {
        return m_code;
    }

protected:
    //重写绘制事件,以此来生成验证码
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private slots:
    void Repaint();

signals:
    void clicked();
    void textchanged();

private:
    const int m_letter_number = 4;
    int m_noice_point_number ;//噪点的数量
    enum class TYPE
    {
        NUMBER_FLAG,
        UPLETTER_FLAG,
        LOWLETTER_FLAG
    };
    void produceVerificationCode() const;
    QChar produceRandomLetter() const;
    void produceRandomColor() const;

    QChar *m_verificationCode;
    QString m_code;
    QColor *m_colorArray;
    bool m_ifgenerate;
};
#endif // VERIFICATIONCODELABEL_H
