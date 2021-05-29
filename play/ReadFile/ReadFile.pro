QT += core sql network
QT -= gui

CONFIG += c++11

DEFINES += QT_USE_FAST_OPERATOR_PLUS
TARGET = ReadFile
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test.cpp

include(../play.pri)
INCLUDEPATH += $$PWD/../Common/
CONFIG(debug, debug|release){
    #LIBS += -L$$PWD/../bin/debug/ -lcommond
}else{
    #LIBS += -L$$PWD/../bin/release/ -lcommon
}
OBJECTS_DIR = $$PWD/../.object/ReadFile
MOC_DIR = $$PWD/../.object/ReadFile
RCC_DIR = $$PWD/../.object/ReadFile
