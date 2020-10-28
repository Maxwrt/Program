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
    void Show();

private:
    void Init();

private:
    Ui::AgreementDialog *ui;
    QString m_filestr;
    QFile m_file;
};

#endif // AGREEMENTDIALOG_H
