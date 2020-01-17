#ifndef BENDEVENTTEST_H
#define BENDEVENTTEST_H
#include <QtTest>

// add necessary includes here
#include "spvshortestpath.h"
#include "Events/pathandboundaryeventcalculator.h"
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

public:
    BendEventTest();
    ~BendEventTest();
private:
    Polygon polygon;
    SPV::ShortestPath *shortestPath;
    SPV::GeometryUtil gU = SPV::GeometryUtil();

private slots:
    void simplePolygonTest1();
    void simplePolygonTest2();
    void simplePolygonTest3();
    void simplePolygonTest4();
    void simplePolygonTest5();
    void simplePolygonTest6();
    void simplePolygonTest7();
    void simplePolygonTest8();
    void simplePolygonTest9();
    void simplePolygonTest10();
    void simplePolygonTest11();
    void simplePolygonTest12();
    void simplePolygonTest13();
    void simplePolygonTest14();
    void simplePolygonTest15();
    void simplePolygonTest16();
    void simplePolygonTest17();
    void simplePolygonTest18();
    void simplePolygonTest19();
    void simplePolygonTest20();
    void simplePolygonTest21();
};
#endif // BENDEVENTTEST_H
