#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T10:12:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testwidget
TEMPLATE = app


SOURCES += main.cpp\
    shape.cpp \
    mainwindow.cpp \
    widget.cpp \
    line.cpp \
    Rect.cpp \
    Ellipse.cpp \
    polygon.cpp

HEADERS  += widget.h \
    shape.h \
    mainwindow.h \
    line.h \
    Rect.h \
    Ellipse.h \
    polygon.h
