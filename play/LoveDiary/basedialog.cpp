#include "basedialog.h"
#include <QApplication>
#include <QPainter>

BaseDialog::BaseDialog(QWidget *parent):
    QDialog(parent)
{

}

void BaseDialog::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_lastPosition = event->globalPos()-pos();
    }
    QDialog::mousePressEvent(event);
}

void BaseDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(m_moving && (event->buttons() == Qt::LeftButton) && ((event->globalPos() - m_lastPosition).manhattanLength() > QApplication::startDragDistance()))
    {
        move(event->globalPos()-m_lastPosition);
        m_lastPosition = event->globalPos()-pos();
    }
    QDialog::mouseMoveEvent(event);
}

void BaseDialog::mouseReleaseEvent(QMouseEvent* event)
{
    m_moving=false;
    QDialog::mouseReleaseEvent(event);
}
