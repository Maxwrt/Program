#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QDialog>
#include <QString>
#include <QSqlDatabase>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
namespace Ui {
class ForgetPassword;
}

class ForgetPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgetPassword(const QString &username, QSqlDatabase& db, const QSize& size, QWidget *parent = 0);
    ~ForgetPassword();

private:
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event);
private:
    Ui::ForgetPassword *ui;
    QPixmap m_pixmap;
    QPoint m_lastPosition;
    bool m_moving;
};

#endif // FORGETPASSWORD_H
