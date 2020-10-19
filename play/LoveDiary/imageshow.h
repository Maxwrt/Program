#ifndef IMAGESHOW_H
#define IMAGESHOW_H

#include <QImage>
#include <QPixmap>
#include <QByteArray>
class ImageShow
{
public:
    ImageShow(QString filename = QString());
    ~ImageShow();
    bool LoadImg(const QString &filename = QString());
    QPixmap ToDifferStyle(QImage::Format type);
    QByteArray ReadGrayImage();


private:
    QImage *m_imgsrc;
    QImage *m_imgdst;
    QString m_filename;
};

#endif // IMAGESHOW_H
