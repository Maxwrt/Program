#include "mainwindow.h"
#include "qdialoglogin.h"
#include "common.h"
#include <QApplication>
#include <QTranslator>
#include <QFont>
#include <QDebug>
#include <QDesktopWidget>
#include <QDir>
#include <QMetaObject>
#include <QMetaProperty>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetAppLogName("CRM");
    qInstallMessageHandler(AppLog);

    QTranslator translator(&a);
    translator.load(":/CRM_zh.qm");
    a.installTranslator(&translator);

    QFont font = a.font();
    font.setPointSize(12);
    font.setStyleStrategy(QFont::NoAntialias);
    a.setFont(font);

    QDialogLogin* login = new QDialogLogin();
    if(login->exec() == QDialog::Accepted)
    {
        MainWindow w(login->m_loginUserHash);
        w.move((a.desktop()->width()-w.width())/2, (a.desktop()->height()-w.height())/2);
        w.ShowWindow();

        if(login)
        {
            login->deleteLater();
            login = nullptr;
        }
        return a.exec();
    }

#if 0
    const QMetaObject* metaobject = login->metaObject();
    int count = metaobject->propertyCount();
    for (int i=0; i<count; i++)
    {
        QMetaProperty metaproperty = metaobject->property(i);
        const char* name = metaproperty.name();
        QVariant value = login->property(name);
        qDebug() << name << " "<<value;
    }
#endif
    if(login)
    {
        login->deleteLater();
        login = nullptr;
    }

    return a.exit();
}
