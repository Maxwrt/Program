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
    : QLabel(parent),m_ifgenerate(true)
{
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    m_colorArray = new QColor[m_letter_number];
    m_verificationCode = new QChar[m_letter_number];
    m_noice_point_number = this->width();

    connect(this, SIGNAL(clicked()), this, SLOT(Repaint()));
}

VerificationCodeLabel::~VerificationCodeLabel()
{
    if (m_colorArray != 0)
    {
        delete []m_colorArray;
        m_colorArray = 0;
    }

    if (m_verificationCode != 0)
    {
        delete []m_verificationCode;
        m_verificationCode = 0;
    }
}

void VerificationCodeLabel::Repaint()
{
    m_ifgenerate = true;
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
    m_code.clear();
    QPainter painter(this);
    QPoint p;
    painter.fillRect(this->rect(), Qt::lightGray);
    if (m_ifgenerate)
    {
        produceVerificationCode();
        produceRandomColor();
    }

    //绘制验证码
    for (int i = 0; i < m_letter_number; ++i)
    {
        p.setX(i * (this->width() / m_letter_number) + this->width()/8);
        p.setY(this->height() / 2);
        painter.setPen(m_colorArray[i]);
        painter.drawText(p, QString(m_verificationCode[i]));
        m_code += m_verificationCode[i];
    }

    //绘制噪点
#if 0
    for (int j = 0; j < m_noice_point_number; ++j) //m_noice_point_number噪声点数
    {
        p.setX(qrand() % this->width());
        p.setY(qrand() % this->height());
        painter.setPen(m_colorArray[j % 4]);
        painter.drawPoint(p);
    }
#endif
    if (m_ifgenerate)
    {
        emit textchanged();
        m_ifgenerate = false;
    }
    return;
}

//这是一个用来生成验证码的函数
void VerificationCodeLabel::produceVerificationCode() const
{
    for (int i = 0; i < m_letter_number; ++i)
        m_verificationCode[i] = produceRandomLetter();
    return;
}

QChar VerificationCodeLabel::produceRandomLetter() const
{
    QChar c;
    int flag = qrand() % m_letter_number;
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
    for (int i = 0; i < m_letter_number; ++i)
        m_colorArray[i] = QColor(qrand() % 255, qrand() % 255, qrand() % 255);
    return;
}

//返回一个字符串（字母一律都按照大写返回）
QString VerificationCodeLabel::getVerificationCode() const
{
    QString s;
    QChar cTemp;
    for (int i = 0; i < m_letter_number; ++i)
    {
        cTemp = m_verificationCode[i];
        s += cTemp>97 ? cTemp.toUpper() : cTemp;
    }
    return s;
}


