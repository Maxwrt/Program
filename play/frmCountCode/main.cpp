#include "widget.h"
#include "common.h"
#include <QApplication>

__declspec(dllimport) void AppLog(QtMsgType type, const QMessageLogContext & context, const QString &msg);
__declspec(dllimport) void SetAppLogName(const QString &appname);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetAppLogName(QStringLiteral("frmCountCode"));
    qInstallMessageHandler(AppLog);
    Widget w;
    w.ShowWidget();

    return a.exec();
}
