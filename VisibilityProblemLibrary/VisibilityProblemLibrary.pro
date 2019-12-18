#-------------------------------------------------
#
# Project created by QtCreator 2019-11-28T06:54:07
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

TARGET = VisibilityProblemLibrary
TEMPLATE = lib
CONFIG += staticlib
CONFIG += create_prl

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    Events/pathandboundaryeventcalculator.cpp \
    Models/pointonshortestpathtree.cpp \
    Models/pointwithtriangulationinfo.cpp \
    ShortestPath/shortestpathtreecalculator.cpp \
    spvshortestpath.cpp \
    spvfaceinfo.cpp \
    ShortestPath/shortestpathcalculator.cpp

HEADERS +=  \
    Events/baseeventcalculator.h \
    Events/bendeventcalculator.h \
    Events/pathandboundaryeventcalculator.h \
    Models/eventsegment.h \
    Models/lineofsight.h \
    Models/pointonshortestpath.h \
    Models/pointonshortestpathtree.h \
    Models/pointwithtriangulationinfo.h \
    Models/sweptsegment.h \
    ShortestPath/shortestpathtreecalculator.h \
    spvshortestpath.h \
    spvfaceinfo.h \
    spveventintersection.h \
    spvboundaryevents.h \
    ShortestPath/shortestpathcalculator.h \
    Models/faceonshortestpath.h \
    Utils/geometryutil.h


macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lCGAL

macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lCGAL_Core

macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lCGAL_ImageIO

macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lCGAL_Qt5

INCLUDEPATH += /usr/local/include
DEPENDPATH += /local/include

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/ -lboost_thread-mt

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include


macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/ -lboost_system-mt

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/lib/ -lgmp.10

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/include

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/lib/ -lmpfr

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/include
