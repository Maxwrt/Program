QT += core widgets network
QT -= gui

CONFIG += c++11

TARGET = Receiver
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Receiver.cpp

HEADERS += \
    Receiver.h
