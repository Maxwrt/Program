/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef AGREEMENTDIALOG_H
#define AGREEMENTDIALOG_H

#include "basedialog.h"
#include <QDialog>
#include <QString>
#include <QFile>
#include <QSize>
namespace Ui {
class AgreementDialog;
}

class AgreementDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit AgreementDialog(const QSize& argsize, QWidget *parent = 0);
    ~AgreementDialog();

private:
    void Init();

private:
    Ui::AgreementDialog *ui;
    QString m_filestr;
    QFile m_file;
};

#endif // AGREEMENTDIALOG_H
