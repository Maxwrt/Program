/********************************************************************************
** Form generated from reading UI file 'picture.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTURE_H
#define UI_PICTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Picture
{
public:
    QGridLayout *gridLayout;

    void setupUi(QDialog *Picture)
    {
        if (Picture->objectName().isEmpty())
            Picture->setObjectName(QStringLiteral("Picture"));
        Picture->resize(629, 571);
        Picture->setFocusPolicy(Qt::StrongFocus);
        Picture->setModal(true);
        gridLayout = new QGridLayout(Picture);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        retranslateUi(Picture);

        QMetaObject::connectSlotsByName(Picture);
    } // setupUi

    void retranslateUi(QDialog *Picture)
    {
        Picture->setWindowTitle(QApplication::translate("Picture", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Picture: public Ui_Picture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTURE_H
