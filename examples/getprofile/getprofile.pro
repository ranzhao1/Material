#-------------------------------------------------
#
# Project created by QtCreator 2010-11-29T16:45:02
#
#-------------------------------------------------

include(../examples.pri)

QT       += core network gui

TARGET = getprofile
TEMPLATE = app

SOURCES += main.cpp\
        getprofile.cpp \
    userprofile.cpp

HEADERS  += getprofile.h \
    userprofile.h

FORMS    += getprofile.ui
