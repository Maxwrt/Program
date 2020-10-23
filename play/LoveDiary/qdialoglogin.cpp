#include "qdialoglogin.h"
#include "ui_qdialoglogin.h"
#include "common.h"
#include "verificationcodelabel.h"
#include "registdialog.h"
#include <QSettings>
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QFileInfoList>
#include <QBitmap>

QDialogLogin::QDialogLogin(const QSize& argsize,QWidget *parent) :
    QDialog(parent),
    m_trynum(0),
    m_imageindex(0),
    ui(new Ui::QDialogLogin)
{
    ui->setupUi(this);
    move((argsize.width()- width())/2, (argsize.height() - height())/2);
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    m_user = QString::null;
    m_password = QString::null;
    initDialog();
    opendb();
    selectdb();
    connect(ui->labelVerificationCode, &VerificationCodeLabel::textchanged, this, [=]()
    {
        m_verification = ui->labelVerificationCode->Text();
    });

//    connect(ui->labelPicture, &ImageLabel::clicked, this, [=]()
//    {
//        QPixmap picture;
//        setPicture(&picture);
//    });
    connect(ui->pushButtonOk, &QPushButton::clicked, this, [&]() mutable -> void
    {
        QString user = ui->lineEditUser->text();
        QString password = ui->lineEditPassword->text();
        //QString encryptPassword=encryptPasswd(password);
        QString verification = ui->lineEditVerification->text();
        if(!user.isEmpty())
        {
            if (password.isEmpty())
            {
                QMessageBox::information(this, tr("Info"), u8"密码不能为空", u8"确定");
                return;
            }

            if (verification.isEmpty())
            {
                QMessageBox::information(this, tr("Info"), u8"请输入验证码", u8"确定");
                return;
            }
            else
            {
                if (qstrcmp(verification.toStdString().c_str(), m_verification.toStdString().c_str()) != 0)
                {
                    QMessageBox::information(this, tr("Info"), u8"输入的验证码不正确", u8"确定");
                    return ;
                }
            }
            //和数据库中的用户名和密码进行比较
            if(m_hashlist.count()>0)
            {
                for(int i=0; i<m_hashlist.count(); i++)
                {
                    QVariantHash hash = m_hashlist.at(i).toHash();
                    if(hash.value("username") == user)
                    {
                        if(hash.value("password") == password)
                        {
                            m_user=user;
                            m_loginUserHash=m_hashlist.at(i).toHash();
                            accept();
                            qDebug() << tr("Login Sys");
                        }
                        else
                        {
                            m_trynum++;
                            if(m_trynum>3)
                            {
                                QMessageBox::critical(this, tr("Error Tip"), tr("Input error number greater than 3,sys close"), u8"确定");
                                close();
                                return;
                            }
                            else
                            {
                                QMessageBox::information(this, tr("Info"), tr("the username or password error, please check"));
                                ui->lineEditPassword->clear();
                                return;
                            }
                        }
                    }
                }
            }
            if((m_hashlist.count()<1) || m_user.isEmpty())
            {
                QMessageBox::information(this, tr("Info"), tr(u8"user %1 not exists，please register firstly").arg(user), u8"确定");
                return;
            }
        }
        else
        {
            QMessageBox::information(this, tr("Info"), tr("please input username"));
        }
    }
    );

    connect(ui->pushButtonRegister, &QPushButton::clicked, this, [=]
    {
        QVariantHash hash;
        registDialog *ptRegister = new registDialog(hash, m_db, m_hashlist, argsize, this);
        if (ptRegister->exec() == QDialog::Accepted)
        {
            m_hashlist << hash;
        }
    });

    connect(ui->pushButtonCancel, &QPushButton::clicked, this, [=]{close();});
    connect(ui->pushButtonForgetPassword, &QPushButton::clicked, this, [=]{});
#if 0
    readsettings();
#endif
}

void QDialogLogin::setPicture(QPixmap *pixmap)
{
    Q_UNUSED(pixmap);
//    pixmap->load(m_imageHash.value(m_keys.at(generateDifferentIndex())));
//    pixmap->scaled(ui->labelPicture->size(), Qt::KeepAspectRatio);
//    ui->labelPicture->setPixmap(*pixmap);
}

int  QDialogLogin::generateDifferentIndex()
{
    int oldvalue = m_imageindex;
    while (true)
    {
        m_imageindex = qrand() % m_keys.size();
        if (oldvalue != m_imageindex)
        {
            return m_imageindex;
        }
    }
    return 0;
}

QDialogLogin::~QDialogLogin()
{
    m_db.close();
    OUT << "~QDialogLogin";
    delete ui;
}

void QDialogLogin::selectdb()
{
    if(m_db.isOpen() || m_db.open())
    {
        QString select_sql("select * from users");
        QSqlQuery qsql;
        qsql.prepare(select_sql);
        if(qsql.exec())
        {
            while(qsql.next())
            {
                QVariantHash hash;
                hash.insert("username", qsql.value(0).toString());
                hash.insert("password", qsql.value(1).toString());
                hash.insert("isroot", qsql.value(2).toBool());
                hash.insert("datestring", qsql.value(3).toString());
                hash.insert("sex", qsql.value(4).toString());
                hash.insert("loginCount", qsql.value(5).toInt());
                hash.insert("latestlogintime",qsql.value(6).toString());
                m_hashlist<<hash;
            }
        }
    }
    else
    {
        OUT << u8"打开users.db失败";
    }
}

