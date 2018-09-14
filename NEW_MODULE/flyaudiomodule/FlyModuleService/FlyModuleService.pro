#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T15:43:10
#
#-------------------------------------------------

QT       -= gui

TARGET = FlyModuleService
TEMPLATE = app
DESTDIR =$$PWD/../out/$$TARGET

DEFINES += LINUX_QT

SOURCES = FlyModuleService.cpp \
            $$PWD/Tinyxml/tinyxml.cpp \
            $$PWD/Tinyxml/tinyxmlparser.cpp \
            $$PWD/Tinyxml/tinyxmlerror.cpp \
            $$PWD/Tinyxml/tinystr.cpp


INCLUDEPATH += $$PWD/../include \
                $$PWD/Tinyxml

SOURCES += $$PWD/../include/moduleCommApi.c \
            $$PWD/../include/commonFunc.c


LIBS += -ldl


unix {
    target.path = /usr/lib
    INSTALLS += target
}


