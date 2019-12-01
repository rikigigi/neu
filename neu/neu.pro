#-------------------------------------------------
#
# Project created by QtCreator 2014-11-21T17:05:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = neu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    neur.h

FORMS    += mainwindow.ui
LIBS    += -lm
CONFIG += debug_and_release
#-----------------------------------------------------
# !!!impostare questo in base al proprio processore!!!
#-----------------------------------------------------
QMAKE_CXXFLAGS += -march=native
