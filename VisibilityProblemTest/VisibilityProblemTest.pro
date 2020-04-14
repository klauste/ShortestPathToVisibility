QT += testlib
QT -= gui

DEFINES+=CGAL_DISABLE_ROUNDING_MATH_CHECK=ON

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TARGET = VisibilityProblemTest
TEMPLATE = app

LIBS += -L$$OUT_PWD/../VisibilityProblemLibrary/ -lVisibilityProblemLibrary

INCLUDEPATH += $$PWD/../VisibilityProblemLibrary
DEPENDPATH += $$PWD/../VisibilityProblemLibrary

PRE_TARGETDEPS += $$OUT_PWD/../VisibilityProblemLibrary/libVisibilityProblemLibrary.a

unix:!macx {
    QMAKE_CXXFLAGS += -frounding-math
    LIBS += -lboost_system
    LIBS += -lboost_thread
    LIBS += -lmpfr
    LIBS += -lgmp
    LIBS += -lCGAL -lCGAL_Core
}

macx {
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/include
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/include
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
    INCLUDEPATH += /usr/local/include
}

HEADERS += \
    bendeventtest.h \
    minmaxtest.h \
    minsumtest.h \
    shortestpathtest.h

SOURCES +=  \
    bendeventtest.cpp \
    main.cpp \
    minmaxtest.cpp \
    minsumtest.cpp \
    shortestpathtest.cpp
