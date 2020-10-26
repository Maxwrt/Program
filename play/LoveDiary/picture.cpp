#include "picture.h"
#include "ui_picture.h"
#include "common.h"
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QStringList>
#include <QTextStream>
Picture::Picture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Picture)
{
    ui->setupUi(this);
    m_imageHash = LoadImage(qApp->applicationDirPath() % QStringLiteral("/us"), QStringList()<<"*.jpg"<<"*.png");
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet(QString("QDialog{border-image:url(%1);}").arg(m_imageHash.value(0)));
    move((parent->width()- width())/2, (parent->height() - height())/2);
}

Picture::~Picture()
{
    delete ui;
}

void Picture::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        static int next = 1;
        if (next > m_imageHash.size())
        {
            next = 0;
        }
        //ÉèÖÃ±³¾°Í¼Æ¬
#if 1
        setStyleSheet(QString("QDialog{border-image:url(%1);}").arg(m_imageHash.value(next++)));
#else
        QPalette pal = palette();
        pal.setBrush(QPalette::Background, QBrush(QPixmap(m_imageHash.value(next++))));
        setPalette(pal);
#endif
    }
    else if (event->button() == Qt::RightButton)
    {
        close();
    }
}

void Picture::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
