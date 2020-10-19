#ifndef AGREEMENTDIALOG_H
#define AGREEMENTDIALOG_H

#include <QDialog>
#include <QString>
#include <QFile>
namespace Ui {
class AgreementDialog;
}

class AgreementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AgreementDialog(QWidget *parent = 0);
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
