/********************************************************************************
** Form generated from reading UI file 'agreementdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGREEMENTDIALOG_H
#define UI_AGREEMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <luatextedit.h>

QT_BEGIN_NAMESPACE

class Ui_AgreementDialog
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    LuaTextEdit *plainTextEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *AgreementDialog)
    {
        if (AgreementDialog->objectName().isEmpty())
            AgreementDialog->setObjectName(QStringLiteral("AgreementDialog"));
        AgreementDialog->resize(577, 597);
        AgreementDialog->setModal(true);
        gridLayout_2 = new QGridLayout(AgreementDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget = new QWidget(AgreementDialog);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit = new LuaTextEdit(widget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(452, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setStyleSheet(QLatin1String("border-image: url(:/config/close.png);\n"
"color: rgb(255, 170, 0);"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        pushButton->raise();
        plainTextEdit->raise();

        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(AgreementDialog);

        QMetaObject::connectSlotsByName(AgreementDialog);
    } // setupUi

    void retranslateUi(QDialog *AgreementDialog)
    {
        AgreementDialog->setWindowTitle(QApplication::translate("AgreementDialog", "Dialog", 0));
#ifndef QT_NO_TOOLTIP
        pushButton->setToolTip(QApplication::translate("AgreementDialog", "<html><head/><body><p><span style=\" color:#ffaa00;\">\345\205\263\351\227\255</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("AgreementDialog", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class AgreementDialog: public Ui_AgreementDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGREEMENTDIALOG_H
