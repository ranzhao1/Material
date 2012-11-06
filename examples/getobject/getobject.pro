#-------------------------------------------------
#
# Project created by QtCreator 2010-06-21T16:45:56
#
#-------------------------------------------------

include(../examples.pri)

QT       += core network
QT       -= gui

TARGET = getobject
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    getobject.cpp

HEADERS += \
    getobject.h
