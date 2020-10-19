QT += gui core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt
TEMPLATE = lib

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../bin/debug/
} else {
    DESTDIR = $$PWD/../bin/release/
}

HEADERS += \
    customwidgets.h \
    form.h

SOURCES += \
    customwidgets.cpp \
    form.cpp

FORMS += \
    form.ui
