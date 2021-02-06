QT += core sql
QT -= gui

CONFIG += c++11

TARGET = AddComment
CONFIG += console
CONFIG -= app_bundle

include(../play.pri)

INCLUDEPATH += $$PWD/../Common/ \
               $$PWD/lua/

CONFIG(debug, debug|release){
    LIBS += -L$$PWD/../bin/debug/ -lcommond
}else{
    LIBS += -L$$PWD/../bin/release/ -lcommon
}

OBJECTS_DIR = $$PWD/../.object/crm
MOC_DIR = $$PWD/../.object/crm
RCC_DIR = $$PWD/../.object/crm

TEMPLATE = app

SOURCES += main.cpp \
    addcomment.cpp


HEADERS += \
    addcomment.h

