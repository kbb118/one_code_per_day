#-------------------------------------------------
#
# Project created by QtCreator 2016-03-13T15:23:39
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++14 debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ch01-todo
TEMPLATE = app

SOURCES += main.cpp\
    MainWindow.cpp \
    SubWindow.cpp \
    CheckGroup.cpp \
    Task.cpp

HEADERS  += MainWindow.h \
    SubWindow.h \
    CheckGroup.h \
    Task.h

FORMS    += MainWindow.ui \
    Task.ui
