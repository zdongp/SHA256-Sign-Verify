#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T15:43:10
#
#-------------------------------------------------

QT       -= gui

TARGET = FlyTest
TEMPLATE = lib
DESTDIR =$$PWD/../out/$$TARGET

DEFINES += LINUX_QT


SOURCES = FlyTest.cpp

INCLUDEPATH += $$PWD/../include 

SOURCES += $$PWD/../include/commonFunc.c

LIBS += -ldl


unix {
    target.path = /usr/lib
    INSTALLS += target
}


