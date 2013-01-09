TEMPLATE = app
TARGET = tst_xrdproperty

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_xrdproperty.h
SOURCES += tst_xrdproperty.cpp
