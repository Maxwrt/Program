#-------------------------------------------------
#
# Project created by QtCreator 2017-06-18T13:36:28
#
#-------------------------------------------------
QT += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CRM
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_USE_FAST_OPERATOR_PLUS

include(../play.pri)

INCLUDEPATH += $$PWD/../Common/

CONFIG(debug, debug|release){
    LIBS += -L$$PWD/../bin/debug/ -lcommond
}else{
    LIBS += -L$$PWD/../bin/release/ -lcommon
}

OBJECTS_DIR = $$PWD/../.object/crm
MOC_DIR = $$PWD/../.object/crm
RCC_DIR = $$PWD/../.object/crm

SOURCES += main.cpp\
           mainwindow.cpp \
           dlgitem.cpp \
           basefunction.cpp \
           qdialoglogin.cpp \
           dialoguser.cpp \
           json.cpp

HEADERS += mainwindow.h \
           dlgitem.h \
           basefunction.h \
           qdialoglogin.h \
           dialoguser.h \
           json.h

FORMS += mainwindow.ui \
         dlgitem.ui \
         qdialoglogin.ui \
         dialoguser.ui

RESOURCES += rc.qrc

TRANSLATIONS += CRM_zh.ts


DISTFILES += crm.rc \
             tool.ico

RC_FILE = crm.rc
