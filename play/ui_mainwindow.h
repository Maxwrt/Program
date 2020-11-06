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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEdit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_work;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_chat;
    QTextEdit *textEdit;
    QWidget *tab_life;
    QWidget *tab_love;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_together;
    QLCDNumber *lcdNumber;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_agreement;
    QPushButton *pushButton_us;
    QTableView *tableView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(913, 563);
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        actionEdit->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/config/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit->setIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::West);
        tab_work = new QWidget();
        tab_work->setObjectName(QStringLiteral("tab_work"));
        gridLayout_3 = new QGridLayout(tab_work);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(762, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        pushButton_chat = new QPushButton(tab_work);
        pushButton_chat->setObjectName(QStringLiteral("pushButton_chat"));

        gridLayout_3->addWidget(pushButton_chat, 0, 1, 1, 1);

        textEdit = new QTextEdit(tab_work);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout_3->addWidget(textEdit, 1, 0, 1, 2);

        tabWidget->addTab(tab_work, QString());
        tab_life = new QWidget();
        tab_life->setObjectName(QStringLiteral("tab_life"));
        tabWidget->addTab(tab_life, QString());
        tab_love = new QWidget();
        tab_love->setObjectName(QStringLiteral("tab_love"));
        gridLayout_2 = new QGridLayout(tab_love);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_together = new QLabel(tab_love);
        label_together->setObjectName(QStringLiteral("label_together"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_together->sizePolicy().hasHeightForWidth());
        label_together->setSizePolicy(sizePolicy);
        label_together->setSizeIncrement(QSize(400, 0));
        label_together->setBaseSize(QSize(1000, 0));

        horizontalLayout->addWidget(label_together);

        lcdNumber = new QLCDNumber(tab_love);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy1);
        lcdNumber->setMinimumSize(QSize(100, 0));
        lcdNumber->setMaximumSize(QSize(16777211, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        lcdNumber->setFont(font);
        lcdNumber->setStyleSheet(QLatin1String("background-color:rgb(85, 85, 0);\n"
"color:red;\n"
""));

        horizontalLayout->addWidget(lcdNumber);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_agreement = new QPushButton(tab_love);
        pushButton_agreement->setObjectName(QStringLiteral("pushButton_agreement"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_agreement->sizePolicy().hasHeightForWidth());
        pushButton_agreement->setSizePolicy(sizePolicy2);
        pushButton_agreement->setStyleSheet(QLatin1String("border-image: url(:/config/loveprotocol.png);\n"
"color: rgb(255, 170, 0);"));

        horizontalLayout->addWidget(pushButton_agreement);

        pushButton_us = new QPushButton(tab_love);
        pushButton_us->setObjectName(QStringLiteral("pushButton_us"));
        sizePolicy2.setHeightForWidth(pushButton_us->sizePolicy().hasHeightForWidth());
        pushButton_us->setSizePolicy(sizePolicy2);
        pushButton_us->setStyleSheet(QLatin1String("border-image: url(:/config/us.png);\n"
"color: rgb(255, 170, 0);"));

        horizontalLayout->addWidget(pushButton_us);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        tableView = new QTableView(tab_love);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setMaximumSize(QSize(16777215, 16777211));

        gridLayout_2->addWidget(tableView, 1, 0, 1, 1);

        tabWidget->addTab(tab_love, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 913, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addSeparator();
        menu->addSeparator();
        menu->addSeparator();
        menu->addSeparator();
        menu->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionEdit->setText(QApplication::translate("MainWindow", "\347\274\226\350\276\221", 0));
#ifndef QT_NO_TOOLTIP
        actionEdit->setToolTip(QApplication::translate("MainWindow", "\347\274\226\350\276\221\347\224\250\346\210\267", 0));
#endif // QT_NO_TOOLTIP
        pushButton_chat->setText(QApplication::translate("MainWindow", "\350\201\212\345\244\251", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_work), QApplication::translate("MainWindow", "WORK", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_life), QApplication::translate("MainWindow", "LIFE", 0));
        label_together->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_agreement->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffaa00;\">\347\210\261\346\203\205\344\271\246</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButton_agreement->setText(QString());
        pushButton_us->setText(QApplication::translate("MainWindow", "\346\210\221\344\273\254", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_love), QApplication::translate("MainWindow", "LOVE", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
