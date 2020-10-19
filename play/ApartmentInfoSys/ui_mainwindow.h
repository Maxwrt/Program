/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QSplitter *splitter;
    QGroupBox *ApartmentGroupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *ApartmentLineEdit;
    QPushButton *ApartmentSearchButton;
    QTreeWidget *ApartmentTreeWidget;
    QGroupBox *StaffGroupBox;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *labelID;
    QLineEdit *StaffLineEdit;
    QPushButton *StaffSearchButton;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget;
    QWidget *tabStaff;
    QGridLayout *gridLayout;
    QTableView *StaffTableView;
    QWidget *tabBoy;
    QGridLayout *gridLayout_4;
    QTableView *BoyTableView;
    QWidget *tabGirl;
    QGridLayout *gridLayout_5;
    QTableView *GirlTableView;
    QWidget *tabAge;
    QGridLayout *gridLayout_7;
    QTableView *AgeTableView;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelInfo;
    QProgressBar *StaffProgressBar;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *StaffCloseButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(902, 659);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        ApartmentGroupBox = new QGroupBox(splitter);
        ApartmentGroupBox->setObjectName(QStringLiteral("ApartmentGroupBox"));
        ApartmentGroupBox->setMaximumSize(QSize(210, 16777215));
        gridLayout_2 = new QGridLayout(ApartmentGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        ApartmentLineEdit = new QLineEdit(ApartmentGroupBox);
        ApartmentLineEdit->setObjectName(QStringLiteral("ApartmentLineEdit"));

        gridLayout_2->addWidget(ApartmentLineEdit, 0, 0, 1, 1);

        ApartmentSearchButton = new QPushButton(ApartmentGroupBox);
        ApartmentSearchButton->setObjectName(QStringLiteral("ApartmentSearchButton"));

        gridLayout_2->addWidget(ApartmentSearchButton, 0, 1, 1, 1);

        ApartmentTreeWidget = new QTreeWidget(ApartmentGroupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        ApartmentTreeWidget->setHeaderItem(__qtreewidgetitem);
        ApartmentTreeWidget->setObjectName(QStringLiteral("ApartmentTreeWidget"));

        gridLayout_2->addWidget(ApartmentTreeWidget, 1, 0, 1, 2);

        splitter->addWidget(ApartmentGroupBox);
        StaffGroupBox = new QGroupBox(splitter);
        StaffGroupBox->setObjectName(QStringLiteral("StaffGroupBox"));
        gridLayout_6 = new QGridLayout(StaffGroupBox);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelID = new QLabel(StaffGroupBox);
        labelID->setObjectName(QStringLiteral("labelID"));

        horizontalLayout->addWidget(labelID);

        StaffLineEdit = new QLineEdit(StaffGroupBox);
        StaffLineEdit->setObjectName(QStringLiteral("StaffLineEdit"));

        horizontalLayout->addWidget(StaffLineEdit);

        StaffSearchButton = new QPushButton(StaffGroupBox);
        StaffSearchButton->setObjectName(QStringLiteral("StaffSearchButton"));
        StaffSearchButton->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(StaffSearchButton);

        horizontalSpacer = new QSpacerItem(372, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 1);

        tabWidget = new QTabWidget(StaffGroupBox);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tabStaff = new QWidget();
        tabStaff->setObjectName(QStringLiteral("tabStaff"));
        gridLayout = new QGridLayout(tabStaff);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        StaffTableView = new QTableView(tabStaff);
        StaffTableView->setObjectName(QStringLiteral("StaffTableView"));

        gridLayout->addWidget(StaffTableView, 0, 0, 1, 1);

        tabWidget->addTab(tabStaff, QString());
        tabBoy = new QWidget();
        tabBoy->setObjectName(QStringLiteral("tabBoy"));
        gridLayout_4 = new QGridLayout(tabBoy);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        BoyTableView = new QTableView(tabBoy);
        BoyTableView->setObjectName(QStringLiteral("BoyTableView"));

        gridLayout_4->addWidget(BoyTableView, 0, 0, 1, 1);

        tabWidget->addTab(tabBoy, QString());
        tabGirl = new QWidget();
        tabGirl->setObjectName(QStringLiteral("tabGirl"));
        gridLayout_5 = new QGridLayout(tabGirl);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        GirlTableView = new QTableView(tabGirl);
        GirlTableView->setObjectName(QStringLiteral("GirlTableView"));

        gridLayout_5->addWidget(GirlTableView, 0, 0, 1, 1);

        tabWidget->addTab(tabGirl, QString());
        tabAge = new QWidget();
        tabAge->setObjectName(QStringLiteral("tabAge"));
        gridLayout_7 = new QGridLayout(tabAge);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        AgeTableView = new QTableView(tabAge);
        AgeTableView->setObjectName(QStringLiteral("AgeTableView"));

        gridLayout_7->addWidget(AgeTableView, 0, 0, 1, 1);

        tabWidget->addTab(tabAge, QString());

        gridLayout_6->addWidget(tabWidget, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelInfo = new QLabel(StaffGroupBox);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));

        horizontalLayout_2->addWidget(labelInfo);

        StaffProgressBar = new QProgressBar(StaffGroupBox);
        StaffProgressBar->setObjectName(QStringLiteral("StaffProgressBar"));
        StaffProgressBar->setValue(24);

        horizontalLayout_2->addWidget(StaffProgressBar);

        horizontalSpacer_2 = new QSpacerItem(413, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        StaffCloseButton = new QPushButton(StaffGroupBox);
        StaffCloseButton->setObjectName(QStringLiteral("StaffCloseButton"));
        StaffCloseButton->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(StaffCloseButton);


        gridLayout_6->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        splitter->addWidget(StaffGroupBox);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 902, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        ApartmentGroupBox->setTitle(QString());
        ApartmentSearchButton->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276", 0));
        StaffGroupBox->setTitle(QString());
        labelID->setText(QApplication::translate("MainWindow", "\345\267\245\345\217\267:", 0));
        StaffSearchButton->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabStaff), QApplication::translate("MainWindow", "\351\203\250\351\227\250\345\220\215\347\247\260", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabBoy), QApplication::translate("MainWindow", "\347\224\267\347\224\237", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabGirl), QApplication::translate("MainWindow", "\345\245\263\347\224\237", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabAge), QApplication::translate("MainWindow", "\345\271\264\351\276\204", 0));
        labelInfo->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\345\212\240\350\275\275\346\225\260\346\215\256\302\267\302\267\302\267", 0));
        StaffCloseButton->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
