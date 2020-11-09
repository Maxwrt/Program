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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actOpen;
    QAction *actSave;
    QAction *actExit;
    QAction *actOpenFile;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *labelDir;
    QLineEdit *lineEditDir;
    QLabel *labelFile;
    QLineEdit *lineEditFile;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonCompare;
    QPushButton *pushButtonSynchronize;
    QPushButton *pushButtonCompare1;
    QPushButton *pushButtonSynchronize1;
    QPushButton *pushButtonCompare2;
    QPushButton *pushButtonSynchronize2;
    QPushButton *pushButtonInfoTip;
    QTableView *tableView;
    QProgressBar *progressBar;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(914, 718);
        actOpen = new QAction(MainWindow);
        actOpen->setObjectName(QStringLiteral("actOpen"));
        actOpen->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/open.png"), QSize(), QIcon::Normal, QIcon::On);
        actOpen->setIcon(icon);
        actSave = new QAction(MainWindow);
        actSave->setObjectName(QStringLiteral("actSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/save.png"), QSize(), QIcon::Normal, QIcon::On);
        actSave->setIcon(icon1);
        actExit = new QAction(MainWindow);
        actExit->setObjectName(QStringLiteral("actExit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/image/exit.png"), QSize(), QIcon::Normal, QIcon::On);
        actExit->setIcon(icon2);
        actOpenFile = new QAction(MainWindow);
        actOpenFile->setObjectName(QStringLiteral("actOpenFile"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/image/paste.png"), QSize(), QIcon::Normal, QIcon::On);
        actOpenFile->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelDir = new QLabel(centralWidget);
        labelDir->setObjectName(QStringLiteral("labelDir"));

        gridLayout->addWidget(labelDir, 0, 0, 1, 1);

        lineEditDir = new QLineEdit(centralWidget);
        lineEditDir->setObjectName(QStringLiteral("lineEditDir"));

        gridLayout->addWidget(lineEditDir, 0, 1, 1, 1);

        labelFile = new QLabel(centralWidget);
        labelFile->setObjectName(QStringLiteral("labelFile"));

        gridLayout->addWidget(labelFile, 0, 2, 1, 1);

        lineEditFile = new QLineEdit(centralWidget);
        lineEditFile->setObjectName(QStringLiteral("lineEditFile"));

        gridLayout->addWidget(lineEditFile, 0, 3, 1, 1);

        pushButtonDelete = new QPushButton(centralWidget);
        pushButtonDelete->setObjectName(QStringLiteral("pushButtonDelete"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonDelete->sizePolicy().hasHeightForWidth());
        pushButtonDelete->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonDelete, 0, 4, 1, 1);

        pushButtonCompare = new QPushButton(centralWidget);
        pushButtonCompare->setObjectName(QStringLiteral("pushButtonCompare"));
        sizePolicy.setHeightForWidth(pushButtonCompare->sizePolicy().hasHeightForWidth());
        pushButtonCompare->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonCompare, 0, 5, 1, 1);

        pushButtonSynchronize = new QPushButton(centralWidget);
        pushButtonSynchronize->setObjectName(QStringLiteral("pushButtonSynchronize"));
        sizePolicy.setHeightForWidth(pushButtonSynchronize->sizePolicy().hasHeightForWidth());
        pushButtonSynchronize->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonSynchronize, 0, 6, 1, 1);

        pushButtonCompare1 = new QPushButton(centralWidget);
        pushButtonCompare1->setObjectName(QStringLiteral("pushButtonCompare1"));
        sizePolicy.setHeightForWidth(pushButtonCompare1->sizePolicy().hasHeightForWidth());
        pushButtonCompare1->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonCompare1, 0, 7, 1, 1);

        pushButtonSynchronize1 = new QPushButton(centralWidget);
        pushButtonSynchronize1->setObjectName(QStringLiteral("pushButtonSynchronize1"));
        sizePolicy.setHeightForWidth(pushButtonSynchronize1->sizePolicy().hasHeightForWidth());
        pushButtonSynchronize1->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonSynchronize1, 0, 8, 1, 1);

        pushButtonCompare2 = new QPushButton(centralWidget);
        pushButtonCompare2->setObjectName(QStringLiteral("pushButtonCompare2"));
        sizePolicy.setHeightForWidth(pushButtonCompare2->sizePolicy().hasHeightForWidth());
        pushButtonCompare2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonCompare2, 0, 9, 1, 1);

        pushButtonSynchronize2 = new QPushButton(centralWidget);
        pushButtonSynchronize2->setObjectName(QStringLiteral("pushButtonSynchronize2"));
        sizePolicy.setHeightForWidth(pushButtonSynchronize2->sizePolicy().hasHeightForWidth());
        pushButtonSynchronize2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonSynchronize2, 0, 10, 1, 1);

        pushButtonInfoTip = new QPushButton(centralWidget);
        pushButtonInfoTip->setObjectName(QStringLiteral("pushButtonInfoTip"));
        sizePolicy.setHeightForWidth(pushButtonInfoTip->sizePolicy().hasHeightForWidth());
        pushButtonInfoTip->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonInfoTip, 0, 11, 1, 1);

        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 1, 0, 1, 12);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 2, 0, 1, 12);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(textEdit, 3, 0, 1, 12);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 914, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\347\233\256\345\275\225", 0));
#ifndef QT_NO_TOOLTIP
        actOpen->setToolTip(QApplication::translate("MainWindow", "\346\211\223\345\274\200\347\233\256\345\275\225", 0));
#endif // QT_NO_TOOLTIP
        actOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", 0));
#ifndef QT_NO_TOOLTIP
        actSave->setToolTip(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", 0));
#endif // QT_NO_TOOLTIP
        actSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
#ifndef QT_NO_TOOLTIP
        actExit->setToolTip(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237", 0));
#endif // QT_NO_TOOLTIP
        actExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0));
        actOpenFile->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", 0));
#ifndef QT_NO_TOOLTIP
        actOpenFile->setToolTip(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", 0));
#endif // QT_NO_TOOLTIP
        labelDir->setText(QApplication::translate("MainWindow", "\347\233\256\345\275\225:", 0));
        labelFile->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266:", 0));
        pushButtonDelete->setText(QApplication::translate("MainWindow", "\346\270\205\351\231\244", 0));
        pushButtonCompare->setText(QApplication::translate("MainWindow", "\346\257\224\350\276\203", 0));
        pushButtonSynchronize->setText(QApplication::translate("MainWindow", "\345\220\214\346\255\245", 0));
        pushButtonCompare1->setText(QApplication::translate("MainWindow", "\346\257\224\350\276\2031", 0));
        pushButtonSynchronize1->setText(QApplication::translate("MainWindow", "\345\220\214\346\255\2451", 0));
        pushButtonCompare2->setText(QApplication::translate("MainWindow", "\346\257\224\350\276\2032", 0));
        pushButtonSynchronize2->setText(QApplication::translate("MainWindow", "\345\220\214\346\255\2452", 0));
        pushButtonInfoTip->setText(QApplication::translate("MainWindow", "\346\217\220\347\244\272\344\277\241\346\201\257", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
