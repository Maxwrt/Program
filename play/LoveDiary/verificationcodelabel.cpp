#include "verificationcodelabel.h"
#include <QPaintEvent>
#include <QPainter>
#include <QTime>
#include <QTextStream>
#include <QPixmap>
#include <QPainter>


void ImageLabel::mousePressEvent(QMouseEvent *event)
{
      if (event->button() == Qt::LeftButton)
      {
           emit clicked();
      }
}


void SignInButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPixmap map(":/config/login_remove.png");
    resize(map.size());
    QPainter painter;
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(rect(), map);
}

VerificationCodeLabel::VerificationCodeLabel(QWidget *parent)
    : QLabel(parent),ifgenerate(true)
{
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    colorArray = QPointer<QColor>(new QColor[letter_number]);
    verificationCode = QPointer<QColor>(new QChar[letter_number]);
    noice_point_number = this->width();

    connect(this, SIGNAL(clicked()), this, SLOT(Repaint()));
}

VerificationCodeLabel::~VerificationCodeLabel()
{
    if (colorArray != 0)
    {
        delete []colorArray;
        colorArray = 0;
    }

    if (verificationCode != 0)
    {
        delete []verificationCode;
        verificationCode = 0;
    }
}

void VerificationCodeLabel::Repaint()
{
    ifgenerate = true;
    repaint();
}

void VerificationCodeLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}

void VerificationCodeLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    code.clear();
    QPainter painter(this);
    QPoint p;
    painter.fillRect(this->rect(), Qt::white);
    if (ifgenerate)
    {
        produceVerificationCode();
        produceRandomColor();
    }

    //绘制验证码
    for (int i = 0; i < letter_number; ++i)
    {
        p.setX(i * (this->width() / letter_number) + this->width()/8);
        p.setY(this->height() / 2);
        painter.setPen(colorArray[i]);
        painter.drawText(p, QString(verificationCode[i]));
        code += verificationCode[i];
    }

    //绘制噪点
    for (int j = 0; j < noice_point_number; ++j) //noice_point_number噪声点数
    {
        p.setX(qrand() % this->width());
        p.setY(qrand() % this->height());
        painter.setPen(colorArray[j % 4]);
        painter.drawPoint(p);
    }
    if (ifgenerate)
    {
        emit textchanged();
        ifgenerate = false;
    }
    return;
}

//这是一个用来生成验证码的函数
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

//产生随机的颜色
void VerificationCodeLabel::produceRandomColor() const
{
    for (int i = 0; i < letter_number; ++i)
        colorArray[i] = QColor(qrand() % 255, qrand() % 255, qrand() % 255);
    return;
}

//返回一个字符串（字母一律都按照大写返回）
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


