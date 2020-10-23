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
    //����һ���ַ�������ĸһ�ɶ����մ�д���أ�
    QString getVerificationCode() const;

    QString Text() const
    {
        return code;
    }

protected:
    //��д�����¼�,�Դ���������֤��
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private slots:
    void Repaint();

signals:
    void clicked();
    void textchanged();

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
    QString code;
    QColor *colorArray;
    bool ifgenerate;
};
#endif // VERIFICATIONCODELABEL_H
