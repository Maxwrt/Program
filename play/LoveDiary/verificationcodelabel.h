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
    //����һ���ַ�������ĸһ�ɶ����մ�д���أ�
    QString getVerificationCode() const;

protected:
    //��д�����¼�,�Դ���������֤��
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void slt_reflushVerification();

private:
    const int letter_number = 4;
    int noice_point_number ;//��������
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
