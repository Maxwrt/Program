QT += core widgets network

CONFIG += c++11

TARGET = Sender
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Sender.cpp

HEADERS += \
    Sender.h

RESOURCES += \
    resource.qrc
