#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H
#include "basedialog.h"
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

class registDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit registDialog(QVariantHash& hash, QSqlDatabase &argdb, const QVariantList& arguserlist, const QSize& size, QWidget *parent = 0);
    ~registDialog();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::registDialog *ui;
};

#endif // REGISTDIALOG_H
