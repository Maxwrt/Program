#include "verificationcodelabel.h"
#include <QPaintEvent>
#include <QPainter>
#include <QTime>
#include <QTextStream>
VerificationCodeLabel::VerificationCodeLabel(QWidget *parent)
    : QLabel(parent)
{
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    colorArray = new QColor[letter_number];
    verificationCode = new QChar[letter_number];
    noice_point_number = this->width();
    connect(this, &QLabel::linkActivated, this, [=]()->void
    {slt_reflushVerification();});
}

VerificationCodeLabel::~VerificationCodeLabel()
{
    if (colorArray != nullptr)
    {
        delete []colorArray;
        colorArray = nullptr;
    }

    if (verificationCode != nullptr)
    {
        delete []verificationCode;
        verificationCode = nullptr;
    }
}

void VerificationCodeLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPoint p;
    painter.fillRect(this->rect(), Qt::white);
    produceVerificationCode();
    produceRandomColor();

    //������֤��
    for (int i = 0; i < letter_number; ++i)
    {
        p.setX(i * (this->width() / letter_number) + this->width()/8);
        p.setY(this->height() / 2);
        painter.setPen(colorArray[i]);
        painter.drawText(p, QString(verificationCode[i]));
    }

    //�������
    for (int j = 0; j < noice_point_number; ++j) //noice_point_number��������
    {
        p.setX(qrand() % this->width());
        p.setY(qrand() % this->height());
        painter.setPen(colorArray[j % 4]);
        painter.drawPoint(p);
    }
    return;
}

//����һ������������֤��ĺ���
void VerificationCodeLabel::produceVerificationCode() const
{
    for (int i = 0; i < letter_number; ++i)
        verificationCode[i] = produceRandomLetter();
    return;
}

QChar VerificationCodeLabel::produceRandomLetter() const
{
    QChar c;
    int flag = qrand() % letter_number;
    switch (flag)
    {
    case TYPE::NUMBER_FLAG:
        c = '0' + qrand() % 10; break;
    case TYPE::UPLETTER_FLAG:
        c = 'A' + qrand() % 26; break;
    case TYPE::LOWLETTER_FLAG:
        c = 'a' + qrand() % 26; break;
    default:
        c = qrand() % 2 ? 'W' : 'S';
    }
    return c;
}

//�����������ɫ
void VerificationCodeLabel::produceRandomColor() const
{
    for (int i = 0; i < letter_number; ++i)
        colorArray[i] = QColor(qrand() % 255, qrand() % 255, qrand() % 255);
    return;
}

//����һ���ַ�������ĸһ�ɶ����մ�д���أ�
QString VerificationCodeLabel::getVerificationCode() const
{
    QString s;
    QChar cTemp;
    for (int i = 0; i < letter_number; ++i)
    {
        cTemp = verificationCode[i];
        s += cTemp>97 ? cTemp.toUpper() : cTemp;
    }
    return s;
}

//ˢ����֤�룬���û���ȷ����ʱ�������Ӧˢ��
void VerificationCodeLabel::slt_reflushVerification()
{
    QTextStream(stdout) << u8"ִ����";
    repaint();
}

