#include "registdialog.h"
#include "ui_registdialog.h"
#include "common.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPainter>
#include <QTextStream>
#include <QBitmap>

registDialog::registDialog(QVariantHash& hash, QSqlDatabase &argdb, const QVariantList& arguserlist, const QSize& size, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registDialog)
{
    ui->setupUi(this);
    move((size.width() - width())/4, (size.height()-height())/4);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    m_pixmap = QPixmap(":/config/heart_remove_7.png");
    connect(ui->pushButtonOk, &QPushButton::clicked, this, [&]() mutable -> void
    {
        QString username(ui->lineEditUser->text());
        QString userpassword(ui->lineEditPassword->text());
        QString userpasswordok(ui->lineEditOkPassword->text());
        if(username.isEmpty() || userpassword.isEmpty() || userpasswordok.isEmpty())
        {
            QMessageBox::information(this, tr("Info"), u8"�û��������롢ȷ�����벻��Ϊ��", u8"ȷ��");
            return;
        }

        if (qstrcmp(userpassword.toStdString().c_str(), userpasswordok.toStdString().c_str()) != 0)
        {
            QMessageBox::information(this, u8"��ʾ��Ϣ", u8"�����������벻һ��", u8"ȷ��");
            return;
        }

        bool isroot = ui->checkBox->isChecked();
        bool isboy  = ui->radioButton->isChecked();
        if (argdb.isValid())
        {
            if(argdb.isOpen() || argdb.open())
            {
                QSqlQuery qsql;
                if(arguserlist.count()>0)
                {
                    for(int i=0; i < arguserlist.size(); i++)
                    {
                        QVariantHash hash = arguserlist.at(i).toHash();
                        if(hash.value("username").toString() == username)
                        {
                            QMessageBox::information(this, u8"��ʾ��Ϣ", QString(u8"�û�%1�Ѵ���").arg(username), u8"ȷ��");
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
                QDateTime dateTime = QDateTime::currentDateTime();
                QString insert_sql("insert into users(username, password, isroot, datestring, sex, loginCount) values('%1', '%2', '%3', '%4', '%5', '%6')");
                insert_sql = insert_sql.arg(username).arg(userpassword).arg(isroot).arg(dateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(sex).arg(0);

                qsql.prepare(insert_sql);
                if(!qsql.exec(insert_sql))
                {
                    OUT << qsql.lastError();
                }
                else
                {
                    QMessageBox::information(this, u8"��ʾ��Ϣ", u8"ע��ɹ�", u8"ȷ��");
                    OUT << u8"ע��ɹ�";
                    hash.insert("username", username);
                    hash.insert("password", userpassword);
                    hash.insert("isroot", isroot);
                    hash.insert("datestring", dateTime.toString());
                    hash.insert("sex", tr("MAN"));
                    hash.insert("loginCount", QString("0").toInt());
                    ui->lineEditUser->clear();
                    ui->lineEditPassword->clear();
                    ui->lineEditOkPassword->clear();
                }
                argdb.close();
                accept();
            }
            else
            {
                OUT << u8"��user.db���ݿ�ʧ��***" << argdb.lastError();
            }
        }
    }
    );
}

registDialog::~registDialog()
{
    delete ui;
}

void registDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    resize(m_pixmap.size());
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(rect(), m_pixmap);
}

void registDialog::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_lastPosition = event->globalPos()-pos();
    }
    QDialog::mousePressEvent(event);
}

void registDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(m_moving && (event->buttons() == Qt::LeftButton) && ((event->globalPos() - m_lastPosition).manhattanLength() > QApplication::startDragDistance()))
    {
        move(event->globalPos()-m_lastPosition);
        m_lastPosition = event->globalPos()-pos();
    }
    QDialog::mouseMoveEvent(event);
}

void registDialog::mouseReleaseEvent(QMouseEvent* event)
{
    m_moving=false;
    QDialog::mouseReleaseEvent(event);
}
