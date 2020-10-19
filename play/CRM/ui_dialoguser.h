/********************************************************************************
** Form generated from reading UI file 'dialoguser.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGUSER_H
#define UI_DIALOGUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogUser
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnDelete;
    QPushButton *btnUpdate;
    QPushButton *btnInsert;
    QTableWidget *tableWidget;

    void setupUi(QDialog *DialogUser)
    {
        if (DialogUser->objectName().isEmpty())
            DialogUser->setObjectName(QStringLiteral("DialogUser"));
        DialogUser->resize(935, 509);
        gridLayout = new QGridLayout(DialogUser);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(570, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        btnDelete = new QPushButton(DialogUser);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        gridLayout->addWidget(btnDelete, 0, 1, 1, 1);

        btnUpdate = new QPushButton(DialogUser);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));

        gridLayout->addWidget(btnUpdate, 0, 2, 1, 1);

        btnInsert = new QPushButton(DialogUser);
        btnInsert->setObjectName(QStringLiteral("btnInsert"));

        gridLayout->addWidget(btnInsert, 0, 3, 1, 1);

        tableWidget = new QTableWidget(DialogUser);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 4);


        retranslateUi(DialogUser);

        QMetaObject::connectSlotsByName(DialogUser);
    } // setupUi

    void retranslateUi(QDialog *DialogUser)
    {
        DialogUser->setWindowTitle(QApplication::translate("DialogUser", "\347\274\226\350\276\221\347\263\273\347\273\237\347\224\250\346\210\267\344\277\241\346\201\257", 0));
        btnDelete->setText(QApplication::translate("DialogUser", "PushButton", 0));
        btnUpdate->setText(QApplication::translate("DialogUser", "PushButton", 0));
        btnInsert->setText(QApplication::translate("DialogUser", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogUser: public Ui_DialogUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGUSER_H
