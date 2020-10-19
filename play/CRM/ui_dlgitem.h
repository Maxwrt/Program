/********************************************************************************
** Form generated from reading UI file 'dlgitem.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGITEM_H
#define UI_DLGITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_DlgItem
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QLineEdit *edit1;
    QLabel *label;
    QComboBox *combo1;
    QLabel *label_3;
    QLineEdit *edit3;
    QLabel *label_5;
    QLabel *label_7;
    QComboBox *combo2;
    QLineEdit *edit4;
    QLabel *label_2;
    QLineEdit *edit2;
    QLabel *label_4;
    QComboBox *combo3;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QTextEdit *textEdit;
    QLabel *label_10;
    QTextEdit *textEdit2;
    QLabel *label_11;
    QTextEdit *textEdit3;
    QLabel *label_9;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelTip;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;
    QPushButton *btnCancel;

    void setupUi(QDialog *DlgItem)
    {
        if (DlgItem->objectName().isEmpty())
            DlgItem->setObjectName(QStringLiteral("DlgItem"));
        DlgItem->resize(1062, 709);
        gridLayout_3 = new QGridLayout(DlgItem);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_6 = new QLabel(DlgItem);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        edit1 = new QLineEdit(DlgItem);
        edit1->setObjectName(QStringLiteral("edit1"));
        edit1->setMinimumSize(QSize(0, 25));
        edit1->setMaximumSize(QSize(400, 16777215));

        gridLayout_2->addWidget(edit1, 0, 1, 1, 1);

        label = new QLabel(DlgItem);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 2, 0, 1, 1);

        combo1 = new QComboBox(DlgItem);
        combo1->setObjectName(QStringLiteral("combo1"));
        combo1->setMinimumSize(QSize(0, 25));
        combo1->setMaximumSize(QSize(200, 16777215));

        gridLayout_2->addWidget(combo1, 1, 1, 1, 1);

        label_3 = new QLabel(DlgItem);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 4, 0, 1, 1);

        edit3 = new QLineEdit(DlgItem);
        edit3->setObjectName(QStringLiteral("edit3"));
        edit3->setMinimumSize(QSize(0, 25));
        edit3->setMaximumSize(QSize(400, 16777215));

        gridLayout_2->addWidget(edit3, 5, 1, 1, 1);

        label_5 = new QLabel(DlgItem);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 6, 0, 1, 1);

        label_7 = new QLabel(DlgItem);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        combo2 = new QComboBox(DlgItem);
        combo2->setObjectName(QStringLiteral("combo2"));
        combo2->setMinimumSize(QSize(0, 25));
        combo2->setMaximumSize(QSize(200, 16777215));

        gridLayout_2->addWidget(combo2, 2, 1, 1, 1);

        edit4 = new QLineEdit(DlgItem);
        edit4->setObjectName(QStringLiteral("edit4"));
        edit4->setMinimumSize(QSize(0, 25));
        edit4->setMaximumSize(QSize(400, 16777215));

        gridLayout_2->addWidget(edit4, 6, 1, 1, 1);

        label_2 = new QLabel(DlgItem);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 3, 0, 1, 1);

        edit2 = new QLineEdit(DlgItem);
        edit2->setObjectName(QStringLiteral("edit2"));
        edit2->setMinimumSize(QSize(0, 25));
        edit2->setMaximumSize(QSize(400, 16777215));

        gridLayout_2->addWidget(edit2, 4, 1, 1, 1);

        label_4 = new QLabel(DlgItem);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 5, 0, 1, 1);

        combo3 = new QComboBox(DlgItem);
        combo3->setObjectName(QStringLiteral("combo3"));
        combo3->setMinimumSize(QSize(0, 25));
        combo3->setMaximumSize(QSize(200, 16777215));

        gridLayout_2->addWidget(combo3, 3, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_8 = new QLabel(DlgItem);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        textEdit = new QTextEdit(DlgItem);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 0, 1, 1, 1);

        label_10 = new QLabel(DlgItem);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        textEdit2 = new QTextEdit(DlgItem);
        textEdit2->setObjectName(QStringLiteral("textEdit2"));

        gridLayout->addWidget(textEdit2, 1, 1, 1, 1);

        label_11 = new QLabel(DlgItem);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 2, 0, 1, 1);

        textEdit3 = new QTextEdit(DlgItem);
        textEdit3->setObjectName(QStringLiteral("textEdit3"));

        gridLayout->addWidget(textEdit3, 2, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        label_9 = new QLabel(DlgItem);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_3->addWidget(label_9, 1, 0, 1, 1);

        tableWidget = new QTableWidget(DlgItem);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(0, 350));
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(150);
        tableWidget->horizontalHeader()->setMinimumSectionSize(100);
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        gridLayout_3->addWidget(tableWidget, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelTip = new QLabel(DlgItem);
        labelTip->setObjectName(QStringLiteral("labelTip"));
        labelTip->setMinimumSize(QSize(400, 0));

        horizontalLayout->addWidget(labelTip);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAdd = new QPushButton(DlgItem);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(btnAdd);

        btnCancel = new QPushButton(DlgItem);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(btnCancel);


        gridLayout_3->addLayout(horizontalLayout, 3, 0, 1, 1);


        retranslateUi(DlgItem);

        QMetaObject::connectSlotsByName(DlgItem);
    } // setupUi

    void retranslateUi(QDialog *DlgItem)
    {
        DlgItem->setWindowTitle(QApplication::translate("DlgItem", "\347\274\226\350\276\221\345\256\242\346\210\267\344\277\241\346\201\257", 0));
        label_6->setText(QApplication::translate("DlgItem", "CompanyName\357\274\232", 0));
        label->setText(QApplication::translate("DlgItem", "Area\357\274\232", 0));
        label_3->setText(QApplication::translate("DlgItem", "City\357\274\232", 0));
        label_5->setText(QApplication::translate("DlgItem", "Https\357\274\232", 0));
        label_7->setText(QApplication::translate("DlgItem", "CompanyType\357\274\232", 0));
        label_2->setText(QApplication::translate("DlgItem", "Province\357\274\232", 0));
        label_4->setText(QApplication::translate("DlgItem", "Address\357\274\232", 0));
        label_8->setText(QApplication::translate("DlgItem", "Buy\357\274\232", 0));
        label_10->setText(QApplication::translate("DlgItem", "Search\357\274\232", 0));
        label_11->setText(QApplication::translate("DlgItem", "Beizhu\357\274\232", 0));
        label_9->setText(QApplication::translate("DlgItem", "CantactWay\357\274\232", 0));
        labelTip->setText(QString());
        btnAdd->setText(QApplication::translate("DlgItem", "add", 0));
        btnCancel->setText(QApplication::translate("DlgItem", "cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgItem: public Ui_DlgItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGITEM_H
