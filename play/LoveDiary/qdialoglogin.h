#ifndef QDIALOGLOGIN_H
#define QDIALOGLOGIN_H

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

class QDialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit QDialogLogin(const QSize& argsize, QWidget *parent = 0);
    ~QDialogLogin();
    int ShowLogin();
    QVariantHash GetUserHash() {return m_loginUserHash;}
    QSqlDatabase GetDB() {return m_db;}


private slots:
    void readsettings();
    void writesettings();
    void initDialog();
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *evnet);

    /**
     * @brief 利用事件过滤器来捕捉控件事件
     * @param obejct
     * @param event
     */
    bool eventFilter(QObject *watched, QEvent *event);
    QString encryptPasswd(const QString& password);

private:
    void opendb();
    void selectdb();
    void loadImages(const QString& dirpath);
    void setPicture(QPixmap *pixmap);
    int  generateDifferentIndex();

private:
    Ui::QDialogLogin *ui;

    int m_imageindex;
    int m_trynum;
    bool m_autoWriteUser;
    bool m_moving;
    QPoint m_lastPosition;
    QVariantList m_hashlist;
    QString m_user;
    QString m_password;
    QString m_verification;
    QHash<QString, QString> m_imageHash;
    QStringList m_keys;
    QPixmap m_pixmap;
    QSqlDatabase  m_db;
    QVariantHash m_loginUserHash;
};

#endif // QDIALOGLOGIN_H
