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
           wrapper.cpp \
    startwindow.cpp

HEADERS += mainwindow.h \
           statistic.h \
           wrapper.h \
    startwindow.h


QMAKE_LFLAGS += -s
QMAKE_LFLAGS_RELEASE += -static-libgcc

RESOURCES += \
    fonts.qrc
