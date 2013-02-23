#-------------------------------------------------
#
# Project created by QtCreator 2012-04-15T23:08:02
#
# 2012-04-16 PhA - Ajout du module sql
#-------------------------------------------------

QT       += core gui sql network

TARGET = SuPer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fident.cpp \
    cbdd.cpp \
    cihmpersonne.cpp \
    cihmcamera.cpp \
    cihmlecteur.cpp \
    cihmbadge.cpp \
    cmsg.cpp \
    cthreadclient.cpp \
    cihmaffecter.cpp \
    cihmparametrer.cpp

HEADERS  += mainwindow.h \
    fident.h \
    cbdd.h \
    cihmpersonne.h \
    cihmcamera.h \
    cihmlecteur.h \
    cihmbadge.h \
    commun.h \
    cmsg.h \
    cthreadclient.h \
    cihmaffecter.h \
    cihmparametrer.h

FORMS    += mainwindow.ui \
    fident.ui \
    cihmpersonne.ui \
    cihmcamera.ui \
    cihmlecteur.ui \
    cihmbadge.ui \
    cihmaffecter.ui \
    cihmparametrer.ui

RESOURCES +=

OTHER_FILES += \
    entree_antisouffle.bmp \
    capsule.bmp \
    partie_haute.bmp \
    conciergerie.bmp \
    servitudes_generales.bmp \
    world1.gif \
    alert.black.gif \
    ball.red.png

































































