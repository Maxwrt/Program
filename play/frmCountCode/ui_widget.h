/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_filenum;
    QLineEdit *lineEdit_filenum;
    QLabel *label_codelinenum;
    QLineEdit *lineEdit_codeline;
    QLabel *label_codelineper;
    QLabel *label_filename;
    QLineEdit *lineEdit_filename;
    QLabel *label_bytenum;
    QLineEdit *lineEdit_bytenum;
    QLabel *label_commentlinenum;
    QLineEdit *lineEdit_commentnum;
    QLabel *label_commentper;
    QLabel *label_dirname;
    QLineEdit *lineEdit_dirname;
    QLabel *label_totallinenum;
    QLineEdit *lineEdit_totalline;
    QLabel *label_blanklinenum;
    QLineEdit *lineEdit_blanknum;
    QLabel *label_blanklineper;
    QLabel *label_filter;
    QLineEdit *lineEdit_filter;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_openfile;
    QPushButton *pushButton_opendir;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_exportfile;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(959, 571);
        Widget->setMinimumSize(QSize(48, 22));
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableWidget = new QTableWidget(Widget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(0, 431));

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_filenum = new QLabel(Widget);
        label_filenum->setObjectName(QStringLiteral("label_filenum"));

        gridLayout->addWidget(label_filenum, 0, 0, 1, 1);

        lineEdit_filenum = new QLineEdit(Widget);
        lineEdit_filenum->setObjectName(QStringLiteral("lineEdit_filenum"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_filenum->sizePolicy().hasHeightForWidth());
        lineEdit_filenum->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_filenum, 0, 1, 1, 1);

        label_codelinenum = new QLabel(Widget);
        label_codelinenum->setObjectName(QStringLiteral("label_codelinenum"));

        gridLayout->addWidget(label_codelinenum, 0, 2, 1, 1);

        lineEdit_codeline = new QLineEdit(Widget);
        lineEdit_codeline->setObjectName(QStringLiteral("lineEdit_codeline"));
        sizePolicy.setHeightForWidth(lineEdit_codeline->sizePolicy().hasHeightForWidth());
        lineEdit_codeline->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_codeline, 0, 3, 1, 1);

        label_codelineper = new QLabel(Widget);
        label_codelineper->setObjectName(QStringLiteral("label_codelineper"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(48);
        sizePolicy1.setVerticalStretch(22);
        sizePolicy1.setHeightForWidth(label_codelineper->sizePolicy().hasHeightForWidth());
        label_codelineper->setSizePolicy(sizePolicy1);
        label_codelineper->setMinimumSize(QSize(48, 22));

        gridLayout->addWidget(label_codelineper, 0, 4, 1, 1);

        label_filename = new QLabel(Widget);
        label_filename->setObjectName(QStringLiteral("label_filename"));

        gridLayout->addWidget(label_filename, 0, 5, 1, 1);

        lineEdit_filename = new QLineEdit(Widget);
        lineEdit_filename->setObjectName(QStringLiteral("lineEdit_filename"));

        gridLayout->addWidget(lineEdit_filename, 0, 6, 1, 1);

        label_bytenum = new QLabel(Widget);
        label_bytenum->setObjectName(QStringLiteral("label_bytenum"));

        gridLayout->addWidget(label_bytenum, 1, 0, 1, 1);

        lineEdit_bytenum = new QLineEdit(Widget);
        lineEdit_bytenum->setObjectName(QStringLiteral("lineEdit_bytenum"));
        sizePolicy.setHeightForWidth(lineEdit_bytenum->sizePolicy().hasHeightForWidth());
        lineEdit_bytenum->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_bytenum, 1, 1, 1, 1);

        label_commentlinenum = new QLabel(Widget);
        label_commentlinenum->setObjectName(QStringLiteral("label_commentlinenum"));

        gridLayout->addWidget(label_commentlinenum, 1, 2, 1, 1);

        lineEdit_commentnum = new QLineEdit(Widget);
        lineEdit_commentnum->setObjectName(QStringLiteral("lineEdit_commentnum"));
        sizePolicy.setHeightForWidth(lineEdit_commentnum->sizePolicy().hasHeightForWidth());
        lineEdit_commentnum->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_commentnum, 1, 3, 1, 1);

        label_commentper = new QLabel(Widget);
        label_commentper->setObjectName(QStringLiteral("label_commentper"));
        sizePolicy.setHeightForWidth(label_commentper->sizePolicy().hasHeightForWidth());
        label_commentper->setSizePolicy(sizePolicy);
        label_commentper->setMinimumSize(QSize(48, 22));

        gridLayout->addWidget(label_commentper, 1, 4, 1, 1);

        label_dirname = new QLabel(Widget);
        label_dirname->setObjectName(QStringLiteral("label_dirname"));

        gridLayout->addWidget(label_dirname, 1, 5, 1, 1);

        lineEdit_dirname = new QLineEdit(Widget);
        lineEdit_dirname->setObjectName(QStringLiteral("lineEdit_dirname"));

        gridLayout->addWidget(lineEdit_dirname, 1, 6, 1, 1);

        label_totallinenum = new QLabel(Widget);
        label_totallinenum->setObjectName(QStringLiteral("label_totallinenum"));

        gridLayout->addWidget(label_totallinenum, 2, 0, 1, 1);

        lineEdit_totalline = new QLineEdit(Widget);
        lineEdit_totalline->setObjectName(QStringLiteral("lineEdit_totalline"));
        sizePolicy.setHeightForWidth(lineEdit_totalline->sizePolicy().hasHeightForWidth());
        lineEdit_totalline->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_totalline, 2, 1, 1, 1);

        label_blanklinenum = new QLabel(Widget);
        label_blanklinenum->setObjectName(QStringLiteral("label_blanklinenum"));

        gridLayout->addWidget(label_blanklinenum, 2, 2, 1, 1);

        lineEdit_blanknum = new QLineEdit(Widget);
        lineEdit_blanknum->setObjectName(QStringLiteral("lineEdit_blanknum"));
        sizePolicy.setHeightForWidth(lineEdit_blanknum->sizePolicy().hasHeightForWidth());
        lineEdit_blanknum->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_blanknum, 2, 3, 1, 1);

        label_blanklineper = new QLabel(Widget);
        label_blanklineper->setObjectName(QStringLiteral("label_blanklineper"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_blanklineper->sizePolicy().hasHeightForWidth());
        label_blanklineper->setSizePolicy(sizePolicy2);
        label_blanklineper->setMinimumSize(QSize(48, 22));

        gridLayout->addWidget(label_blanklineper, 2, 4, 1, 1);

        label_filter = new QLabel(Widget);
        label_filter->setObjectName(QStringLiteral("label_filter"));

        gridLayout->addWidget(label_filter, 2, 5, 1, 1);

        lineEdit_filter = new QLineEdit(Widget);
        lineEdit_filter->setObjectName(QStringLiteral("lineEdit_filter"));

        gridLayout->addWidget(lineEdit_filter, 2, 6, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_openfile = new QPushButton(Widget);
        pushButton_openfile->setObjectName(QStringLiteral("pushButton_openfile"));

        verticalLayout->addWidget(pushButton_openfile);

        pushButton_opendir = new QPushButton(Widget);
        pushButton_opendir->setObjectName(QStringLiteral("pushButton_opendir"));

        verticalLayout->addWidget(pushButton_opendir);

        pushButton_clear = new QPushButton(Widget);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));

        verticalLayout->addWidget(pushButton_clear);

        pushButton_exportfile = new QPushButton(Widget);
        pushButton_exportfile->setObjectName(QStringLiteral("pushButton_exportfile"));

        verticalLayout->addWidget(pushButton_exportfile);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        label_filenum->setText(QApplication::translate("Widget", "\346\226\207\344\273\266\346\225\260", 0));
        label_codelinenum->setText(QApplication::translate("Widget", "\344\273\243\347\240\201\350\241\214\346\225\260", 0));
        label_codelineper->setText(QString());
        label_filename->setText(QApplication::translate("Widget", "\346\226\207\344\273\266", 0));
        label_bytenum->setText(QApplication::translate("Widget", "\345\255\227\350\212\202\346\225\260", 0));
        label_commentlinenum->setText(QApplication::translate("Widget", "\346\263\250\351\207\212\350\241\214\346\225\260", 0));
        label_commentper->setText(QString());
        label_dirname->setText(QApplication::translate("Widget", "\347\233\256\345\275\225", 0));
        label_totallinenum->setText(QApplication::translate("Widget", "\346\200\273\350\241\214\346\225\260", 0));
        label_blanklinenum->setText(QApplication::translate("Widget", "\347\251\272\347\231\275\350\241\214\346\225\260", 0));
        label_blanklineper->setText(QString());
        label_filter->setText(QApplication::translate("Widget", "\350\277\207\346\273\244", 0));
        pushButton_openfile->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\346\226\207\344\273\266", 0));
        pushButton_opendir->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\347\233\256\345\275\225", 0));
        pushButton_clear->setText(QApplication::translate("Widget", "\346\270\205\347\251\272\347\273\223\346\236\234", 0));
        pushButton_exportfile->setText(QApplication::translate("Widget", "\345\257\274\345\207\272\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
