#-------------------------------------------------
#
# Project created by QtCreator 2020-06-15T09:24:18
#
#-------------------------------------------------

QT += core gui sql

CONFIG += qt thread
CONFIG(debug, debug|release) {
    DIRNAME=wrtdebug
    message("wrtdebug")
} else {
    DIRNAME=wrtrelease
    message("wrtrelease")
}
DESTDIR = $$PWD/$${DIRNAME}/
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = ApartmentInfoSys
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    util.cpp \
    base.cpp

HEADERS  += mainwindow.h \
    util.h \
    base.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
