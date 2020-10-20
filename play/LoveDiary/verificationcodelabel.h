#ifndef VERIFICATIONCODELABEL_H
#define VERIFICATIONCODELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QChar>
#include <QColor>

class VerificationCodeLabel : public QLabel
{
    Q_OBJECT

public:
    VerificationCodeLabel(QWidget *parent=0);
    ~VerificationCodeLabel();
    //返回一个字符串（字母一律都按照大写返回）
    QString getVerificationCode() const;

protected:
    //重写绘制事件,以此来生成验证码
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void slt_reflushVerification();

private:
    const int letter_number = 4;
    int noice_point_number ;//噪点的数量
    enum class TYPE
    {
        NUMBER_FLAG,
        UPLETTER_FLAG,
        LOWLETTER_FLAG
    };
    void produceVerificationCode() const;
    QChar produceRandomLetter() const;
    void produceRandomColor() const;

    QChar *verificationCode;
    QColor *colorArray;
};
#endif // VERIFICATIONCODELABEL_H
