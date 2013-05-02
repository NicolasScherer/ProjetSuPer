#-------------------------------------------------
#
# Project created by QtCreator 2013-05-02T16:39:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuPer_SCHERER_backend
TEMPLATE = app


SOURCES += main.cpp\
        configurer.cpp \
    bdd.cpp

HEADERS  += configurer.h \
    bdd.h

FORMS    += configurer.ui
