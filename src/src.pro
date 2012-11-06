QT -= gui
QT += network

TARGET = qfacebook
TEMPLATE = lib
DESTDIR  = ../lib

DEFINES += QFACEBOOK_LIBRARY

macx: LIBS += -L$$PWD/../../qjson/lib/ -lqjson

INCLUDEPATH += $$PWD/../../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qjson
DEPENDPATH += $$PWD/../../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qjson

SOURCES += \
    qfacebook.cpp \
    graphapi.cpp \
    qfacebookreply.cpp

HEADERS += \
    qfacebook.h \
    qfacebook_global.h \
    graphapi.h \
    qfacebookreply.h


headers.files = qfacebook.h qfacebookreply.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE106BC58
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = qfacebook.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target headers
}


