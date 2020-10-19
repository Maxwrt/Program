#-------------------------------------------------
#
# Project created by QtCreator 2020-08-27T09:26:58
#
#-------------------------------------------------

QT       += core gui gui-private

#CONFIG += console
CONFIG -= app_bundle
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = frmCountCode
TEMPLATE = app

#�˺궨��֧��%���������ַ���
DEFINES += QT_USE_FAST_OPERATOR_PLUS

include(../play.pri)

CONFIG(debug, debug|release){
    LIBS += -L$$PWD/../lib/debug/ -lcommond -lQXlsx
}else{
    LIBS += -L$$PWD/../lib/release/ -lcommon
}

OBJECTS_DIR = $$PWD/../.object/frmCountCode
MOC_DIR = $$PWD/../.object/frmCountCode
RCC_DIR = $$PWD/../.object/frmCountCode

INCLUDEPATH += $$PWD/../QXlsx/header/
INCLUDEPATH += $$PWD/../Common/
SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES += \
    image.qrc

#QtĬ�ϲ�֧�ִ���Դ�ļ������������ļ�
CONFIG += resources_big
