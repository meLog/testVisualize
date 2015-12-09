QT += core
QT -= gui

TARGET = testVisualizer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    applicationdata.cpp \
    visualize.cpp \
    chartdata.cpp


HEADERS += \
    applicationdata.h \
    visualize.h \
    chartdata.h

