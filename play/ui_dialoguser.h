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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogUser
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
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
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(570, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnDelete = new QPushButton(DialogUser);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnDelete->sizePolicy().hasHeightForWidth());
        btnDelete->setSizePolicy(sizePolicy);
        btnDelete->setStyleSheet(QStringLiteral("border-image: url(:/config/delete.png);"));

        horizontalLayout->addWidget(btnDelete);

        btnUpdate = new QPushButton(DialogUser);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));
        sizePolicy.setHeightForWidth(btnUpdate->sizePolicy().hasHeightForWidth());
        btnUpdate->setSizePolicy(sizePolicy);
        btnUpdate->setStyleSheet(QStringLiteral("border-image: url(:/config/update.png);"));

        horizontalLayout->addWidget(btnUpdate);

        btnInsert = new QPushButton(DialogUser);
        btnInsert->setObjectName(QStringLiteral("btnInsert"));
        sizePolicy.setHeightForWidth(btnInsert->sizePolicy().hasHeightForWidth());
        btnInsert->setSizePolicy(sizePolicy);
        btnInsert->setStyleSheet(QStringLiteral("border-image: url(:/config/insert.png);"));

        horizontalLayout->addWidget(btnInsert);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        tableWidget = new QTableWidget(DialogUser);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 1);


        retranslateUi(DialogUser);

        QMetaObject::connectSlotsByName(DialogUser);
    } // setupUi

    void retranslateUi(QDialog *DialogUser)
    {
        DialogUser->setWindowTitle(QApplication::translate("DialogUser", "\347\274\226\350\276\221\347\263\273\347\273\237\347\224\250\346\210\267\344\277\241\346\201\257", 0));
#ifndef QT_NO_TOOLTIP
        btnDelete->setToolTip(QApplication::translate("DialogUser", "<html><head/><body><p><span style=\" color:#ffaa00;\">\345\210\240\351\231\244</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnDelete->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnUpdate->setToolTip(QApplication::translate("DialogUser", "<html><head/><body><p><span style=\" color:#ffaa00;\">\346\233\264\346\226\260</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnUpdate->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnInsert->setToolTip(QApplication::translate("DialogUser", "<html><head/><body><p><span style=\" color:#ffaa00;\">\346\267\273\345\212\240</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnInsert->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogUser: public Ui_DialogUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGUSER_H
