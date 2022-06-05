#-------------------------------------------------
#
# Project created by QtCreator 2019-05-17T18:23:18
#
#-------------------------------------------------

QT += core gui
QT += widgets svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Painting
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
        components/arrowitem.cpp \
        components/circleitem.cpp \
        components/componentfactory.cpp \
        components/elements/graphnode.cpp \
        components/elements/polylineitem.cpp \
        components/elements/svgitem.cpp \
        components/elements/twogtext.cpp \
        components/grawitem.cpp \
        components/lineitem.cpp \
        components/rectangleitem.cpp \
        components/rectangletextitem.cpp \
        giproperty.cpp \
        main.cpp \
        mainwindow.cpp \
        mygraphicsscene.cpp \
        mygraphicsview.cpp

HEADERS += \
        components/arrowitem.h \
        components/circleitem.h \
        components/componentfactory.h \
        components/componenttype.h \
        components/elements/graphnode.h \
        components/elements/polylineitem.h \
        components/elements/svgitem.h \
        components/elements/twogtext.h \
        components/grawitem.h \
        components/lineitem.h \
        components/rectangleitem.h \
        components/rectangletextitem.h \
        components/svgitem.h \
        giproperty.h \
        mainwindow.h \
        mygraphicsscene.h \
        mygraphicsview.h \
        scenestates.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    draw_rect.qrc
