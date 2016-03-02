#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T17:45:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFSstat
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           statistic.cpp \
           wrapper.cpp

HEADERS += mainwindow.h \
           statistic.h \
           wrapper.h


QMAKE_LFLAGS += -s
QMAKE_LFLAGS_RELEASE += -static -static-libgcc

RESOURCES += \
    fonts.qrc \
    images.qrc
