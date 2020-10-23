#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QVariantList>
#include <QIcon>
#include <QPaintEvent>
#include <QPixmap>
#include <QPoint>
#include <QSize>

namespace Ui {
class registDialog;
}

class registDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registDialog(QVariantHash& hash, QSqlDatabase &argdb, const QVariantList& arguserlist, const QSize& size, QWidget *parent = 0);
    ~registDialog();

private:
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event);

private:
    Ui::registDialog *ui;
    QPixmap m_pixmap;
    QPoint m_lastPosition;
    bool m_moving;
};

#endif // REGISTDIALOG_H
