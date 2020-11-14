#ifndef IMAGESHOW_H
#define IMAGESHOW_H

#include <QImage>
#include <QPixmap>
#include <QByteArray>
#include <QPointer>
class ImageShow
{
public:
    ImageShow(QString filename = QString());
    ~ImageShow();
    bool LoadImg(const QString &filename = QString());
    QPixmap ToDifferStyle(QImage::Format type);
    QByteArray ReadGrayImage();


private:
    QPointer<QImage> m_imgsrc;
    QPointer<QImage> m_imgdst;
    QString m_filename;
};

#endif // IMAGESHOW_H
