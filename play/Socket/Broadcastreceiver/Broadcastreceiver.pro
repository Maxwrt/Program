QT += core widgets network
QT -= gui

CONFIG += c++11

TARGET = Broadcastreceiver
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    broadcastreceiver.cpp

HEADERS += \
    broadcastreceiver.h
