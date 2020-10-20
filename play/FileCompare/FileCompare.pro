#-------------------------------------------------
#
# Project created by QtCreator 2020-06-28T10:26:01
#
#-------------------------------------------------

QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tool
TEMPLATE = app

include(../play.pri)

DEFINES += QT_USE_FAST_OPERATOR_PLUS


CONFIG(debug, debug|release){
    LIBS += -L$$PWD/../bin/debug/ -lcommond
}else{
    LIBS += -L$$PWD/../bin/release/ -lcommon
}

INCLUDEPATH += $$PWD/../Common/

OBJECTS_DIR = $$PWD/../.object/filecompare
MOC_DIR = $$PWD/../.object/filecompare
RCC_DIR = $$PWD/../.object/filecompare



SOURCES += main.cpp\
           mainwindow.cpp \
           comparethread.cpp \
           thread.cpp \
           boolresult.cpp \
           compare.cpp

HEADERS  += mainwindow.h \
            comparethread.h \
            thread.h \
            boolresult.h \
            compare.h

FORMS    += mainwindow.ui

RESOURCES += \
            resource.qrc

TRANSLATIONS = FileCompare_en.ts \
               FileCompare_zh.ts

DISTFILES += \
            tool.rc \
            tool.ico \
            json.js

RC_FILE = tool.rc


