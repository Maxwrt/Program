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
#include <luatextedit.h>

QT_BEGIN_NAMESPACE

class Ui_AgreementDialog
{
public:
    QGridLayout *gridLayout;
    LuaTextEdit *textEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *AgreementDialog)
    {
        if (AgreementDialog->objectName().isEmpty())
            AgreementDialog->setObjectName(QStringLiteral("AgreementDialog"));
        AgreementDialog->resize(580, 499);
        gridLayout = new QGridLayout(AgreementDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit = new LuaTextEdit(AgreementDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        textEdit->setHeaderItem(__qtreewidgetitem);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(473, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton = new QPushButton(AgreementDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);


        retranslateUi(AgreementDialog);

        QMetaObject::connectSlotsByName(AgreementDialog);
    } // setupUi

    void retranslateUi(QDialog *AgreementDialog)
    {
        AgreementDialog->setWindowTitle(QApplication::translate("AgreementDialog", "Dialog", 0));
        pushButton->setText(QApplication::translate("AgreementDialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class AgreementDialog: public Ui_AgreementDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGREEMENTDIALOG_H
