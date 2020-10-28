#ifndef QDIALOGLOGIN_H
#define QDIALOGLOGIN_H

#include "basedialog.h"
#include <QDialog>
#include <QMouseEvent>
#include <QVariantList>
#include <QVariantHash>
#include <QSqlDatabase>
#include <QObject>
#include <QEvent>
#include <QHash>
#include <QPaintEvent>
#include <QPixmap>
#include <QSize>

namespace Ui {
class QDialogLogin;
}

class QDialogLogin : public BaseDialog
{
    Q_OBJECT

public:
    explicit QDialogLogin(const QSize& argsize, QWidget *parent = 0);
    ~QDialogLogin();
    int ShowLogin();
    QVariantHash GetUserHash() {return m_loginUserHash;}
    QSqlDatabase GetDB() {return m_db;}


protected :
    void readsettings();
    void writesettings();
    void initDialog();
    virtual bool eventFilter(QObject *watched, QEvent *event);
    QString encryptPasswd(const QString& password);
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void loginSystem();

private:
    void opendb();
    void selectdb();
    void loadImages(const QString& dirpath);
    void setPicture(QPixmap *pixmap);
    int  generateDifferentIndex();
    bool isUser(const QString &username);

private:
    Ui::QDialogLogin *ui;

    int m_imageindex;
    int m_trynum;
    bool m_autoWriteUser;
    QVariantList m_hashlist;
    QString m_user;
    QString m_password;
    QString m_verification;
    QHash<QString, QString> m_imageHash;
    QStringList m_keys;
    QSqlDatabase  m_db;
    QVariantHash m_loginUserHash;
};

#endif // QDIALOGLOGIN_H
