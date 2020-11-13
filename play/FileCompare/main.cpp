#include "mainwindow.h"
#include "common.h"
#include <QApplication>
#include <QTranslator>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QStringBuilder>
#include <QPointer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetAppLogName(QStringLiteral("filecompare"));
    qInstallMessageHandler(AppLog);

    QFont font = a.font();
    font.setPointSize(10);
    font.setStyleStrategy(QFont::NoAntialias);
    a.setFont(font);
    QPointer<QTranslator> translator=NULL;
    translator = QPointer<QTranslator>(new QTranslator(&a));
    translator->load(QStringLiteral(":/FileCompare_zh.qm"));
    a.installTranslator(translator);

    MainWindow w;
    w.showNormal();

    return a.exec();
}
