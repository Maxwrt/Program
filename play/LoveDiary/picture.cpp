#include "picture.h"
#include "ui_picture.h"
#include "common.h"
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QStringList>
#include <QTextStream>
Picture::Picture(const QSize& size, QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::Picture)
{
    ui->setupUi(this);
    m_imageHash = LoadImage(qApp->applicationDirPath() % QStringLiteral("/us"), QStringList()<<"*.jpg"<<"*.png");
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet(QString("QDialog{border-image:url(%1);}").arg(m_imageHash.value(0)));
    move((size.width()- width())/2, (size.height() - height())/2);
}

Picture::~Picture()
{
    delete ui;
}

void Picture::keyPressEvent(QKeyEvent *event)
{
    static int next = 1;
    if(event->key() == Qt::Key_Right)
    {
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
    else if(event->key() == Qt::Key_Left)
    {
        if (next < 0)
        {
            next = m_imageHash.size();
        }
        setStyleSheet(QString("QDialog{border-image:url(%1);}").arg(m_imageHash.value(next--)));
    }
    else if(event->key() == Qt::Key_Escape)
    {
        close();
    }
}

void Picture::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}
