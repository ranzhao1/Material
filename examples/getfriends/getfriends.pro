#-------------------------------------------------
#
# Project created by QtCreator 2010-11-17T12:16:44
#
#-------------------------------------------------

include(../examples.pri)

QT       += core network gui

TARGET = getfriends
TEMPLATE = app


SOURCES += main.cpp\
        getfriends.cpp \
    getconnection.cpp

HEADERS  += getfriends.h \
    getconnection.h

FORMS    += getfriends.ui
