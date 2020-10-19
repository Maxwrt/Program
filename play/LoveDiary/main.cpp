#include "mainwindow.h"
#include "qdialoglogin.h"
#include "common.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRect rect = a.desktop()->availableGeometry();
    QSize size = rect.size();

    SetAppLogName("LoveDiary");
    qInstallMessageHandler(AppLog);


    QTranslator translator(&a);
    translator.load(":/LoveDiary_zh.qm");
    a.installTranslator(&translator);

    QFont font = a.font();
    font.setPointSize(12);
    font.setStyleStrategy(QFont::NoAntialias);
    a.setFont(font);

    QDialogLogin* login = new QDialogLogin();
    if(login->exec() == QDialog::Accepted)
    {
        MainWindow w(login->m_loginUserHash);
        w.resize(size.width() - size.width()/4, size.height() - size.height()/4);
        w.move((size.width()- w.width())/2, (size.height() - w.height())/2);
        w.show();
        if(login)
        {
            login->deleteLater();
            login = nullptr;
        }
        return a.exec();
    }

    if(login)
    {
        login->deleteLater();
        login = nullptr;
    }
    return a.exit();
}
