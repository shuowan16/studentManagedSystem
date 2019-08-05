#-------------------------------------------------
#
# Project created by QtCreator 2019-07-28T09:32:24
#
#-------------------------------------------------

QT       += core gui texttospeech network
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = gradeManagedSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 gif

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    welcomewindow.cpp \
    searchinfostudent.cpp \
    addlessonswindow.cpp \
    searchinfolessons.cpp \
    searchinfoteacher.cpp \
    voice_operation.cpp \
    searchinfodeparts.cpp

HEADERS += \
        mainwindow.h \
    welcomewindow.h \
    public_fuctions.h \
    searchinfostudent.h \
    addlessonswindow.h \
    searchinfolessons.h \
    searchinfoteacher.h \
    voice_operation.h \
    searchinfodeparts.h

FORMS += \
        mainwindow.ui \
    welcomewindow.ui \
    searchinfostudent.ui \
    addlessonswindow.ui \
    searchinfolessons.ui \
    searchinfoteacher.ui \
    searchinfodeparts.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
