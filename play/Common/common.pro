#-------------------------------------------------
#
# Project created by QtCreator 2020-07-24T14:24:32
#
#-------------------------------------------------
QT       += gui core network sql

TEMPLATE = lib

CONFIG(debug, debug|release){
    TARGET = commond
} else {
    TARGET = common
}

DEFINES += COMMON_LIBRARY
DEFINES += QT_USE_FAST_OPERATOR_PLUS
include(../play.pri)

OBJECTS_DIR = $$PWD/../.object/common
MOC_DIR = $$PWD/../.object/common
RCC_DIR = $$PWD/../.object/common

SOURCES += common.cpp

HEADERS += common.h\
        common_global.h

unix {
    target.path = /home/wrt/lib
    INSTALLS += target
}
