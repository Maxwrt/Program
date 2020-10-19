#-------------------------------------------------
#
# Project created by QtCreator 2020-09-29T10:24:43
#
#-------------------------------------------------
include(../play.pri)

QT       +=  gui sql

DEFINES += QT_USE_FAST_OPERATOR_PLUS

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoveDiary
TEMPLATE = app

INCLUDEPATH += $$PWD/../Common/
SOURCES += main.cpp\
        mainwindow.cpp \
        qdialoglogin.cpp \
        luatextedit.cpp \
        mytextedit.cpp \
        agreementdialog.cpp \
    imageshow.cpp

HEADERS  += mainwindow.h \
            qdialoglogin.h \
            luatextedit.h \
            mytextedit.h \
            agreementdialog.h \
    imageshow.h

FORMS    += mainwindow.ui \
            qdialoglogin.ui \
            agreementdialog.ui
