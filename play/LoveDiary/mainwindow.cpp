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
#include <QSqlQuery>


MainWindow::MainWindow(const QVariantHash& logHash, QWidget *parent) :
    QMainWindow(parent),
    m_numDigits(99),
    m_UserHash(logHash),
    ui(new Ui::MainWindow)
{
    Init();
    InitSignalSlot();
    EditUser();
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
    m_db = Createdb(QStringLiteral("/config/LoveDiary.db"));
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
    connect(&m_timer, &QTimer::timeout, this, [=]() mutable -> void { ui->lcdNumber->display(CalculateDateTime(m_loveDateTime));});
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

void MainWindow::EditUser()
{
    m_LoginTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->labelTipInfo->setText(QString(u8"管理员:%1,您好！这是您第%2次使用系统").arg(m_UserHash.value("username").toString()).arg(m_UserHash.value("loginCount").toInt()+1));
    if(m_UserHash.value("isroot").toBool())
    {
        ui->btnEditUsers->show();
    }
    else
    {
        ui->btnEditUsers->hide();
    }
    //更新数据库中用户的登陆次数
    UpdateLoginCount();
}

void MainWindow::UpdateLoginCount()
{
    if(m_db.open())
    {
        QString update_sql="update users set loginCount='%1',latestlogintime='%2' where username='%3'";
        update_sql=update_sql.arg(m_UserHash.value("loginCount").toInt()+1).arg(m_LoginTime).arg(m_UserHash.value("username").toString());
        QSqlQuery query;
        query.prepare(update_sql);
        if(query.exec())
        {
            qDebug().noquote()<<u8"更新loginCount成功";
        }
        else
        {
            qDebug().noquote()<<u8"更新loginCount失败";
        }

        m_db.close();
    }
}
