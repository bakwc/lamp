TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    network.cpp \
    lamp.cpp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    exception.h \
    network.h \
    lamp.h
