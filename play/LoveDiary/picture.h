#ifndef PICTURE_H
#define PICTURE_H

#include <QDialog>
#include <QMouseEvent>
#include <QHash>
#include <QString>

namespace Ui {
class Picture;
}

class Picture : public QDialog
{
    Q_OBJECT

public:
    explicit Picture(QWidget *parent = 0);
    ~Picture();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::Picture *ui;
    QHash<int, QString> m_imageHash;
};

#endif // PICTURE_H
