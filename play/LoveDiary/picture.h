#ifndef PICTURE_H
#define PICTURE_H
#include "basedialog.h"
#include <QDialog>
#include <QMouseEvent>
#include <QHash>
#include <QString>
#include <QKeyEvent>

namespace Ui {
class Picture;
}

class Picture : public BaseDialog
{
    Q_OBJECT

public:
    explicit Picture(const QSize& size, QWidget *parent = 0);
    ~Picture();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::Picture *ui;
    QHash<int, QString> m_imageHash;
};

#endif // PICTURE_H
