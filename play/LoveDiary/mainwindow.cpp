#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QStringList>
#include <QString>
#include <QWidget>
#include <QFont>


MainWindow::MainWindow(const QVariantHash& logHash, QWidget *parent) :
    QMainWindow(parent),
    m_numDigits(99),
    m_loginUserHash(logHash),
    ui(new Ui::MainWindow)
{
    Init();
    InitSignalSlot();
}

MainWindow::~MainWindow()
{
    if (m_timer.isActive())
    {
        m_timer.stop();
    }
    delete ui;
}


void MainWindow::Init()
{
    ui->setupUi(this);

    m_loveDateTime = QDateTime(QDate(2020, 9, 4), QTime(21, 9, 9)),
    setWindowTitle(tr("Love Diary About SuSu & GuaGua"));
    ui->label_together->setText(tr("%1 SuSu & GuaGua were together. We have been together:") \
                                .arg(m_loveDateTime.toString(u8"yyyy年MM月dd日 hh点mm分ss秒")));
    ui->lcdNumber->setDigitCount(m_numDigits);
    m_timer.setInterval(1000);
    m_AgreementDialog = nullptr;
}

void MainWindow::InitSignalSlot()
{
    connect(&m_timer, &QTimer::timeout, this, [&]() mutable -> void { ui->lcdNumber->display(CalculateDateTime(m_loveDateTime));});
    connect(ui->pushButton_agreement, &QPushButton::clicked, this, [&]
    {
        if (!m_AgreementDialog)
        {
            m_AgreementDialog = new AgreementDialog(this);
        }
        m_AgreementDialog->Show();
    });
}

void MainWindow::Show()
{
    if (!m_timer.isActive())
    {
        m_timer.start();
    }
    show();
}
