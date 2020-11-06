/********************************************************************************
** Form generated from reading UI file 'Sender.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDER_H
#define UI_SENDER_H

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
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Sender
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_ip;
    QLabel *label_2;
    QLineEdit *lineEdit_port;
    QTextEdit *textEdit_history;
    QTextEdit *textEdit_data;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonSend;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *Sender)
    {
        if (Sender->objectName().isEmpty())
            Sender->setObjectName(QStringLiteral("Sender"));
        Sender->resize(685, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Sender->sizePolicy().hasHeightForWidth());
        Sender->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(Sender);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(Sender);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_ip = new QLineEdit(Sender);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));
        lineEdit_ip->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEdit_ip, 0, 1, 1, 1);

        label_2 = new QLabel(Sender);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_port = new QLineEdit(Sender);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));
        lineEdit_port->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEdit_port, 1, 1, 1, 1);

        textEdit_history = new QTextEdit(Sender);
        textEdit_history->setObjectName(QStringLiteral("textEdit_history"));

        gridLayout->addWidget(textEdit_history, 2, 0, 1, 4);

        textEdit_data = new QTextEdit(Sender);
        textEdit_data->setObjectName(QStringLiteral("textEdit_data"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit_data->sizePolicy().hasHeightForWidth());
        textEdit_data->setSizePolicy(sizePolicy1);
        textEdit_data->setMaximumSize(QSize(16777215, 130));

        gridLayout->addWidget(textEdit_data, 3, 0, 1, 4);

        horizontalSpacer_3 = new QSpacerItem(578, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 0, 1, 3);

        pushButtonSend = new QPushButton(Sender);
        pushButtonSend->setObjectName(QStringLiteral("pushButtonSend"));
        pushButtonSend->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(pushButtonSend, 4, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(502, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(502, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 2);


        retranslateUi(Sender);

        QMetaObject::connectSlotsByName(Sender);
    } // setupUi

    void retranslateUi(QDialog *Sender)
    {
        Sender->setWindowTitle(QApplication::translate("Sender", "Dialog", 0));
        label->setText(QApplication::translate("Sender", "IP\345\234\260\345\235\200:", 0));
        label_2->setText(QApplication::translate("Sender", "\347\253\257\345\217\243:", 0));
        pushButtonSend->setText(QApplication::translate("Sender", "\345\217\221\351\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class Sender: public Ui_Sender {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDER_H
