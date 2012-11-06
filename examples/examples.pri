win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../qfacebook-build-desktop-Desktop_Qt_4_8_1_for_GCC__Qt_SDK__Debug/lib/release/ -lqfacebook
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../qfacebook-build-desktop-Desktop_Qt_4_8_1_for_GCC__Qt_SDK__Debug/lib/debug/ -lqfacebook
else:symbian: LIBS += -lqfacebook
else:unix: LIBS += -L$$PWD/../../qfacebook-build-desktop-Desktop_Qt_4_8_1_for_GCC__Qt_SDK__Debug/lib/ -lqfacebook

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src




