#ifndef QDIALOGLOGIN_H
#define QDIALOGLOGIN_H

#include <QDialog>
#include <QMouseEvent>
#include <QVariantList>
#include <QVariantHash>
#include <QSqlDatabase>
#include <QObject>
#include <QEvent>

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

private slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonRegister_clicked();
    void readsettings();
    void writesettings();
    void initDialog();
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

    /**
     * @brief eventFilter li'yong�����¼�����������׽�ؼ��¼�
     * @param obejct
     * @param event
     */
    bool eventFilter(QObject *watched, QEvent *event);
    QString encryptPasswd(const QString& password) ;

private:
    void opendb();
    void selectdb();
private:
    Ui::QDialogLogin *ui;

    int m_trynum=0;
    bool autoWriteUser;
    bool m_moving;
    QPoint m_lastPosition;
    QVariantList m_hashlist;
    QString m_user;
    QString m_password;
    QSqlDatabase  m_db;
};

#endif // QDIALOGLOGIN_H
