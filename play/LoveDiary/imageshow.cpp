#include "imageshow.h"
#include "common.h"
#include <QObject>

ImageShow::ImageShow(QString filename)
{
    m_filename = filename;
    m_imgsrc = Q_NULLPTR;
    m_imgdst = Q_NULLPTR;
}

ImageShow::~ImageShow()
{
    if (m_imgsrc != Q_NULLPTR)
    {
        delete m_imgsrc;
    }
}

bool ImageShow::LoadImg(const QString &filename)
{
    if (!m_filename.isEmpty())
    {
        m_imgsrc = new QImage(m_filename);
    }
    else if (!filename.isEmpty())
    {
        m_imgsrc = new QImage(filename);
    }
    else
    {
        OUT << u8"没有加载到图片文件";
        return false;
    }
    return true;
}

//白色为255，黑色为0
QByteArray ImageShow::ReadGrayImage()
{
    if(m_imgdst->format() != QImage::Format_Grayscale8)
    {
        return QByteArray();
    }
    QByteArray Serial_buff;
    uchar * datap;
    for(int i=0;i<m_imgsrc->height();i++)
    {
        datap = m_imgsrc->scanLine(i);
        for(int j=0;j<m_imgsrc->width();j++)
        {
            OUT << datap[j] << " ";
        }
        OUT << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    }
    return Serial_buff;
}

QPixmap ImageShow::ToDifferStyle(QImage::Format type)
{
    if(m_imgdst != nullptr)
    {
        delete m_imgdst;
    }

    QString err = QString::null;
    if (type == QImage::Format_RGB16)
    {
        err = QStringLiteral("Format_RGB16");
    }
    else if (type == QImage::Format_Grayscale8)
    {
        err = QStringLiteral("Format_Grayscale8");
    }

    if(m_imgsrc != nullptr)
    {
        if (type == QImage::Format_RGB16)
        {
            m_imgdst = new QImage(m_imgsrc->convertToFormat(QImage::Format_RGB16));
        }
        else if (type == QImage::Format_Grayscale8)
        {
            m_imgdst = new QImage(m_imgsrc->convertToFormat(QImage::Format_Grayscale8));
        }
    }
    else
    {
        OUT << QObject::tr(u8"转换%1失败,请检查").arg(err);
        return QPixmap();
    }
    return QPixmap::fromImage(*m_imgdst);
}
