QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

SOURCES += \
    main.cpp \
    SPVGraphicsScene.cpp \
    spvgraphicsscenecgalmodel.cpp \
    spvshortestpath.cpp \
    spvshortestpathtree.cpp \
    spvfaceinfo.cpp \
    spventryonshortestpath.cpp \
    spveventmap.cpp \
    spvboundaryevents.cpp \
    spvbendevents.cpp \
    spvbaseevents.cpp \
    spveventonshortestpath.cpp \
    spvminimumcalculator.cpp \
    spvminimumcalculatorminmax.cpp


HEADERS += \
    SPVGraphicsScene.h \
    SPVGraphicsSceneCGALModel.h \
    spvshortestpath.h \
    spvshortestpathtree.h \
    spvfaceinfo.h \
    spventryonshortestpath.h \
    spveventmap.h \
    spveventintersection.h \
    spvboundaryevents.h \
    spvgeometryutil.h \
    spvbendevents.h \
    spvbaseevents.h \
    spveventonshortestpath.h \
    spvminimum.h \
    spvminimumcalculator.h \
    spvminimumcalculatorminmax.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/lib/release/ -lgmp.10
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/lib/debug/ -lgmp.10
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/lib/ -lgmp.10

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.1.2_2/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/lib/release/ -lmpfr.6
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/lib/debug/ -lmpfr.6
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/lib/ -lmpfr.6

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/4.0.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/release/ -lboost_system-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/debug/ -lboost_system-mt
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/ -lboost_system-mt

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/release/ -lboost_thread-mt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/debug/ -lboost_thread-mt
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/lib/ -lboost_thread-mt

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.68.0_1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/release/ -lCGAL_Core.13.0.2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/debug/ -lCGAL_Core.13.0.2
else:unix: LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/ -lCGAL_Core.13.0.2

INCLUDEPATH += $$PWD/../../../CGAL/CGAL-4.13/include
DEPENDPATH += $$PWD/../../../CGAL/CGAL-4.13/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/release/ -lCGAL_ImageIO.13.0.2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/debug/ -lCGAL_ImageIO.13.0.2
else:unix: LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/ -lCGAL_ImageIO.13.0.2

INCLUDEPATH += $$PWD/../../../CGAL/CGAL-4.13/include
DEPENDPATH += $$PWD/../../../CGAL/CGAL-4.13/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/release/ -lCGAL_Qt5.13.0.2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/debug/ -lCGAL_Qt5.13.0.2
else:unix: LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/ -lCGAL_Qt5.13.0.2

INCLUDEPATH += $$PWD/../../../CGAL/CGAL-4.13/include
DEPENDPATH += $$PWD/../../../CGAL/CGAL-4.13/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/release/ -lCGAL.13.0.2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/debug/ -lCGAL.13.0.2
else:unix: LIBS += -L$$PWD/../../../CGAL/CGAL-4.13/lib/ -lCGAL.13.0.2

INCLUDEPATH += $$PWD/../../../CGAL/CGAL-4.13/include
DEPENDPATH += $$PWD/../../../CGAL/CGAL-4.13/include
