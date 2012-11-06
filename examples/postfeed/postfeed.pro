#-------------------------------------------------
#
# Project created by QtCreator 2010-11-17T12:16:44
#
#-------------------------------------------------

include(../examples.pri)

QT       += core network gui

TARGET = postfeed
TEMPLATE = app


SOURCES += main.cpp\
        postfeed.cpp \
    putobject.cpp

HEADERS  += postfeed.h \
    putobject.h

FORMS    += postfeed.ui
