#-------------------------------------------------
#
# Project created by QtCreator 2016-01-03T12:01:45
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = lab4_labyrinth
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11
TEMPLATE = app

LIBS += -lglut -lGLEW -lGL -lGLU -lSDL2 -lSDL


SOURCES += main.cpp \
    labyrinth.cpp

HEADERS += \
    labyrinth.h \
    input.h
