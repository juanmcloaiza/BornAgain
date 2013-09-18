TEMPLATE = app
CONFIG  += console
CONFIG  -= qt app_bundle
QT      -= core gui

include($$PWD/../../../../shared.pri)
DEFINES += STANDALONE

INCLUDEPATH *= $$EIGEN_INCLUDE_DIR
INCLUDEPATH *= $$BOOST_INCLUDE_DIR
INCLUDEPATH += $$BornAgainCore_INCLUDE_DIR $$BornAgainFit_INCLUDE_DIR
LIBS += $$BOOST_LIBRARY $$BornAgainCore_LIBRARY  $$BornAgainFit_LIBRARY

SOURCES += TestFit02.cpp SampleBuilder.cpp
HEADERS += TestFit02.h SampleBuilder.h

