#include <QtTest>

// add necessary includes here
#include "spvshortestpath.h"
#include "spvminimum.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon;

class MinimumTest : public QObject
{
    Q_OBJECT

public:
    MinimumTest();
    ~MinimumTest();
private:
    Polygon polygon;
    SPV::ShortestPath *shortestPath;
    std::vector<SPV::Minimum*> minima;

private slots:
    void simplePolygonTest1();
    void simplePolygonTest2();

};

MinimumTest::MinimumTest()
{

}

MinimumTest::~MinimumTest()
{

}

void MinimumTest::simplePolygonTest1()
{
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 5.0, 5.0);
    shortestPath->setPoint(1, 9.0, 6.0);
    shortestPath->calculateShortestPath();
    minima = shortestPath->getMinima();
    QCOMPARE(minima.size(), 1);
    SPV::Minimum *min = minima.at(0);

    double distance = min->getDistance() * 1000;
    QCOMPARE(round(distance), 2121);
    delete shortestPath;
}

void MinimumTest::simplePolygonTest2()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 5.0, 6.0);
    shortestPath->setPoint(1, 9.0, 5.0);
    shortestPath->calculateShortestPath();
    minima = shortestPath->getMinima();
    QCOMPARE(minima.size(), 1);
    SPV::Minimum *min = minima.at(0);

    double distance = min->getDistance() * 1000;
    QCOMPARE(round(distance), 2121);
    delete shortestPath;
}

QTEST_APPLESS_MAIN(MinimumTest)

#include "tst_minimumtest.moc"
