#-------------------------------------------------
#
# Project created by QtCreator 2020-09-29T10:24:43
#
#-------------------------------------------------

QT       +=  gui sql network gui-private

DEFINES += QT_USE_FAST_OPERATOR_PLUS

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoveDiary
TEMPLATE = app

include(../play.pri)

CONFIG(debug, debug|release){
    LIBS += -L$$PWD/../bin/debug/ -lcommond -lQXlsx
}else{
    LIBS += -L$$PWD/../bin/release/ -lcommon
}


OBJECTS_DIR = $$PWD/../.object/LoveDiary
MOC_DIR = $$PWD/../.object/LoveDiary
RCC_DIR = $$PWD/../.object/LoveDiary

INCLUDEPATH += $$PWD/../Common/
SOURCES += main.cpp\
        mainwindow.cpp \
        qdialoglogin.cpp \
        luatextedit.cpp \
        mytextedit.cpp \
        agreementdialog.cpp \
        imageshow.cpp \
    dialoguser.cpp \
    verificationcodelabel.cpp \
    registdialog.cpp \
    picture.cpp \
    forgetpassword.cpp \
    basedialog.cpp \
    Sender.cpp \
    Receiver.cpp

HEADERS  += mainwindow.h \
            qdialoglogin.h \
            luatextedit.h \
            mytextedit.h \
            agreementdialog.h \
            imageshow.h \
    dialoguser.h \
    verificationcodelabel.h \
    registdialog.h \
    picture.h \
    forgetpassword.h \
    basedialog.h \
    Sender.h \
    Receiver.h

FORMS    += mainwindow.ui \
            qdialoglogin.ui \
            agreementdialog.ui \
    dialoguser.ui \
    registdialog.ui \
    picture.ui \
    forgetpassword.ui \
    Sender.ui \
    Receiver.ui

TRANSLATIONS = LoveDiary_en.ts \
               LoveDiary_zh.ts

DISTFILES += \
            tool.rc \
            tool.ico

RC_FILE = tool.rc

RESOURCES += \
    resource.qrc
