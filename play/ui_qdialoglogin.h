/********************************************************************************
** Form generated from reading UI file 'qdialoglogin.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QDIALOGLOGIN_H
#define UI_QDIALOGLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <verificationcodelabel.h>

QT_BEGIN_NAMESPACE

class Ui_QDialogLogin
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QPushButton *pushButtonForgetPassword;
    QPushButton *pushButtonCancel;
    QLabel *labelUser;
    QLineEdit *lineEditUser;
    QLineEdit *lineEditPassword;
    QLabel *labelPassword;
    QLabel *labelVerification;
    QLineEdit *lineEditVerification;
    VerificationCodeLabel *labelVerificationCode;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonRegister;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *QDialogLogin)
    {
        if (QDialogLogin->objectName().isEmpty())
            QDialogLogin->setObjectName(QStringLiteral("QDialogLogin"));
        QDialogLogin->resize(617, 567);
        gridLayout_2 = new QGridLayout(QDialogLogin);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 213, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        pushButtonForgetPassword = new QPushButton(QDialogLogin);
        pushButtonForgetPassword->setObjectName(QStringLiteral("pushButtonForgetPassword"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonForgetPassword->sizePolicy().hasHeightForWidth());
        pushButtonForgetPassword->setSizePolicy(sizePolicy);
        pushButtonForgetPassword->setStyleSheet(QLatin1String("color: rgb(255, 170, 0);\n"
"border-image: url(:/config/insert.png);"));

        gridLayout->addWidget(pushButtonForgetPassword, 3, 2, 1, 1);

        pushButtonCancel = new QPushButton(QDialogLogin);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        sizePolicy.setHeightForWidth(pushButtonCancel->sizePolicy().hasHeightForWidth());
        pushButtonCancel->setSizePolicy(sizePolicy);
        pushButtonCancel->setStyleSheet(QLatin1String("color: rgb(255, 170, 0);\n"
"border-image: url(:/config/close.png);"));

        gridLayout->addWidget(pushButtonCancel, 3, 1, 1, 1);

        labelUser = new QLabel(QDialogLogin);
        labelUser->setObjectName(QStringLiteral("labelUser"));
        labelUser->setStyleSheet(QStringLiteral("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(labelUser, 0, 0, 1, 1);

        lineEditUser = new QLineEdit(QDialogLogin);
        lineEditUser->setObjectName(QStringLiteral("lineEditUser"));

        gridLayout->addWidget(lineEditUser, 0, 1, 1, 1);

        lineEditPassword = new QLineEdit(QDialogLogin);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));

        gridLayout->addWidget(lineEditPassword, 1, 1, 1, 1);

        labelPassword = new QLabel(QDialogLogin);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));
        labelPassword->setStyleSheet(QStringLiteral("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(labelPassword, 1, 0, 1, 1);

        labelVerification = new QLabel(QDialogLogin);
        labelVerification->setObjectName(QStringLiteral("labelVerification"));
        labelVerification->setLayoutDirection(Qt::LeftToRight);
        labelVerification->setAutoFillBackground(true);
        labelVerification->setStyleSheet(QStringLiteral("color: rgb(255, 170, 0);"));

        gridLayout->addWidget(labelVerification, 2, 0, 1, 1);

        lineEditVerification = new QLineEdit(QDialogLogin);
        lineEditVerification->setObjectName(QStringLiteral("lineEditVerification"));

        gridLayout->addWidget(lineEditVerification, 2, 1, 1, 1);

        labelVerificationCode = new VerificationCodeLabel(QDialogLogin);
        labelVerificationCode->setObjectName(QStringLiteral("labelVerificationCode"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelVerificationCode->sizePolicy().hasHeightForWidth());
        labelVerificationCode->setSizePolicy(sizePolicy1);
        labelVerificationCode->setMinimumSize(QSize(80, 0));
        labelVerificationCode->setLayoutDirection(Qt::LeftToRight);
        labelVerificationCode->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(labelVerificationCode, 2, 2, 1, 1);

        pushButtonOk = new QPushButton(QDialogLogin);
        pushButtonOk->setObjectName(QStringLiteral("pushButtonOk"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(25);
        sizePolicy2.setVerticalStretch(25);
        sizePolicy2.setHeightForWidth(pushButtonOk->sizePolicy().hasHeightForWidth());
        pushButtonOk->setSizePolicy(sizePolicy2);
        pushButtonOk->setLayoutDirection(Qt::LeftToRight);
        pushButtonOk->setStyleSheet(QLatin1String("color: rgb(255, 170, 0);\n"
"border-image: url(:/config/delete.png);"));

        gridLayout->addWidget(pushButtonOk, 3, 0, 1, 1);

        pushButtonRegister = new QPushButton(QDialogLogin);
        pushButtonRegister->setObjectName(QStringLiteral("pushButtonRegister"));
        sizePolicy.setHeightForWidth(pushButtonRegister->sizePolicy().hasHeightForWidth());
        pushButtonRegister->setSizePolicy(sizePolicy);
        pushButtonRegister->setLayoutDirection(Qt::LeftToRight);
        pushButtonRegister->setStyleSheet(QLatin1String("color: rgb(255, 170, 0);\n"
"border-image: url(:/config/update.png);"));

        gridLayout->addWidget(pushButtonRegister, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(149, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 212, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        labelUser->setBuddy(lineEditUser);
        labelPassword->setBuddy(lineEditPassword);
        labelVerification->setBuddy(lineEditPassword);
        labelVerificationCode->setBuddy(lineEditPassword);
#endif // QT_NO_SHORTCUT

        retranslateUi(QDialogLogin);

        QMetaObject::connectSlotsByName(QDialogLogin);
    } // setupUi

    void retranslateUi(QDialog *QDialogLogin)
    {
        QDialogLogin->setWindowTitle(QApplication::translate("QDialogLogin", "Dialog", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonForgetPassword->setToolTip(QApplication::translate("QDialogLogin", "<html><head/><body><p><span style=\" color:#ffaa00;\">\346\211\276\345\233\236\345\257\206\347\240\201</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButtonForgetPassword->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonCancel->setToolTip(QApplication::translate("QDialogLogin", "<html><head/><body><p><span style=\" color:#ffaa00;\">\345\205\263\351\227\255</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButtonCancel->setText(QString());
        labelUser->setText(QApplication::translate("QDialogLogin", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
#ifndef QT_NO_TOOLTIP
        labelPassword->setToolTip(QApplication::translate("QDialogLogin", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        labelPassword->setText(QApplication::translate("QDialogLogin", "\345\257\206  \347\240\201\357\274\232", 0));
#ifndef QT_NO_TOOLTIP
        labelVerification->setToolTip(QApplication::translate("QDialogLogin", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        labelVerification->setText(QApplication::translate("QDialogLogin", "\351\252\214\350\257\201\347\240\201\357\274\232", 0));
#ifndef QT_NO_WHATSTHIS
        labelVerificationCode->setWhatsThis(QApplication::translate("QDialogLogin", "<html><head/><body><p><span style=\" color:#ffaa00;\">\351\252\214\350\257\201\347\240\201</span></p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        labelVerificationCode->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonOk->setToolTip(QApplication::translate("QDialogLogin", "<html><head/><body><p><span style=\" color:#ffaa00;\">\347\231\273\345\275\225</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButtonOk->setText(QString());
#ifndef QT_NO_WHATSTHIS
        pushButtonRegister->setWhatsThis(QApplication::translate("QDialogLogin", "<html><head/><body><p><span style=\" color:#ffaa00;\">\346\226\260\347\224\250\346\210\267\346\263\250\345\206\214</span></p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        pushButtonRegister->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QDialogLogin: public Ui_QDialogLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDIALOGLOGIN_H
