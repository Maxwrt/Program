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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actInsert;
    QAction *actAppend;
    QAction *actDelete;
    QAction *actExport;
    QAction *actClose;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QTreeWidget *treeWidget;
    QWidget *tab_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QPushButton *btnSearch;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnEditUsers;
    QPushButton *btnExport;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QTabWidget *tabWidget_2;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QTableView *tableView_2;
    QLabel *labelTipInfo_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelTipInfo;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1717, 957);
        actInsert = new QAction(MainWindow);
        actInsert->setObjectName(QStringLiteral("actInsert"));
        actAppend = new QAction(MainWindow);
        actAppend->setObjectName(QStringLiteral("actAppend"));
        actDelete = new QAction(MainWindow);
        actDelete->setObjectName(QStringLiteral("actDelete"));
        actExport = new QAction(MainWindow);
        actExport->setObjectName(QStringLiteral("actExport"));
        actClose = new QAction(MainWindow);
        actClose->setObjectName(QStringLiteral("actClose"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::West);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        treeWidget = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout_3->addWidget(treeWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());
        splitter->addWidget(tabWidget);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(200, 25));
        comboBox->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(150, 25));
        lineEdit->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(lineEdit);

        btnSearch = new QPushButton(groupBox);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        btnSearch->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(btnSearch);

        horizontalSpacer = new QSpacerItem(377, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnEditUsers = new QPushButton(groupBox);
        btnEditUsers->setObjectName(QStringLiteral("btnEditUsers"));
        btnEditUsers->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(btnEditUsers);

        btnExport = new QPushButton(groupBox);
        btnExport->setObjectName(QStringLiteral("btnExport"));
        btnExport->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(btnExport);

        btnAdd = new QPushButton(groupBox);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(btnAdd);

        btnDelete = new QPushButton(groupBox);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(btnDelete);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 3);

        tabWidget_2 = new QTabWidget(groupBox);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setTabPosition(QTabWidget::South);
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout = new QGridLayout(tab_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(tab_2);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->horizontalHeader()->setHighlightSections(false);

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        tabWidget_2->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tableView_2 = new QTableView(tab_3);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->horizontalHeader()->setHighlightSections(false);

        gridLayout_4->addWidget(tableView_2, 0, 0, 1, 1);

        tabWidget_2->addTab(tab_3, QString());

        gridLayout_5->addWidget(tabWidget_2, 1, 0, 1, 3);

        labelTipInfo_2 = new QLabel(groupBox);
        labelTipInfo_2->setObjectName(QStringLiteral("labelTipInfo_2"));
        labelTipInfo_2->setMinimumSize(QSize(400, 0));

        gridLayout_5->addWidget(labelTipInfo_2, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(763, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 2, 1, 1, 1);

        labelTipInfo = new QLabel(groupBox);
        labelTipInfo->setObjectName(QStringLiteral("labelTipInfo"));
        labelTipInfo->setMinimumSize(QSize(200, 0));

        gridLayout_5->addWidget(labelTipInfo, 2, 2, 1, 1);

        splitter->addWidget(groupBox);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1717, 26));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\212\261\346\265\213\345\256\242\346\210\267\347\256\241\347\220\206\347\263\273\347\273\237", 0));
        actInsert->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240", 0));
#ifndef QT_NO_TOOLTIP
        actInsert->setToolTip(QApplication::translate("MainWindow", "\346\217\222\345\205\245\344\270\200\350\241\214", 0));
#endif // QT_NO_TOOLTIP
        actInsert->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", 0));
        actAppend->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240", 0));
#ifndef QT_NO_TOOLTIP
        actAppend->setToolTip(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\270\200\346\235\241\346\225\260\346\215\256", 0));
#endif // QT_NO_TOOLTIP
        actAppend->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
        actDelete->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", 0));
#ifndef QT_NO_TOOLTIP
        actDelete->setToolTip(QApplication::translate("MainWindow", "\345\210\240\351\231\244\351\200\211\344\270\255\347\232\204\346\225\260\346\215\256", 0));
#endif // QT_NO_TOOLTIP
        actDelete->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        actExport->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272", 0));
#ifndef QT_NO_TOOLTIP
        actExport->setToolTip(QApplication::translate("MainWindow", "\345\257\274\345\207\272\350\241\250\346\240\274\346\225\260\346\215\256\345\210\260\346\226\207\346\234\254\344\270\255", 0));
#endif // QT_NO_TOOLTIP
        actExport->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0));
        actClose->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
#ifndef QT_NO_TOOLTIP
        actClose->setToolTip(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237", 0));
#endif // QT_NO_TOOLTIP
        actClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\345\234\260\345\214\272", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "\344\272\214\346\254\241", 0));
        groupBox->setTitle(QString());
        label_5->setText(QApplication::translate("MainWindow", "filter\357\274\232", 0));
        label_4->setText(QApplication::translate("MainWindow", "key\357\274\232", 0));
        btnSearch->setText(QApplication::translate("MainWindow", "search", 0));
        btnEditUsers->setText(QApplication::translate("MainWindow", "edituser", 0));
        btnExport->setText(QApplication::translate("MainWindow", "export", 0));
        btnAdd->setText(QApplication::translate("MainWindow", "add", 0));
        btnDelete->setText(QApplication::translate("MainWindow", "del", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QApplication::translate("MainWindow", "\345\256\242\346\210\267\346\225\260\346\215\256", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("MainWindow", "\344\272\214\346\254\241\350\256\276\345\244\207\350\241\250", 0));
        labelTipInfo_2->setText(QString());
        labelTipInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
