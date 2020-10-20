#include "qdialoglogin.h"
#include "ui_qdialoglogin.h"
#include "common.h"
#include <QSettings>
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

QDialogLogin::QDialogLogin(QWidget *parent) :
    QDialog(parent),
    m_trynum(0),
    ui(new Ui::QDialogLogin)
{
    ui->setupUi(this);
    m_user = QString::null;
    m_password = QString::null;
    initDialog();

    connect(ui->pushButtonOk, &QPushButton::clicked, this, [&]() mutable -> void
    {
        QString user=ui->lineEditUser->text();
        QString password=ui->lineEditPassword->text();
        //QString encryptPassword=encryptPasswd(password);
        if(!user.isEmpty())
        {
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
                                QMessageBox::critical(this, tr("Error Tip"), tr("Input error number greater than 3,sys close"), tr(u8"OK"));
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
                QMessageBox::information(this, u8"Info", tr(u8"user %1 not exists，please register firstly").arg(user), u8"OK");
                return;
            }
        }
        else
        {
            QMessageBox::information(this, tr("Info"), tr("please input username"));
        }
    }
    );

    connect(ui->pushButtonRegister, &QPushButton::clicked, this, [&]() mutable -> void
    {
        QString username = ui->lineEditUser->text();
        QString userpassword = ui->lineEditPassword->text();
        if(username.isEmpty() || userpassword.isEmpty())
        {
            QMessageBox::information(this, u8"Info", u8"username or password is empty, please check", u8"OK");
            return;
        }
        bool isroot = ui->checkBox->isChecked();
        bool isboy = ui->radioButton->isChecked();

        if(m_db.isOpen() || m_db.open())
        {
            QSqlQuery qsql;

            if(m_hashlist.count()>0)
            {
                for(int i=0; i < m_hashlist.size(); i++)
                {
                    QVariantHash hash=m_hashlist.at(i).toHash();
                    if(hash.value("username").toString() == username)
                    {
                        QMessageBox::information(this, u8"Info", tr(u8"user %1 existed").arg(username), u8"OK");
                        return;
                    }
                }
            }
            QString sex = QString::null;
            if(isboy)
            {
                sex = tr("MAN");
            }
            else
            {
                sex = tr("WOMAN");
            }
            QDateTime dateTime=QDateTime::currentDateTime();
            QString insert_sql = QStringLiteral("insert into users(username, password, isroot, datestring, sex, loginCount) values('%1', '%2', '%3', '%4', '%5', '%6')");
            insert_sql=insert_sql.arg(username).arg(userpassword).arg(isroot).arg(dateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(sex).arg(0);

            qsql.prepare(insert_sql);
            if(!qsql.exec(insert_sql))
            {
                OUT << qsql.lastError();
            }
            else
            {
                OUT << u8"注册成功";

                QVariantHash hash;
                hash.insert("username", username);
                hash.insert("password", userpassword);
                hash.insert("isroot", isroot);
                hash.insert("datestring", dateTime.toString());
                hash.insert("sex", tr("MAN"));
                hash.insert("loginCount", QString("0").toInt());
                m_hashlist << hash;

                ui->pushButtonRegister->setText(u8"register success");
                ui->pushButtonRegister->setStyleSheet("QPushButton{color:red;}");
                Sleep(2000);
                ui->pushButtonRegister->setText(u8"register");
                ui->pushButtonRegister->setStyleSheet("QPushButton{color:black;}");
                ui->lineEditUser->clear();
                ui->lineEditPassword->clear();
            }
        }
        else
        {
            OUT << u8"打开user.db数据库失败***" << m_db.lastError();
        }
    }
    );

    connect(ui->pushButtonCancel, &QPushButton::clicked, this, [=]{close();});
#if 0
    readsettings();
#endif
    opendb();
    selectdb();
}

QDialogLogin::~QDialogLogin()
{
    m_db.close();
    qDebug() << QStringLiteral("~QDialogLogin");
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
        m_moving=true;
        m_lastPosition=event->globalPos()-pos();
    }
    QDialog::mousePressEvent(event);
}

void QDialogLogin::mouseMoveEvent(QMouseEvent *event)
{
    if(m_moving && (event->buttons() == Qt::LeftButton) && ((event->globalPos() - m_lastPosition).manhattanLength() > QApplication::startDragDistance()))
    {
        move(event->globalPos()-m_lastPosition);
        m_lastPosition=event->globalPos()-pos();
    }
    QDialog::mouseMoveEvent(event);
}

void QDialogLogin::mouseReleaseEvent(QMouseEvent* event)
{
    m_moving=false;
    QDialog::mouseReleaseEvent(event);
}

void QDialogLogin::readsettings()
{
    QString organization = "WRT-Qt";
    QString application = "LoveDiary";
    QSettings settings(organization, application);
    m_user=settings.value("User", "wrt").toString();
    QString encryptPassword=encryptPasswd("Sn_11210318");
    m_password=settings.value("Password", encryptPassword).toString();
    autoWriteUser=settings.value("flag", false).toBool();
    if(autoWriteUser)
        ui->lineEditUser->setText(m_user);
}

void QDialogLogin::writesettings()
{
    QString organization="WRT-Qt";
    QString application="LoveDiary";
    QSettings settings(organization, application);
    settings.setValue("User", m_user);
    settings.setValue("Password", encryptPasswd("Sn_11210318"));
    settings.setValue("flag", ui->checkBox->isChecked());
}

void QDialogLogin::initDialog()
{
    ui->labelPicture->setText("");
    ui->labelUser->setText(tr("username:"));
    ui->labelPassword->setText(tr("password:"));
    ui->labelVerification->setText(u8"验证码");
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    //给用户名和密码编辑框安装事件过滤器
    ui->lineEditUser->installEventFilter(this);
    ui->lineEditPassword->installEventFilter(this);

    ui->pushButtonOk->setText(tr("OK"));
    ui->pushButtonCancel->setText(u8"关闭");
    ui->pushButtonRegister->setText(tr("register"));
    QPixmap pixmap;
    pixmap.load(":/config/login.jpg");
    ui->labelPicture->setPixmap(pixmap);
#if 0
    setWindowFlags(Qt::FramelessWindowHint);
#endif
    setWindowFlags(Qt::CustomizeWindowHint);
    QIcon icon(":/config/title.png");
    setWindowIcon(icon);
    m_db = Createdb(QStringLiteral("/config/LoveDiary.db"));
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
    if (watched == ui->lineEditUser || watched == ui->lineEditPassword)
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
    return QWidget::eventFilter(watched, event);
}
