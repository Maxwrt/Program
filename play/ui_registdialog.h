/********************************************************************************
** Form generated from reading UI file 'registdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTDIALOG_H
#define UI_REGISTDIALOG_H

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

class Ui_registDialog
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *labelOkPassword;
    QLineEdit *lineEditOkPassword;
    QRadioButton *radioButton;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonOk;
    QLabel *labelUser;
    QLineEdit *lineEditUser;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *registDialog)
    {
        if (registDialog->objectName().isEmpty())
            registDialog->setObjectName(QStringLiteral("registDialog"));
        registDialog->resize(483, 392);
        registDialog->setModal(true);
        gridLayout_2 = new QGridLayout(registDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 67, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(84, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelOkPassword = new QLabel(registDialog);
        labelOkPassword->setObjectName(QStringLiteral("labelOkPassword"));
        labelOkPassword->setStyleSheet(QStringLiteral("color:rgb(255, 170, 0)"));

        gridLayout->addWidget(labelOkPassword, 2, 0, 1, 1);

        lineEditOkPassword = new QLineEdit(registDialog);
        lineEditOkPassword->setObjectName(QStringLiteral("lineEditOkPassword"));

        gridLayout->addWidget(lineEditOkPassword, 2, 1, 1, 2);

        radioButton = new QRadioButton(registDialog);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setStyleSheet(QStringLiteral("color:rgb(255, 170, 0)"));

        gridLayout->addWidget(radioButton, 3, 0, 1, 1);

        checkBox = new QCheckBox(registDialog);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setStyleSheet(QStringLiteral("color:rgb(255, 170, 0)"));

        gridLayout->addWidget(checkBox, 3, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 2);

        labelPassword = new QLabel(registDialog);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));
        labelPassword->setStyleSheet(QStringLiteral("color:rgb(255, 170, 0)"));

        gridLayout->addWidget(labelPassword, 1, 0, 1, 1);

        lineEditPassword = new QLineEdit(registDialog);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));

        gridLayout->addWidget(lineEditPassword, 1, 1, 1, 2);

        pushButtonOk = new QPushButton(registDialog);
        pushButtonOk->setObjectName(QStringLiteral("pushButtonOk"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonOk->sizePolicy().hasHeightForWidth());
        pushButtonOk->setSizePolicy(sizePolicy);
        pushButtonOk->setStyleSheet(QLatin1String("color: rgb(255, 170, 0);\n"
"border-image: url(:/config/close.png);\n"
""));

        gridLayout->addWidget(pushButtonOk, 4, 2, 1, 1);

        labelUser = new QLabel(registDialog);
        labelUser->setObjectName(QStringLiteral("labelUser"));
        labelUser->setStyleSheet(QStringLiteral("color:rgb(255, 170, 0)"));

        gridLayout->addWidget(labelUser, 0, 0, 1, 1);

        lineEditUser = new QLineEdit(registDialog);
        lineEditUser->setObjectName(QStringLiteral("lineEditUser"));

        gridLayout->addWidget(lineEditUser, 0, 1, 1, 2);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(84, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 67, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(registDialog);

        QMetaObject::connectSlotsByName(registDialog);
    } // setupUi

    void retranslateUi(QDialog *registDialog)
    {
        registDialog->setWindowTitle(QApplication::translate("registDialog", "Dialog", 0));
        labelOkPassword->setText(QApplication::translate("registDialog", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", 0));
        radioButton->setText(QApplication::translate("registDialog", "   \347\224\267", 0));
        checkBox->setText(QApplication::translate("registDialog", "        \347\256\241\347\220\206\345\221\230", 0));
        labelPassword->setText(QApplication::translate("registDialog", "\345\257\206    \347\240\201\357\274\232", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonOk->setToolTip(QApplication::translate("registDialog", "<html><head/><body><p><span style=\" color:#ffaa00;\">\346\263\250\345\206\214</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButtonOk->setText(QString());
        labelUser->setText(QApplication::translate("registDialog", "\347\224\250 \346\210\267 \345\220\215\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class registDialog: public Ui_registDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTDIALOG_H
