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
    $$PWD/fileupdater.h \
    $$PWD/mimeutils.h \
    $$PWD/qfmwidget.h \

SOURCES += \
    $$PWD/fileupdater.cpp \
    $$PWD/main.cpp \
    $$PWD/mimeutils.cpp \
    $$PWD/qfmwidget.cpp

RESOURCES += \
    res.qrc

