#include "agreementdialog.h"
#include "ui_agreementdialog.h"
#include "common.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QIODevice>

AgreementDialog::AgreementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgreementDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Love Protocal"));
    Init();
}

AgreementDialog::~AgreementDialog()
{
    delete ui;
}

void AgreementDialog::Show()
{
    exec();
}

void AgreementDialog::Init()
{
    m_filestr = QStringLiteral(":/config/loveAgreement.txt");
    if (!QFile::exists(m_filestr))
    {
        OUT << tr(u8"资源文件%1不存在，请检查").arg(QFileInfo(m_filestr).absoluteFilePath());
    }
    m_file.setFileName(m_filestr);

    if (m_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream read(&m_file);
        ui->textEdit->setText(read.readAll());
        m_file.close();
    }
    else
    {
        OUT << tr(u8"打开文件%1失败").arg(m_filestr);
    }

    connect(ui->pushButton, &QPushButton::clicked, this, [=]
    {
        if (m_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            QString content = ui->textEdit->toPlainText();
            QTextStream write(&m_file);
            write << content;
            m_file.close();
        }
        close();
    }
    );
}

