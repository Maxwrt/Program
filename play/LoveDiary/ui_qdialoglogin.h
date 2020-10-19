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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_QDialogLogin
{
public:
    QGridLayout *gridLayout;
    QLabel *labelPicture;
    QLabel *labelUser;
    QLineEdit *lineEditUser;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QRadioButton *radioButton;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonRegister;

    void setupUi(QDialog *QDialogLogin)
    {
        if (QDialogLogin->objectName().isEmpty())
            QDialogLogin->setObjectName(QStringLiteral("QDialogLogin"));
        QDialogLogin->resize(901, 523);
        gridLayout = new QGridLayout(QDialogLogin);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelPicture = new QLabel(QDialogLogin);
        labelPicture->setObjectName(QStringLiteral("labelPicture"));

        gridLayout->addWidget(labelPicture, 0, 0, 1, 11);

        labelUser = new QLabel(QDialogLogin);
        labelUser->setObjectName(QStringLiteral("labelUser"));

        gridLayout->addWidget(labelUser, 1, 0, 1, 1);

        lineEditUser = new QLineEdit(QDialogLogin);
        lineEditUser->setObjectName(QStringLiteral("lineEditUser"));

        gridLayout->addWidget(lineEditUser, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        labelPassword = new QLabel(QDialogLogin);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));

        gridLayout->addWidget(labelPassword, 1, 3, 1, 1);

        lineEditPassword = new QLineEdit(QDialogLogin);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));

        gridLayout->addWidget(lineEditPassword, 1, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 5, 1, 1);

        checkBox = new QCheckBox(QDialogLogin);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 1, 6, 1, 1);

        radioButton = new QRadioButton(QDialogLogin);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        gridLayout->addWidget(radioButton, 1, 7, 1, 1);

        pushButtonOk = new QPushButton(QDialogLogin);
        pushButtonOk->setObjectName(QStringLiteral("pushButtonOk"));

        gridLayout->addWidget(pushButtonOk, 1, 8, 1, 1);

        pushButtonCancel = new QPushButton(QDialogLogin);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        gridLayout->addWidget(pushButtonCancel, 1, 9, 1, 1);

        pushButtonRegister = new QPushButton(QDialogLogin);
        pushButtonRegister->setObjectName(QStringLiteral("pushButtonRegister"));

        gridLayout->addWidget(pushButtonRegister, 1, 10, 1, 1);

#ifndef QT_NO_SHORTCUT
        labelUser->setBuddy(lineEditUser);
        labelPassword->setBuddy(lineEditPassword);
#endif // QT_NO_SHORTCUT

        retranslateUi(QDialogLogin);

        QMetaObject::connectSlotsByName(QDialogLogin);
    } // setupUi

    void retranslateUi(QDialog *QDialogLogin)
    {
        QDialogLogin->setWindowTitle(QApplication::translate("QDialogLogin", "Dialog", 0));
        labelPicture->setText(QApplication::translate("QDialogLogin", "TextLabel", 0));
        labelUser->setText(QApplication::translate("QDialogLogin", "TextLabel", 0));
        labelPassword->setText(QApplication::translate("QDialogLogin", "TextLabel", 0));
        checkBox->setText(QApplication::translate("QDialogLogin", "\347\256\241\347\220\206\345\221\230", 0));
        radioButton->setText(QApplication::translate("QDialogLogin", "\347\224\267", 0));
        pushButtonOk->setText(QApplication::translate("QDialogLogin", "PushButton", 0));
        pushButtonCancel->setText(QApplication::translate("QDialogLogin", "PushButton", 0));
        pushButtonRegister->setText(QApplication::translate("QDialogLogin", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class QDialogLogin: public Ui_QDialogLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDIALOGLOGIN_H
