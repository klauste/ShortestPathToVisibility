#ifndef BENDEVENTTEST_H
#define BENDEVENTTEST_H
#include <QtTest>

// add necessary includes here
#include "Minima/minmaxcalculator.h"
#include "Events/bendeventcalculator.h"
#include "Models/eventsegment.h"
#include "Models/lineofsight.h"
#include "Utils/geometryutil.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon;

class BendEventTest : public QObject
{
    Q_OBJECT

private:
    Polygon polygon;
    SPV::GeometryUtil gU = SPV::GeometryUtil();
    SPV::BendEventCalculator *bendEventCalculator;

private slots:
    void bendEventTest1();
    void bendEventTest2();
    void bendEventTest3();
    void bendEventTest4();
    void bendEventTest5();
    void bendEventTest6();
    void bendEventTest7();
    void bendEventTest8();
};
#endif // BENDEVENTTEST_H
