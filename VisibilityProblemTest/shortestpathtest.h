#ifndef SHORTESTPATHTEST_H
#define SHORTESTPATHTEST_H
#include <QtTest>

// add necessary includes here
#include "Events/pathandboundaryeventcalculator.h"
#include "Models/eventsegment.h"
#include "Models/lineofsight.h"
#include "Utils/geometryutil.h"
#include "ShortestPath/shortestpathcalculator.h"
#include "ShortestPath/shortestpathtreecalculator.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon;

class ShortestPathTest : public QObject
{
    Q_OBJECT

public:
    ShortestPathTest();
    ~ShortestPathTest();
private:
    Polygon polygon;
    SPV::GeometryUtil gU = SPV::GeometryUtil();
    std::vector<std::shared_ptr<SPV::SweptSegment>> sweptSegments;
    SPV::ShortestPathTreeCalculator *shortestPathCalculator;
    SPV::PathAndBoundaryEventCalculator *pathAndBoundaryCalculator;

private slots:
    void shortestPathTest1();
    void shortestPathTest2();
    void shortestPathTest3();
    void shortestPathTest4();
    void shortestPathTest5();
    void shortestPathTest6();
    void shortestPathTest7();
    void shortestPathTest8();
    void shortestPathTest9();
    void shortestPathTest10();
    void shortestPathTest11();
    void shortestPathTest12();
    void shortestPathTest13();
};
#endif // SHORTESTPATHTEST_H
