#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoguser.h"
#include "common.h"
#include "Sender.h"
#include "Receiver.h"
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
#include <QThread>
#include <QDesktopWidget>

MainWindow::MainWindow(QSqlDatabase& db, const QVariantHash& logHash, QWidget *parent) :
    QMainWindow(parent),
    m_numDigits(11),
    m_db(db),
    m_UserHash(logHash),
    m_picture(Q_NULLPTR),
    m_dlgUser(Q_NULLPTR),
    m_AgreementDialog(Q_NULLPTR),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitSignalSlot();
    Init();
    EditUser();
}

MainWindow::~MainWindow()
{
    if (m_timer.isActive())
    {
        m_timer.stop();
    }
    if (m_thread.isRunning())
    {
        m_thread.quit();
        m_thread.wait();
    }
    delete ui;
}


void MainWindow::Init()
{
    m_timer.setInterval(1000);
    setWindowIcon(QIcon(":/config/title.ico"));
    m_labelTipInfo = new QLabel(this);
    m_labelTipInfo->adjustSize();
    statusBar()->addWidget(m_labelTipInfo);
    m_loveDateTime = QDateTime(QDate(2020, 9, 4), QTime(21, 9, 9)),
    setWindowTitle(tr("Love Diary About SuSu & GuaGua"));
    ui->label_together->setText(QString(u8"%1 苏苏&瓜瓜在一起. 我们在一起:%2了") \
                                .arg(m_loveDateTime.toString(u8"yyyy年MM月dd日 hh点mm分ss秒"))
                                .arg(CalculateDateTime(m_loveDateTime)));
    ui->lcdNumber->setDigitCount(m_numDigits);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setFrameShape(QFrame::NoFrame);
    ui->lcdNumber->setFrameShadow(QFrame::Sunken);
    ui->lcdNumber->display(CalculateDateTime(m_loveDateTime, false));
    ui->lcdNumber->hide();
    ui->menu->addAction(ui->actionEdit);
    if (!m_timer.isActive())
    {
        m_timer.start();
    }
}


void MainWindow::InitSignalSlot()
{
    connect(&m_timer, &QTimer::timeout, this, [=]() mutable -> void
    {
#if 0
        ui->lcdNumber->display(CalculateDateTime(m_loveDateTime, false));
#endif
        ui->label_together->setText(QString(u8"%1 苏苏&瓜瓜在一起. 我们在一起:%2了") \
                                    .arg(m_loveDateTime.toString(u8"yyyy年MM月dd日 hh点mm分ss秒"))
                                    .arg(CalculateDateTime(m_loveDateTime)));
    });

    connect(ui->pushButton_agreement, &QPushButton::clicked, this, [&]
    {
        if (!m_AgreementDialog)
        {
            m_AgreementDialog = QPointer<AgreementDialog>(new AgreementDialog(size(), this));
        }
        m_AgreementDialog->setFocus();
        m_AgreementDialog->exec();
    });

    connect(ui->actionEdit, &QAction::triggered, this, [=]()
    {
        if (nullptr == m_dlgUser)
        {
            m_dlgUser = QPointer<DialogUser>(new DialogUser(m_db, this));
        }
        m_dlgUser->setFocus();
        m_dlgUser->exec();
    });

    m_picture = QPointer<Picture>(new Picture(size(), Q_NULLPTR));
    m_picture->moveToThread(&m_thread);
    connect(&m_thread, &QThread::finished, m_picture, &QObject::deleteLater, Qt::QueuedConnection);
    connect(ui->pushButton_us, &QPushButton::clicked, this, [=]()
    {
        m_thread.start();
        m_picture->move( (QApplication::desktop()->availableGeometry().size().width() - m_picture->width())/2,
                         (QApplication::desktop()->availableGeometry().size().height() - m_picture->height())/2);
        m_picture->setFocus();
        m_picture->exec();
    }
    );

    connect(ui->pushButton_chat, &QPushButton::clicked, this, [=]()
    {
        static QPointer<Sender> sender = 0;
        if (sender == 0)
        {
            sender = QPointer<Sender>(new Sender());
        }
        sender->exec();

        static QPointer<Receiver> receiver = 0;
        if (receiver == 0)
        {
            receiver = QPointer<Receiver>(new Receiver());
        }
        receiver->exec();
    });
}

void MainWindow::Show()
{
    show();
}

void MainWindow::EditUser()
{
    m_LoginTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    m_labelTipInfo->setText(QString(u8"管理员:%1,您好！这是您第%2次使用系统").arg(m_UserHash.value("username").toString()).arg(m_UserHash.value("loginCount").toInt()+1));
    if(!m_UserHash.value("isroot").toBool())
    {
        ui->actionEdit->setEnabled(false);
    }
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
            OUT << u8"更新loginCount成功";
        }
        else
        {
            OUT << u8"更新loginCount失败";
        }
        m_db.close();
    }
}
