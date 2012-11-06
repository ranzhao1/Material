#-------------------------------------------------
#
# Project created by QtCreator 2010-06-21T16:45:56
#
#-------------------------------------------------

include(../examples.pri)

QT       += core network webkit xml
QT       -= gui

TARGET = getconnection
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    getconnection.cpp

HEADERS += \
    getconnection.h
