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

DEFINES+=CGAL_DISABLE_ROUNDING_MATH_CHECK=ON

unix:!macx {
    QMAKE_CXXFLAGS += -frounding-math
    LIBS += -lboost_system -lboost_thread -lgmp
    LIBS += -lCGAL -lCGAL_Core -lCGAL_ImageIO
    target.path = /usr/lib
    INSTALLS += target
}

macx {
    LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lCGAL
    LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lCGAL_Core
    LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lCGAL_ImageIO

    INCLUDEPATH += /usr/local/include

    LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/ -lboost_thread-mt
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include

    LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/ -lboost_system-mt
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include

    LIBS += -L$$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/lib/ -lgmp.10
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/include

    LIBS += -L$$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/lib/ -lmpfr
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/include
}

HEADERS +=  \
    Minima/minmaxcalculator.h \
    basecalculator.h \
    Events/bendeventcalculator.h \
    Events/pathandboundaryeventcalculator.h \
    Models/eventsegment.h \
    Models/lineofsight.h \
    Models/minimum.h \
    Models/pointonshortestpath.h \
    Models/pointonshortestpathtree.h \
    Models/sweptsegment.h \
    ShortestPath/shortestpathtreecalculator.h \
    ShortestPath/shortestpathcalculator.h \
    Models/faceonshortestpath.h \
    Utils/geometryutil.h \
    Minima/minsumcalculator.h \
    ShortestPath/faceinfo.h \
    ShortestPath/triangulation.h

SOURCES += \
    Events/bendeventcalculator.cpp \
    Events/pathandboundaryeventcalculator.cpp \
    Minima/minmaxcalculator.cpp \
    Minima/minsumcalculator.cpp \
    Models/eventsegment.cpp \
    Models/lineofsight.cpp \
    Models/minimum.cpp \
    Models/pointonshortestpath.cpp \
    Models/pointonshortestpathtree.cpp \
    Models/sweptsegment.cpp \
    ShortestPath/shortestpathtreecalculator.cpp \
    ShortestPath/faceinfo.cpp \
    ShortestPath/shortestpathcalculator.cpp \
    ShortestPath/triangulation.cpp \
    Utils/geometryutil.cpp \
    basecalculator.cpp
