#-------------------------------------------------
#
# Project created by QtCreator 2018-01-25T18:50:39
#
#-------------------------------------------------

QT       += core gui \
          sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graduationwork02
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    sign.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    login.h \
    sign.h \
    game.h

FORMS    += mainwindow.ui \
    login.ui \
    sign.ui \
    game.ui

RESOURCES += \
    image.qrc

DISTFILES +=
