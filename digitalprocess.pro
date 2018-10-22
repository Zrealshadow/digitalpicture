#-------------------------------------------------
#
# Project created by QtCreator 2018-09-25T21:29:13
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = digitalprocess
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

CONFIG += c++11

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    function.cpp \
    qcustomplot.cpp \
    histogram.cpp \
    hist_func.cpp \
    spacemove.cpp \
    spacezoom.cpp \
    sp_func.cpp \
    spacerotate.cpp \
    spacesmooth.cpp \
    fig_show.cpp \
    spacesharpen.cpp

HEADERS += \
        mainwindow.h \
    function.h \
    function.h \
    qcustomplot.h \
    qcustomplot.h \
    histogram.h \
    hist_func.h \
    spacemove.h \
    spacezoom.h \
    sp_func.h \
    spacerotate.h \
    spacesmooth.h \
    fig_show.h \
    spacesharpen.h

FORMS += \
        mainwindow.ui \
    histogram.ui \
    spacemove.ui \
    spacezoom.ui \
    spacerotate.ui \
    spacesmooth.ui \
    fig_show.ui \
    spacesharpen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