void QDialogLogin::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_lastPosition = event->globalPos()-pos();
    }
    QDialog::mousePressEvent(event);
}

void QDialogLogin::mouseMoveEvent(QMouseEvent *event)
{
    if(m_moving && (event->buttons() == Qt::LeftButton) && ((event->globalPos() - m_lastPosition).manhattanLength() > QApplication::startDragDistance()))
    {
        move(event->globalPos()-m_lastPosition);
        m_lastPosition = event->globalPos()-pos();
    }
    QDialog::mouseMoveEvent(event);
}

void QDialogLogin::mouseReleaseEvent(QMouseEvent* event)
{
    m_moving=false;
    QDialog::mouseReleaseEvent(event);
}

void QDialogLogin::loadImages(const QString& dirpath)
{
    if (dirpath.isEmpty())
    {
        OUT << u8"图片路径为空";
        return;
    }

    QDir dir(dirpath);
    for (auto item: dir.entryInfoList(QStringList("*.jpg"), QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
    {
        if (item.isDir())
        {
            loadImages(item.absoluteFilePath());
        }
        if (item.isFile())
        {
            m_imageHash.insert(item.baseName(), item.filePath());
            m_keys << item.baseName();
        }
    }
    if (m_keys.size() > 0)
    {
        m_imageindex = qrand() % m_keys.size();
    }
}

void QDialogLogin::readsettings()
{
    QString organization = "WRT-Qt";
    QString application = "LoveDiary";
    QSettings settings(organization, application);
    m_user=settings.value("User", "wrt").toString();
    QString encryptPassword=encryptPasswd("Sn_11210318");
    m_password=settings.value("Password", encryptPassword).toString();
    m_autoWriteUser=settings.value("flag", false).toBool();
    if(m_autoWriteUser)
        ui->lineEditUser->setText(m_user);
}

void QDialogLogin::writesettings()
{
    QString organization="WRT-Qt";
    QString application="LoveDiary";
    QSettings settings(organization, application);
    settings.setValue("User", m_user);
    settings.setValue("Password", encryptPasswd("Sn_11210318"));
//    settings.setValue("flag", ui->checkBox->isChecked());
}
#include <QPainter>
void QDialogLogin::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    resize(m_pixmap.size());
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(rect(), m_pixmap);
}

void QDialogLogin::initDialog()
{
    m_db = Createdb("/config/LoveDiary.db");
    loadImages(":/config/");
    setWindowIcon(QIcon(m_imageHash.value(m_keys.at(generateDifferentIndex()))));
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    //给用户名和密码编辑框安装事件过滤器
    ui->lineEditUser->installEventFilter(this);
    ui->lineEditPassword->installEventFilter(this);
    ui->labelVerificationCode->installEventFilter(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    m_pixmap = QPixmap(":/config/heart_remove.png");
}

int QDialogLogin::ShowLogin()
{
    return exec();
}

void QDialogLogin::opendb()
{
    if(m_db.isOpen() || m_db.open())
    {
        QString sql = QStringLiteral("create table if not exists users(username varchar(11) not null primary key, \
                                     password varchar(11) not null, isroot boolean, datestring varchar(20), sex varchar(5), loginCount int, latestlogintime varchar(20))");

                QSqlQuery qsql;
        qsql.prepare(sql);
        if(!qsql.exec(sql))
        {
            OUT << qsql.lastError();
        }
        else
        {
            OUT << u8"创建user表成功";
        }
    }
    else
    {
        OUT << u8"打开user.db数据库失败***" << m_db.lastError();
    }
}

QString QDialogLogin::encryptPasswd(const QString &password)
{
    QByteArray byteArray;
    byteArray.append(password);
    QByteArray hashByteArray = QCryptographicHash::hash(byteArray, QCryptographicHash::Md5);
    QString md5=hashByteArray.toHex();
    return md5;
}

bool QDialogLogin::eventFilter(QObject *watched, QEvent *event)
{
    if (qobject_cast<QLineEdit*>(watched) == ui->lineEditUser || watched == ui->lineEditPassword)
    {
        QPalette p = QPalette();
        if (event->type() == QEvent::FocusIn)
        {
            p.setColor(QPalette::Base, Qt::magenta);
            if (watched == ui->lineEditUser )
                ui->lineEditUser->setPalette(p);
            else if (watched == ui->lineEditPassword )
                ui->lineEditPassword->setPalette(p);
        }
        else if (event->type() == QEvent::FocusOut)
        {
            p.setColor(QPalette::Base, Qt::white);
            if (watched == ui->lineEditUser )
                ui->lineEditUser->setPalette(p);
            else if (watched == ui->lineEditPassword )
                ui->lineEditPassword->setPalette(p);
        }
    }
    else if (qobject_cast<QLabel*>(watched) == ui->labelVerificationCode && event->type() == QEvent::MouseButtonDblClick)
    {

    }
    return QWidget::eventFilter(watched, event);
}
