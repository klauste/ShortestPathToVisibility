QT += core gui

CONFIG += link_prl

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

macx: LIBS += -L$$OUT_PWD/../VisibilityProblemLibrary/ -lVisibilityProblemLibrary

INCLUDEPATH += $$PWD/../VisibilityProblemLibrary
DEPENDPATH += $$PWD/../VisibilityProblemLibrary

macx: PRE_TARGETDEPS += $$OUT_PWD/../VisibilityProblemLibrary/libVisibilityProblemLibrary.a

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/include

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/include

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

SOURCES += \
    Utils/cgalgeometryconnector.cpp \
    main.cpp \
    mainwindow.cpp \
    visibilityproblemscene.cpp

HEADERS += \
    Utils/cgalgeometryconnector.h \
    mainwindow.h \
    visibilityproblemscene.h
