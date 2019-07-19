#-------------------------------------------------
#
# Project created by QtCreator 2017-06-29T16:20:46
#
#-------------------------------------------------

QT  += quickwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qfm
TEMPLATE = app

INCLUDEPATH +=$$PWD main

HEADERS += \
    $$PWD/common.h \
    $$PWD/desktopfile.h \
    $$PWD/fileupdater.h \
    $$PWD/fileutils.h \
    $$PWD/mimeutils.h \
    $$PWD/properties.h \
    $$PWD/qfmwidget.h \

SOURCES += \
    $$PWD/common.cpp \
    $$PWD/desktopfile.cpp \
    $$PWD/fileupdater.cpp \
    $$PWD/fileutils.cpp \
    $$PWD/main.cpp \
    $$PWD/mimeutils.cpp \
    $$PWD/properties.cpp \
    $$PWD/qfmwidget.cpp

RESOURCES += \
    res.qrc

