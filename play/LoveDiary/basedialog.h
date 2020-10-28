#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QPixmap>

class BaseDialog : public QDialog
{
public:
    BaseDialog(QWidget *parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

protected:
    bool m_moving;
    QPoint m_lastPosition;
    QPixmap m_pixmap;
};

#endif // BASEDIALOG_H
