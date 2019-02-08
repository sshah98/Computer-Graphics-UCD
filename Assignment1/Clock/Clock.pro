QT += core
QT -= gui

TARGET = Clock
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    clock.cpp \
    normal.cpp \
    alarm.cpp \
    timer.cpp

HEADERS += \
    clock.h \
    normal.h \
    alarm.h \
    timer.h

