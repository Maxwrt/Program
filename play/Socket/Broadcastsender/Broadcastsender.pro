QT += core network widgets
QT -= gui

CONFIG += c++11

TARGET = Broadcastsender
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    broadcastsender.cpp

HEADERS += \
    broadcastsender.h
