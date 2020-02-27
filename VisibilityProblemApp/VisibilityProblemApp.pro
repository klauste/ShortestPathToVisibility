QT += core gui

CONFIG += link_prl

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

LIBS += -L$$OUT_PWD/../VisibilityProblemLibrary/ -lVisibilityProblemLibrary

INCLUDEPATH += $$PWD/../VisibilityProblemLibrary
DEPENDPATH += $$PWD/../VisibilityProblemLibrary

PRE_TARGETDEPS += $$OUT_PWD/../VisibilityProblemLibrary/libVisibilityProblemLibrary.a

unix:!macx {
    LIBS += -lboost_system
    LIBS += -lboost_thread
    LIBS += -lmpfr
    LIBS += -lgmp
    LIBS += -lCGAL -lCGAL_Core -lCGAL_ImageIO
}

macx {
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/include
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/include
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
    INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
    INCLUDEPATH += /usr/local/include
}

HEADERS += \
    Utils/cgalgeometryconnector.h \
    mainwindow.h \
    visibilityproblemscene.h

SOURCES += \
    Utils/cgalgeometryconnector.cpp \
    main.cpp \
    mainwindow.cpp \
    visibilityproblemscene.cpp
