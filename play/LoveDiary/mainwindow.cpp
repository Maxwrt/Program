#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoguser.h"
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
#include <QIcon>

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
    setWindowIcon(QIcon(":/config/love.jpg"));
    m_labelTipInfo = new QLabel(this);
    m_labelTipInfo->adjustSize();
    statusBar()->addWidget(m_labelTipInfo);
    m_db = Createdb(QStringLiteral("/config/LoveDiary.db"));
    m_loveDateTime = QDateTime(QDate(2020, 9, 4), QTime(21, 9, 9)),
    setWindowTitle(tr("Love Diary About SuSu & GuaGua"));
    ui->label_together->setText(tr("%1 SuSu & GuaGua were together. We have been together:") \
                                .arg(m_loveDateTime.toString(u8"yyyy��MM��dd�� hh��mm��ss��")));
    ui->lcdNumber->setDigitCount(m_numDigits);
    m_timer.setInterval(1000);
    m_AgreementDialog = nullptr;
    ui->menu->addAction(ui->actionEdit);
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

    connect(ui->actionEdit,&QAction::triggered, this, [=]()
    {
        DialogUser dlgUser(this);
        dlgUser.exec();
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
    m_labelTipInfo->setText(QString(u8"����Ա:%1,���ã���������%2��ʹ��ϵͳ").arg(m_UserHash.value("username").toString()).arg(m_UserHash.value("loginCount").toInt()+1));
    if(!m_UserHash.value("isroot").toBool())
    {
        ui->actionEdit->setEnabled(false);
    }

    //�������ݿ����û��ĵ�½����
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
            qDebug().noquote()<<u8"����loginCount�ɹ�";
        }
        else
        {
            qDebug().noquote()<<u8"����loginCountʧ��";
        }

        m_db.close();
    }
}
