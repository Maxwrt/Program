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

namespace Ui {
class QDialogLogin;
}

class QDialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit QDialogLogin(QWidget *parent = 0);
    ~QDialogLogin();
    QVariantHash m_loginUserHash;
    int ShowLogin();

private slots:
    void readsettings();
    void writesettings();
    void initDialog();
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

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
    QSqlDatabase  m_db;
    QHash<QString, QString> m_imageHash;
    QStringList m_keys;
};

#endif // QDIALOGLOGIN_H
