TEMPLATE = subdirs
SUBDIRS = sub_src sub_examples sub_facebookauth sub_dissent

sub_src.subdir = src
sub_dissent.subdir=dissent
sub_facebookauth.subdir=facebookauth
sub_examples.subdir = examples
sub_examples.depends = sub_src
sub_examples.depends =sub_facebookauth
sub_facebookauth.depends = sub_dissent

macx: LIBS += -L$$PWD/../../qjson/lib/ -lqjson

INCLUDEPATH += $$PWD/../../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qjson
DEPENDPATH += $$PWD/../../../QtSDK/Madde/sysroots/harmattan_sysroot_10.2011.34-1_slim/usr/include/qjson







