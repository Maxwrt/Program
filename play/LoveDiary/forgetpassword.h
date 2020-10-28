#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include "basedialog.h"
#include <QDialog>
#include <QString>
#include <QSqlDatabase>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
namespace Ui {
class ForgetPassword;
}

class ForgetPassword : public BaseDialog
{
    Q_OBJECT

public:
    explicit ForgetPassword(const QString &username, QSqlDatabase& db, const QSize& size, QWidget *parent = 0);
    ~ForgetPassword();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ForgetPassword *ui;
    QPoint m_lastPosition;
    bool m_moving;
};

#endif // FORGETPASSWORD_H
