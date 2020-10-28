#include "forgetpassword.h"
#include "ui_forgetpassword.h"
#include "common.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QPainter>
ForgetPassword::ForgetPassword(const QString &username, QSqlDatabase& db, const QSize& size,QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::ForgetPassword)
{
    ui->setupUi(this);
    ui->lineEdit->setText(username);
    move((size.width() - width())/2, (size.height()-height())/2);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    m_pixmap = QPixmap(":/config/forgetPassword.png");
    connect(ui->pushButton, &QPushButton::clicked, this, [&]()->void
    {
        QString userpassword(ui->lineEdit_2->text());
        QString userpasswordok(ui->lineEdit_3->text());
        if(userpassword.isEmpty() || userpasswordok.isEmpty())
        {
            QMessageBox::information(this, u8"提示信息", u8"密码、确认密码不能为空", u8"确定");
            return;
        }

        if (userpassword.indexOf(QRegExp("^[A-Z][a-zA-Z0-9]{5,17}")))
        {
            QMessageBox::information(this, u8"提示信息", u8"密码长度不小6且以大写字母开头必须包含小写字母和数字", u8"确定");
            return;
        }

        if (qstrcmp(userpassword.toStdString().c_str(), userpasswordok.toStdString().c_str()) != 0)
        {
            QMessageBox::information(this, u8"提示信息", u8"两次输入密码不一致", u8"确定");
            return;
        }

        if (qstrcmp(username.toStdString().c_str(), userpassword.toStdString().c_str()) == 0)
        {
            QMessageBox::information(this, u8"提示信息", u8"用户名和密码不能相同", u8"确定");
            return;
        }
        if (db.open())
        {
            QString update_sql = QString("update users set password='%1' where username='%2';").arg(userpassword).arg(username);
            QSqlQuery qsql;
            qsql.prepare(update_sql);
            if(!qsql.exec(update_sql))
            {
               OUT << qsql.lastError();
            }
            else
            {
               QMessageBox::information(this, u8"提示信息", u8"重置成功", u8"确定");
            }
               db.close();
         }
         else
         {
            OUT << u8"打开数据库失败";
         }
         });

    connect(ui->pushButton_2, &QPushButton::clicked, this, [&]()->void
    {
         if (db.open())
         {
             QString select_sql = QString("select password from users where username='%1'").arg(username);
             QSqlQuery qsql;
             qsql.prepare(select_sql);
             if(!qsql.exec(select_sql))
             {
                 OUT << qsql.lastError();
                 return;
             }
             else
             {
                 if (qsql.first())
                 {
                    QString password = qsql.value(0).toString();
                    if (!password.isEmpty())
                    {
                        ui->lineEdit_4->setText(password);
                    }
                 }
             }
             db.close();
         }
         else
         {
             OUT << u8"打开数据库失败";
         }
             return;
      });

    connect(ui->pushButton_3, &QPushButton::clicked, this, [=]
    {
        close();
    });
}

ForgetPassword::~ForgetPassword()
{
    delete ui;
}

void ForgetPassword::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    resize(m_pixmap.size());
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(rect(), m_pixmap);
}

