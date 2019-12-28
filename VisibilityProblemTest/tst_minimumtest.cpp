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

class MinimumTest : public QObject
{
    Q_OBJECT

public:
    MinimumTest();
    ~MinimumTest();
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
};

MinimumTest::MinimumTest()
{

}

MinimumTest::~MinimumTest()
{

}

void MinimumTest::simplePolygonTest1()
{
    /*polygon.push_back(Point(3.0, 8.0));
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
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest2()
{
    /*polygon = Polygon();
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
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest3()
{
    /*polygon = Polygon();
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
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    QCOMPARE(sP.size(), 3);
    QCOMPARE(Point(5.0, 6.0), sP.at(0)->getPoint());
    QCOMPARE(Point(9.0, 5.0), sP.at(2)->getPoint());
    QCOMPARE(Point(7.0, 4.0), sP.at(1)->getPoint());
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest4()
{
    /*polygon = Polygon();
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
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();

    std::vector<SPV::SweptSegment*> segments = sP.at(1)->getSegmentsFromStart();
    SPV::SweptSegment *segment;
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(9,2));
    QCOMPARE(segment->getRightPoint(), Point(12,2));
    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(12,2));
    QCOMPARE(segment->getRightPoint(), Point(12,8));
    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(12,8));
    QCOMPARE(segment->getRightPoint(), Point(8,8));

    segments = sP.at(1)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(6,8));
    QCOMPARE(segment->getRightPoint(), Point(3,8));
    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(3,8));
    QCOMPARE(segment->getRightPoint(), Point(3,2));
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest5()
{
    /*polygon = Polygon();
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
    shortestPath->setPoint(1, 11.0, 5.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();

    std::vector<SPV::SweptSegment*> segments = sP.at(1)->getSegmentsFromStart();
    SPV::SweptSegment *segment;
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(11,2));
    QCOMPARE(segment->getRightPoint(), Point(12,2));
    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(12,2));
    QCOMPARE(segment->getRightPoint(), Point(12,8));
    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(12,8));
    QCOMPARE(segment->getRightPoint(), Point(8,8));

    segments = sP.at(1)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(6,8));
    QCOMPARE(segment->getRightPoint(), Point(3,8));
    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(3,8));
    QCOMPARE(segment->getRightPoint(), Point(3,3));
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest6()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(16.0, 7.0));
    polygon.push_back(Point(17.0, 9.0));
    polygon.push_back(Point(17.0, 12.0));
    polygon.push_back(Point(21.0, 12.0));
    polygon.push_back(Point(21.0, 8.0));
    polygon.push_back(Point(18.0, 8.0));
    polygon.push_back(Point(21.0, 5.0));
    polygon.push_back(Point(16.0, 6.0));
    polygon.push_back(Point(14.0, 3.0));
    polygon.push_back(Point(13.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 11.0, 11.0);
    shortestPath->setPoint(1, 19.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    QCOMPARE(sP.size(), 5);
    QCOMPARE(sP.at(0)->getPoint(), Point(11.0,11.0));
    QCOMPARE(sP.at(1)->getPoint(), Point(12.0,9.0));
    QCOMPARE(sP.at(2)->getPoint(), Point(14.0,7.0));
    QCOMPARE(sP.at(3)->getPoint(), Point(16.0,7.0));
    QCOMPARE(sP.at(4)->getPoint(), Point(19.0,11.0));

    std::vector<SPV::SweptSegment*> segments = sP.at(1)->getSegmentsFromStart();
    SPV::SweptSegment *segment;
    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(14.5714, 3.8571)), true);
    QCOMPARE(segment->getRightPoint(), Point(15.6,5.4));

    segments = sP.at(2)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(15.6,5.4));
    QCOMPARE(segment->getRightPoint(), Point(16,6));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(16,6));
    QCOMPARE(segment->getRightPoint(), Point(21,5));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(21,5));
    QCOMPARE(segment->getRightPoint(), Point(19,7));

    segments = sP.at(3)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(19,7));
    Point rightPoint = segment->getRightPoint();
    QCOMPARE(segment->getRightPoint(), Point(18,8));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(21,9.5));
    QCOMPARE(segment->getRightPoint(), Point(21,12));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(21,12));
    QCOMPARE(segment->getRightPoint(), Point(18.5,12));
    // From End
    // Point 1
    segments = sP.at(1)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(12,12));
    QCOMPARE(segment->getRightPoint(), Point(9,12));

    // Point 2
    segments = sP.at(2)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(9,12));
    QCOMPARE(segment->getRightPoint(), Point(6.5,12));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(11, 9));
    QCOMPARE(segment->getRightPoint(), Point(10.5,7));

    // Point 3
    segments = sP.at(3)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(10.5,7));
    QCOMPARE(segment->getRightPoint(), Point(10,5));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(10, 5));
    QCOMPARE(segment->getRightPoint(), Point(13,5));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(13,5));
    QCOMPARE(segment->getRightPoint(), Point(13.6,3.8));
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest7()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(16.0, 7.0));
    polygon.push_back(Point(17.0, 9.0));
    polygon.push_back(Point(17.0, 12.0));
    polygon.push_back(Point(21.0, 12.0));
    polygon.push_back(Point(21.0, 8.0));
    polygon.push_back(Point(18.0, 8.0));
    polygon.push_back(Point(21.0, 5.0));
    polygon.push_back(Point(16.0, 6.0));
    polygon.push_back(Point(14.0, 3.0));
    polygon.push_back(Point(13.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 19.0, 11.0);
    shortestPath->setPoint(1, 11.0, 11.0);

    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    QCOMPARE(sP.size(), 5);
    QCOMPARE(sP.at(4)->getPoint(), Point(11.0,11.0));
    QCOMPARE(sP.at(3)->getPoint(), Point(12.0,9.0));
    QCOMPARE(sP.at(2)->getPoint(), Point(14.0,7.0));
    QCOMPARE(sP.at(1)->getPoint(), Point(16.0,7.0));
    QCOMPARE(sP.at(0)->getPoint(), Point(19.0,11.0));

    std::vector<SPV::SweptSegment*> segments = sP.at(3)->getSegmentsFromEnd();
    SPV::SweptSegment *segment;
    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(14.5714, 3.8571)), true);
    QCOMPARE(segment->getRightPoint(), Point(15.6,5.4));

    segments = sP.at(2)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(15.6,5.4));
    QCOMPARE(segment->getRightPoint(), Point(16,6));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(16,6));
    QCOMPARE(segment->getRightPoint(), Point(21,5));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(21,5));
    QCOMPARE(segment->getRightPoint(), Point(19,7));

    segments = sP.at(1)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(19,7));
    QCOMPARE(segment->getRightPoint(), Point(18,8));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(21,9.5));
    QCOMPARE(segment->getRightPoint(), Point(21,12));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(21,12));
    QCOMPARE(segment->getRightPoint(), Point(18.5,12));
    // From End
    // Point 1
    segments = sP.at(3)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(12,12));
    QCOMPARE(segment->getRightPoint(), Point(9,12));

    // Point 2
    segments = sP.at(2)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(9,12));
    QCOMPARE(segment->getRightPoint(), Point(6.5,12));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(11, 9));
    QCOMPARE(segment->getRightPoint(), Point(10.5,7));

    // Point 3
    segments = sP.at(1)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(10.5,7));
    QCOMPARE(segment->getRightPoint(), Point(10,5));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(10, 5));
    QCOMPARE(segment->getRightPoint(), Point(13,5));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(13,5));
    QCOMPARE(segment->getRightPoint(), Point(13.6,3.8));
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest8()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(15.0, 9.0));
    polygon.push_back(Point(17.0, 7.0));
    polygon.push_back(Point(19.0, 8.0));
    polygon.push_back(Point(19.0, 4.0));
    polygon.push_back(Point(15.0, 2.0));
    polygon.push_back(Point(11.5, 3.5));
    polygon.push_back(Point(10.0, 2.0));
    polygon.push_back(Point(6.0, 5.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(9.0, 4.0));
    polygon.push_back(Point(15.0, 4.0));
    polygon.push_back(Point(18.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 11.0, 11.0);
    shortestPath->setPoint(1, 8.0, 5.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    QCOMPARE(sP.size(), 7);
    QCOMPARE(sP.at(0)->getPoint(), Point(11.0,11.0));
    QCOMPARE(sP.at(1)->getPoint(), Point(12.0,9.0));
    QCOMPARE(sP.at(2)->getPoint(), Point(14.0,7.0));
    QCOMPARE(sP.at(3)->getPoint(), Point(18.0,5.0));
    QCOMPARE(sP.at(4)->getPoint(), Point(15.0,4.0));
    QCOMPARE(sP.at(5)->getPoint(), Point(9.0,4.0));
    QCOMPARE(sP.at(6)->getPoint(), Point(8.0,5.0));

    std::vector<SPV::SweptSegment*> segments = sP.at(1)->getSegmentsFromStart();
    SPV::SweptSegment *segment;
    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(14, 5));
    QCOMPARE(segment->getRightPoint(), Point(16,5));

    segments = sP.at(2)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(16,5));
    QCOMPARE(segment->getRightPoint(), Point(18,5));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(19, 4.5));
    QCOMPARE(segment->getRightPoint(), Point(19,7));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(17,7));
    QCOMPARE(segment->getRightPoint(), Point(15,9));

    segments = sP.at(3)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(12.375,3.125));
    QCOMPARE(segment->getRightPoint(), Point(15,2));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(15,2));
    QCOMPARE(segment->getRightPoint(), Point(19,4));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(19,4));
    QCOMPARE(segment->getRightPoint(), Point(19, 4.5));

    segments = sP.at(4)->getSegmentsFromStart();

    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(7.3333, 4)), true);
    QCOMPARE(segment->getRightPoint(), Point(8.56,3.08));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(11.5,3.5));
    QCOMPARE(segment->getRightPoint(), Point(12.375,3.125));

    segments = sP.at(5)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(8,6));
    QCOMPARE(segment->getRightPoint(), Point(6,5));
    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(6,5));
    QCOMPARE(gU.pointsAreEqual(segment->getRightPoint(), Point(7.3333, 4)), true);

    // From End
    // Point 1
    segments = sP.at(1)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(12,12));
    QCOMPARE(segment->getRightPoint(), Point(9,12));

    // Point 2
    segments = sP.at(2)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(9,12));
    QCOMPARE(segment->getRightPoint(), Point(6.5,12));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(11, 9));
    QCOMPARE(gU.pointsAreEqual(segment->getRightPoint(), Point(10.8889, 8.5556)), true);

    // Point 3
    segments = sP.at(3)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 5);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(19, 5.3333)), true);
    QCOMPARE(segment->getRightPoint(), Point(19,8));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(19, 8));
    QCOMPARE(segment->getRightPoint(), Point(17,7));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(17,7));
    QCOMPARE(segment->getRightPoint(), Point(15,9));

    segment = segments.at(3);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(15,9));
    QCOMPARE(segment->getRightPoint(), Point(14,7));

    segment = segments.at(4);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(10.8889, 8.5556)), true);
    QCOMPARE(segment->getRightPoint(), Point(10,5));

    // Point 4
    segments = sP.at(4)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(19,4));
    QCOMPARE(gU.pointsAreEqual(segment->getRightPoint(), Point(19, 5.3333)), true);

    // Point 5
    segments = sP.at(5)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(10.5,2.5));
    QCOMPARE(segment->getRightPoint(), Point(11.5,3.5));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(16.1429, 2.5714)), true);
    QCOMPARE(segment->getRightPoint(), Point(19,4));
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest9()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(15.0, 9.0));
    polygon.push_back(Point(17.0, 7.0));
    polygon.push_back(Point(19.0, 8.0));
    polygon.push_back(Point(19.0, 4.0));
    polygon.push_back(Point(15.0, 2.0));
    polygon.push_back(Point(11.5, 3.5));
    polygon.push_back(Point(10.0, 2.0));
    polygon.push_back(Point(6.0, 5.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(9.0, 4.0));
    polygon.push_back(Point(15.0, 4.0));
    polygon.push_back(Point(18.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 8.0, 5.0);
    shortestPath->setPoint(1, 11.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    QCOMPARE(sP.size(), 7);
    QCOMPARE(sP.at(6)->getPoint(), Point(11.0,11.0));
    QCOMPARE(sP.at(5)->getPoint(), Point(12.0,9.0));
    QCOMPARE(sP.at(4)->getPoint(), Point(14.0,7.0));
    QCOMPARE(sP.at(3)->getPoint(), Point(18.0,5.0));
    QCOMPARE(sP.at(2)->getPoint(), Point(15.0,4.0));
    QCOMPARE(sP.at(1)->getPoint(), Point(9.0,4.0));
    QCOMPARE(sP.at(0)->getPoint(), Point(8.0,5.0));

    std::vector<SPV::SweptSegment*> segments = sP.at(5)->getSegmentsFromEnd();
    SPV::SweptSegment *segment;
    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(14, 5));
    QCOMPARE(segment->getRightPoint(), Point(16,5));

    segments = sP.at(4)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(16,5));
    QCOMPARE(segment->getRightPoint(), Point(18,5));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(19, 4.5));
    QCOMPARE(segment->getRightPoint(), Point(19,7));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(17,7));
    QCOMPARE(segment->getRightPoint(), Point(15,9));

    segments = sP.at(3)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 3);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(12.375,3.125));
    QCOMPARE(segment->getRightPoint(), Point(15,2));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(15,2));
    QCOMPARE(segment->getRightPoint(), Point(19,4));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(19,4));
    QCOMPARE(segment->getRightPoint(), Point(19, 4.5));

    segments = sP.at(2)->getSegmentsFromEnd();

    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(7.3333, 4)), true);
    QCOMPARE(segment->getRightPoint(), Point(8.56,3.08));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(11.5,3.5));
    QCOMPARE(segment->getRightPoint(), Point(12.375,3.125));

    segments = sP.at(1)->getSegmentsFromEnd();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(8,6));
    QCOMPARE(segment->getRightPoint(), Point(6,5));
    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(6,5));
    QCOMPARE(gU.pointsAreEqual(segment->getRightPoint(), Point(7.3333, 4)), true);

    // From Start
    // Point 5
    segments = sP.at(5)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(12,12));
    QCOMPARE(segment->getRightPoint(), Point(9,12));

    // Point 2
    segments = sP.at(4)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(9,12));
    QCOMPARE(segment->getRightPoint(), Point(6.5,12));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(11, 9));
    QCOMPARE(gU.pointsAreEqual(segment->getRightPoint(), Point(10.8889, 8.5556)), true);

    // Point 3
    segments = sP.at(3)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 5);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(19, 5.3333)), true);
    QCOMPARE(segment->getRightPoint(), Point(19,8));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(19, 8));
    QCOMPARE(segment->getRightPoint(), Point(17,7));

    segment = segments.at(2);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(17,7));
    QCOMPARE(segment->getRightPoint(), Point(15,9));

    segment = segments.at(3);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(15,9));
    QCOMPARE(segment->getRightPoint(), Point(14,7));

    segment = segments.at(4);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(10.8889, 8.5556)), true);
    QCOMPARE(segment->getRightPoint(), Point(10,5));

    // Point 4
    segments = sP.at(2)->getSegmentsFromStart();

    QCOMPARE(segments.size(), 1);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), true);
    QCOMPARE(segment->rightPointIsPolygonVertex(), false);
    QCOMPARE(segment->getLeftPoint(), Point(19,4));
    QCOMPARE(gU.pointsAreEqual(segment->getRightPoint(), Point(19, 5.3333)), true);

    // Point 5
    segments = sP.at(1)->getSegmentsFromStart();
    QCOMPARE(segments.size(), 2);
    segment = segments.at(0);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(segment->getLeftPoint(), Point(10.5,2.5));
    QCOMPARE(segment->getRightPoint(), Point(11.5,3.5));

    segment = segments.at(1);
    QCOMPARE(segment->leftPointIsPolygonVertex(), false);
    QCOMPARE(segment->rightPointIsPolygonVertex(), true);
    QCOMPARE(gU.pointsAreEqual(segment->getLeftPoint(), Point(16.1429, 2.5714)), true);
    QCOMPARE(segment->getRightPoint(), Point(19,4));
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest10()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(15.0, 9.0));
    polygon.push_back(Point(17.0, 7.0));
    polygon.push_back(Point(19.0, 8.0));
    polygon.push_back(Point(19.0, 4.0));
    polygon.push_back(Point(15.0, 2.0));
    polygon.push_back(Point(11.5, 3.5));
    polygon.push_back(Point(10.0, 2.0));
    polygon.push_back(Point(6.0, 5.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(9.0, 4.0));
    polygon.push_back(Point(15.0, 4.0));
    polygon.push_back(Point(18.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 11.0, 11.0);
    shortestPath->setPoint(1, 8.0, 5.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);
    std::vector<SPV::SweptSegment*> segments = eC->getSegmentsForFinalPoint(true);
    QCOMPARE(segments.size(), 1);
    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->getLeftPoint(), Point(10.5,12));
    QCOMPARE(segments.at(0)->getRightPoint(), Point(9,12));

    segments.clear();
    segments = eC->getSegmentsForFinalPoint(false);
    QCOMPARE(segments.size(), 2);
    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), true);

    QCOMPARE(gU.pointsAreEqual(segments.at(0)->getLeftPoint(), Point(7.3333,5.6667)), true);
    QCOMPARE(segments.at(0)->getRightPoint(), Point(6,5));
    QCOMPARE(segments.at(1)->leftPointIsPolygonVertex(), true);
    QCOMPARE(segments.at(1)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(1)->getLeftPoint(), Point(6,5));
    QCOMPARE(gU.pointsAreEqual(segments.at(1)->getRightPoint(), Point(7.3333,4)), true);
    segments.clear();*/
}

void MinimumTest::simplePolygonTest11()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(15.0, 9.0));
    polygon.push_back(Point(17.0, 7.0));
    polygon.push_back(Point(19.0, 8.0));
    polygon.push_back(Point(19.0, 4.0));
    polygon.push_back(Point(15.0, 2.0));
    polygon.push_back(Point(11.5, 3.5));
    polygon.push_back(Point(10.0, 2.0));
    polygon.push_back(Point(6.0, 5.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(9.0, 4.0));
    polygon.push_back(Point(15.0, 4.0));
    polygon.push_back(Point(18.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 8.0, 5.0);
    shortestPath->setPoint(1, 11.0, 11.0);

    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);
    std::vector<SPV::SweptSegment*> segments = eC->getSegmentsForFinalPoint(false);
    QCOMPARE(segments.size(), 1);
    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->getLeftPoint(), Point(10.5,12));
    QCOMPARE(segments.at(0)->getRightPoint(), Point(9,12));

    segments.clear();
    segments = eC->getSegmentsForFinalPoint(true);
    QCOMPARE(segments.size(), 2);
    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), true);

    QCOMPARE(gU.pointsAreEqual(segments.at(0)->getLeftPoint(), Point(7.3333,5.6667)), true);
    QCOMPARE(segments.at(0)->getRightPoint(), Point(6,5));
    QCOMPARE(segments.at(1)->leftPointIsPolygonVertex(), true);
    QCOMPARE(segments.at(1)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(1)->getLeftPoint(), Point(6,5));
    QCOMPARE(gU.pointsAreEqual(segments.at(1)->getRightPoint(), Point(7.3333,4)), true);
    segments.clear();*/
}

void MinimumTest::simplePolygonTest12()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(16.0, 7.0));
    polygon.push_back(Point(17.0, 9.0));
    polygon.push_back(Point(17.0, 12.0));
    polygon.push_back(Point(21.0, 12.0));
    polygon.push_back(Point(21.0, 8.0));
    polygon.push_back(Point(18.0, 8.0));
    polygon.push_back(Point(21.0, 5.0));
    polygon.push_back(Point(16.0, 6.0));
    polygon.push_back(Point(14.0, 3.0));
    polygon.push_back(Point(13.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 11.0, 11.0);
    shortestPath->setPoint(1, 19.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);

    std::vector<SPV::SweptSegment*> segments = eC->getSegmentsForFinalPoint(true);
    QCOMPARE(segments.size(), 1);
    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->getLeftPoint(), Point(10.5,12));
    QCOMPARE(segments.at(0)->getRightPoint(), Point(9,12));

    segments.clear();
    eC->setCurrentSegmentOrderFromLeftToRightFromOutside(false);

    segments = eC->getSegmentsForFinalPoint(false);
    QCOMPARE(segments.size(), 3);

    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), true);
    QCOMPARE(segments.at(0)->getLeftPoint(), Point(19,7));
    QCOMPARE(segments.at(0)->getRightPoint(), Point(18,8));

    QCOMPARE(segments.at(1)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(1)->rightPointIsPolygonVertex(), true);
    QCOMPARE(segments.at(1)->getLeftPoint(), Point(21,9.5));
    QCOMPARE(segments.at(1)->getRightPoint(), Point(21,12));

    QCOMPARE(segments.at(2)->leftPointIsPolygonVertex(), true);
    QCOMPARE(segments.at(2)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(2)->getLeftPoint(), Point(21,12));
    QCOMPARE(segments.at(2)->getRightPoint(), Point(19.75,12));
    segments.clear();
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest13()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(16.0, 7.0));
    polygon.push_back(Point(17.0, 9.0));
    polygon.push_back(Point(17.0, 12.0));
    polygon.push_back(Point(21.0, 12.0));
    polygon.push_back(Point(21.0, 8.0));
    polygon.push_back(Point(18.0, 8.0));
    polygon.push_back(Point(21.0, 5.0));
    polygon.push_back(Point(16.0, 6.0));
    polygon.push_back(Point(14.0, 3.0));
    polygon.push_back(Point(13.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 19.0, 11.0);
    shortestPath->setPoint(1, 11.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);

    std::vector<SPV::SweptSegment*> segments = eC->getSegmentsForFinalPoint(false);
    QCOMPARE(segments.size(), 1);
    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->getLeftPoint(), Point(10.5,12));
    QCOMPARE(segments.at(0)->getRightPoint(), Point(9,12));

    segments.clear();
    eC->setCurrentSegmentOrderFromLeftToRightFromOutside
            (false);
    segments = eC->getSegmentsForFinalPoint(true);
    QCOMPARE(segments.size(), 3);

    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), true);
    QCOMPARE(segments.at(0)->getLeftPoint(), Point(19,7));
    QCOMPARE(segments.at(0)->getRightPoint(), Point(18,8));

    QCOMPARE(segments.at(1)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(1)->rightPointIsPolygonVertex(), true);
    QCOMPARE(segments.at(1)->getLeftPoint(), Point(21,9.5));
    QCOMPARE(segments.at(1)->getRightPoint(), Point(21,12));

    QCOMPARE(segments.at(2)->leftPointIsPolygonVertex(), true);
    QCOMPARE(segments.at(2)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(2)->getLeftPoint(), Point(21,12));
    Point r = segments.at(2)->getRightPoint();
    QCOMPARE(segments.at(2)->getRightPoint(), Point(19.75,12));
    segments.clear();
    delete shortestPath;*/
}

void MinimumTest::simplePolygonTest14()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(16.0, 7.0));
    polygon.push_back(Point(17.0, 9.0));
    polygon.push_back(Point(17.0, 12.0));
    polygon.push_back(Point(21.0, 12.0));
    polygon.push_back(Point(21.0, 8.0));
    polygon.push_back(Point(18.0, 8.0));
    polygon.push_back(Point(21.0, 5.0));
    polygon.push_back(Point(16.0, 6.0));
    polygon.push_back(Point(14.0, 3.0));
    polygon.push_back(Point(13.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 11.0, 11.0);
    shortestPath->setPoint(1, 19.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(12,9));
    SPV::LineOfSight *loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide() , Point(10.5,12));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(14.5714, 3.8571)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(9,12));
    QCOMPARE(loS->getPointOnEndSide(), Point(15.6, 5.4));
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(12,9));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), false);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide() , Point(9,12));
    QCOMPARE(loS->getPointOnEndSide(), Point(15.6, 5.4));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(6.5,12));
     QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(15.8461, 5.7692)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide() , Point(11,9));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(15.8461, 5.7692)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(10.8888, 8.5555)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(16, 6));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(10.8888, 8.5555)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(16, 6));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(10.7333, 7.9333)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(21, 5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(10.7333, 7.9333)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(21, 5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(10.5, 7));
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 7));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(10.5, 7));
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 7));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(10, 5));
    QCOMPARE(loS->getPointOnEndSide(), Point(18.25, 7.75));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(10, 5));
    QCOMPARE(loS->getPointOnEndSide(), Point(18.25, 7.75));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(12, 5));
    QCOMPARE(loS->getPointOnEndSide(), Point(18, 8));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(12, 5));
    QCOMPARE(loS->getPointOnEndSide(), Point(21, 9.5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(13, 5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(21, 10.3333)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(13, 5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(21, 10.3333)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(13.3333, 4.3333)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(21, 12));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(13.3333, 4.3333)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(21, 12));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(13.6, 3.8));
    QCOMPARE(loS->getPointOnEndSide(), Point(19.75, 12));
    QCOMPARE(eS->hasSuccessor(), false);
    QCOMPARE(eS->hasPredecessor(), true);*/
}

void MinimumTest::simplePolygonTest15()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(16.0, 7.0));
    polygon.push_back(Point(17.0, 9.0));
    polygon.push_back(Point(17.0, 12.0));
    polygon.push_back(Point(21.0, 12.0));
    polygon.push_back(Point(21.0, 8.0));
    polygon.push_back(Point(18.0, 8.0));
    polygon.push_back(Point(21.0, 5.0));
    polygon.push_back(Point(16.0, 6.0));
    polygon.push_back(Point(14.0, 3.0));
    polygon.push_back(Point(13.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 19.0, 11.0);
    shortestPath->setPoint(1, 11.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();

    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    SPV::LineOfSight * loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(13.6, 3.8));
    QCOMPARE(loS->getPointOnStartSide(), Point(19.75, 12));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(13.3333, 4.3333)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(21, 12));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), false);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(13.3333, 4.3333)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(21, 12));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(13, 5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 10.3333)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(13, 5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 10.3333)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(12, 5));
    QCOMPARE(loS->getPointOnStartSide(), Point(21, 9.5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(12, 5));
    QCOMPARE(loS->getPointOnStartSide(), Point(18, 8));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(10, 5));
    QCOMPARE(loS->getPointOnStartSide(), Point(18.25, 7.75));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(16,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(10, 5));
    QCOMPARE(loS->getPointOnStartSide(), Point(18.25, 7.75));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(10.5, 7));
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 7));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(10.5, 7));
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 7));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(10.7333, 7.9333)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(21, 5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(10.7333, 7.9333)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(21, 5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(10.8888, 8.5555)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(16, 6));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(10.8888, 8.5555)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(16, 6));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide() , Point(11,9));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(15.8461, 5.7692)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(6.5,12));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(15.8461, 5.7692)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide() , Point(9,12));
    QCOMPARE(loS->getPointOnStartSide(), Point(15.6, 5.4));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(12,9));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(9,12));
    QCOMPARE(loS->getPointOnStartSide(), Point(15.6, 5.4));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide() , Point(10.5,12));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14.5714, 3.8571)), true);
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(12,9));
    QCOMPARE(eS->hasSuccessor(), false);
    QCOMPARE(eS->hasPredecessor(), true);*/
}

void MinimumTest::simplePolygonTest16()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(13.0, 10.0));
    polygon.push_back(Point(13.0, 11.0));
    polygon.push_back(Point(15.0, 11.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(15.0, 9.0));
    polygon.push_back(Point(17.0, 7.0));
    polygon.push_back(Point(19.0, 8.0));
    polygon.push_back(Point(19.0, 4.0));
    polygon.push_back(Point(15.0, 2.0));
    polygon.push_back(Point(11.5, 3.5));
    polygon.push_back(Point(10.0, 2.0));
    polygon.push_back(Point(6.0, 5.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(9.0, 4.0));
    polygon.push_back(Point(15.0, 4.0));
    polygon.push_back(Point(18.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 11.0, 11.0);
    shortestPath->setPoint(1, 8.0, 5.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);

    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(12,9));
    SPV::LineOfSight *loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide() , Point(10.5,12));
    QCOMPARE(loS->getPointOnEndSide(), Point(14, 5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(9,12));
    QCOMPARE(loS->getPointOnEndSide(), Point(16, 5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), false);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(9,12));
    QCOMPARE(loS->getPointOnEndSide(), Point(16, 5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(6.5,12));
    QCOMPARE(loS->getPointOnEndSide(), Point(17, 5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide() , Point(11,9));
    QCOMPARE(loS->getPointOnEndSide(), Point(17, 5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(10.8888, 8.5555)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(18, 5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(14, 7));
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 4.5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14.6666, 8.3333)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 4));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14.6666, 8.3333)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 4));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(15, 9));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(18.8182, 3.9091)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(15, 9));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(18.8182, 3.9091)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(17, 7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(18.6, 3.8)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(17, 7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(18.6, 3.8)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 8));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(17.4, 3.2)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 8));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(17.4, 3.2)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 6));
    QCOMPARE(loS->getPointOnEndSide(), Point(15, 2));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 6));
    QCOMPARE(loS->getPointOnEndSide(), Point(15, 2));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19, 5.3333)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(12.375, 3.125));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(15,4));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19, 5.3333)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(12.375, 3.125));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19, 4.5714)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(11.5, 3.5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(15,4));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19, 4.5714)), true);
    QCOMPARE(loS->getPointOnEndSide(), Point(8.56, 3.08));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 4));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(7.3333, 4)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 4));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(7.3333, 4)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(16.1429, 2.5714)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(6.7273, 4.4545)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(11.5, 3.5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(6.7273, 4.4545)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(11.25, 3.25));
    QCOMPARE(loS->getPointOnEndSide(), Point(6,5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(11.25, 3.25));
    QCOMPARE(loS->getPointOnEndSide(), Point(6,5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnStartSide(), Point(10.5, 2.5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(7.3333, 5.6666)), true);
    QCOMPARE(eS->hasSuccessor(), false);
    QCOMPARE(eS->hasPredecessor(), true);*/
}

void MinimumTest::simplePolygonTest17()
{
    /*polygon = Polygon();
    polygon.push_back(Point(6.0, 12.0));
    polygon.push_back(Point(12.0, 12.0));
    polygon.push_back(Point(12.0, 9.0));
    polygon.push_back(Point(13.0, 10.0));
    polygon.push_back(Point(13.0, 11.0));
    polygon.push_back(Point(15.0, 11.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(15.0, 9.0));
    polygon.push_back(Point(17.0, 7.0));
    polygon.push_back(Point(19.0, 8.0));
    polygon.push_back(Point(19.0, 4.0));
    polygon.push_back(Point(15.0, 2.0));
    polygon.push_back(Point(11.5, 3.5));
    polygon.push_back(Point(10.0, 2.0));
    polygon.push_back(Point(6.0, 5.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(9.0, 4.0));
    polygon.push_back(Point(15.0, 4.0));
    polygon.push_back(Point(18.0, 5.0));
    polygon.push_back(Point(10.0, 5.0));
    polygon.push_back(Point(11.0, 9.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(8.0, 10.0));
    polygon.push_back(Point(6.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 8.0, 5.0);
    shortestPath->setPoint(1, 11.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);
    std::vector<SPV::SweptSegment*> segments = eC->getSegmentsForFinalPoint(true);

    SPV::EventSegment *eS = shortestPath->getFirstEvent();

    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
    SPV::LineOfSight *loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(11.25, 3.25));
    QCOMPARE(loS->getPointOnStartSide(), Point(6,5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(10.5, 2.5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(7.3333, 5.6666)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), false);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(11.5, 3.5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(6.7273, 4.4545)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(11.25, 3.25));
    QCOMPARE(loS->getPointOnStartSide(), Point(6,5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 4));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(7.3333, 4)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(16.1429, 2.5714)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(6.7273, 4.4545)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(15,4));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(19, 4.5714)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(8.56, 3.08));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 4));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(7.3333, 4)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(15,4));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(19, 5.3333)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(12.375, 3.125));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(19, 4.5714)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(11.5, 3.5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 6));
    QCOMPARE(loS->getPointOnStartSide(), Point(15, 2));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(19, 5.3333)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(12.375, 3.125));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 8));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(17.4, 3.2)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 6));
    QCOMPARE(loS->getPointOnStartSide(), Point(15, 2));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(17, 7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(18.6, 3.8)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(19, 8));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(17.4, 3.2)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(15, 9));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(18.8182, 3.9091)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(17, 7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(18.6, 3.8)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(14.6666, 8.3333)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 4));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(15, 9));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(18.8182, 3.9091)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(18,5));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(14, 7));
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 4.5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(14.6666, 8.3333)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(19, 4));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide() , Point(11,9));
    QCOMPARE(loS->getPointOnStartSide(), Point(17, 5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(10.8888, 8.5555)), true);
    QCOMPARE(loS->getPointOnStartSide(), Point(18, 5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(9,12));
    QCOMPARE(loS->getPointOnStartSide(), Point(16, 5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(6.5,12));
    QCOMPARE(loS->getPointOnStartSide(), Point(17, 5));
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(12,9));
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide() , Point(10.5,12));
    QCOMPARE(loS->getPointOnStartSide(), Point(14, 5));
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(loS->getPointOnEndSide(), Point(9,12));
    QCOMPARE(loS->getPointOnStartSide(), Point(16, 5));
    QCOMPARE(eS->hasSuccessor(), false);
    QCOMPARE(eS->hasPredecessor(), true);*/
}

void MinimumTest::simplePolygonTest18()
{
    /*polygon = Polygon();
    polygon.push_back(Point(16.0, 12.0));
    polygon.push_back(Point(19.0, 12.0));
    polygon.push_back(Point(19.0, 7.0));
    polygon.push_back(Point(13.0, 7.0));
    polygon.push_back(Point(14.0, 5.0));
    polygon.push_back(Point(18.0, 5.0));
    polygon.push_back(Point(18.0, 3.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(11.0, 5.0));
    polygon.push_back(Point(8.0, 5.0));
    polygon.push_back(Point(12.5, 6));
    polygon.push_back(Point(11.0, 8.0));
    polygon.push_back(Point(14.5, 7.5));
    polygon.push_back(Point(11.0, 12.0));
    polygon.push_back(Point(14.0, 12.0));
    polygon.push_back(Point(14.0, 10.0));
    polygon.push_back(Point(15.0, 8.0));
    polygon.push_back(Point(16.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 17.0, 11.0);
    shortestPath->setPoint(1, 17.0, 4.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();

    SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);
    std::vector<SPV::SweptSegment*> segments = eC->getSegmentsForFinalPoint(true);

    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::LineOfSight *loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(15,8));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(17.6666, 12)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(14.3333,7)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19,12)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(14,7)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), false);

    eS = eS->getSuccessor();
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14.5,7.5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19,12)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(14,7)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19,9)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(13,7)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(13,7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14.5,7.5)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12,6.6666)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(13.3333, 7.6666)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12.5,6)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(13,7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(13.3333, 7.6666)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(11.5,4)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(13.1724, 7.6897)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(13,7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(13.1724, 7.6897)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12,3)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12.6154, 7.7692)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(15,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12.6154, 7.7692)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(15,3)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(11, 8)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(16,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(11, 8)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(16,3)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12.5, 6)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(17,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12.5, 6)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(17,3)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12.1538, 5.9231)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(18,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12.1538, 5.9231)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(18,3)), true);
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(11.6, 5.8)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(18,3.6666)), true);
    QCOMPARE(eS->hasSuccessor(), false);
    QCOMPARE(eS->hasPredecessor(), true);*/
}

void MinimumTest::simplePolygonTest19()
{
    /*polygon = Polygon();
    polygon.push_back(Point(16.0, 12.0));
    polygon.push_back(Point(19.0, 12.0));
    polygon.push_back(Point(19.0, 7.0));
    polygon.push_back(Point(13.0, 7.0));
    polygon.push_back(Point(14.0, 5.0));
    polygon.push_back(Point(18.0, 5.0));
    polygon.push_back(Point(18.0, 3.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(11.0, 5.0));
    polygon.push_back(Point(8.0, 5.0));
    polygon.push_back(Point(12.5, 6));
    polygon.push_back(Point(11.0, 8.0));
    polygon.push_back(Point(14.5, 7.5));
    polygon.push_back(Point(11.0, 12.0));
    polygon.push_back(Point(14.0, 12.0));
    polygon.push_back(Point(14.0, 10.0));
    polygon.push_back(Point(15.0, 8.0));
    polygon.push_back(Point(16.0, 10.0));
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 17.0, 4.0);
    shortestPath->setPoint(1, 17.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();

    SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);
    std::vector<SPV::SweptSegment*> segments = eC->getSegmentsForFinalPoint(true);

    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::LineOfSight *loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12.1538, 5.9231)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(18,3)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(11.6, 5.8)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(18,3.6666)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), false);

    eS = eS->getSuccessor();
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12.5, 6)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(17,3)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12.1538, 5.9231)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(18,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(11, 8)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(16,3)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12.5, 6)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(17,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12.6154, 7.7692)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(15,3)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(11, 8)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(16,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(13,7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(13.1724, 7.6897)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12,3)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(12.6154, 7.7692)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(15,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(13,7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(13.3333, 7.6666)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(11.5,4)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(13.1724, 7.6897)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12,3)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(13,7));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(14.5,7.5)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12,6.6666)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(13.3333, 7.6666)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(12.5,6)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14.5,7.5));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(19,12)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14,7)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(19,9)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(13,7)), true);
    QCOMPARE(eS->hasSuccessor(), true);
    QCOMPARE(eS->hasPredecessor(), true);

    eS = eS->getSuccessor();
    loS = eS->getSecondLineOfSightFromStart();
    QCOMPARE(eS->getPivotPoint()->getPoint(), Point(15,8));
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(17.6666, 12)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14.3333,7)), true);
    loS = eS->getFirstLineOfSightFromStart();
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(19,12)), true);
    QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14,7)), true);
    QCOMPARE(eS->hasSuccessor(), false);
    QCOMPARE(eS->hasPredecessor(), true);*/
}

void MinimumTest::simplePolygonTest20()
{
    polygon = Polygon();
        polygon.push_back(Point(6.0, 12.0));
        polygon.push_back(Point(12.0, 12.0));
        polygon.push_back(Point(12.0, 9.0));
        polygon.push_back(Point(13.0, 10.0));
        polygon.push_back(Point(13.0, 11.0));
        polygon.push_back(Point(15.0, 11.0));
        polygon.push_back(Point(14.0, 7.0));
        polygon.push_back(Point(15.0, 9.0));
        polygon.push_back(Point(17.0, 7.0));
        polygon.push_back(Point(21.0, 8.0));
        polygon.push_back(Point(21.0, 4.0));
        polygon.push_back(Point(17.0, 2.0));
        polygon.push_back(Point(11.5, 3.5));
        polygon.push_back(Point(10.0, 2.0));
        polygon.push_back(Point(6.0, 5.0));
        polygon.push_back(Point(8.0, 6.0));
        polygon.push_back(Point(9.0, 4.0));
        polygon.push_back(Point(15.0, 4.0));
        polygon.push_back(Point(20.0, 5.0));
        polygon.push_back(Point(9.0, 5.0));
        polygon.push_back(Point(10.9, 8.3));
        polygon.push_back(Point(9.0, 7.0));
        polygon.push_back(Point(11.0, 9.0));
        polygon.push_back(Point(8.0, 8.0));
        polygon.push_back(Point(8.0, 10.0));
        polygon.push_back(Point(6.0, 10.0));
        shortestPath = new SPV::ShortestPath();
        shortestPath->initialize(polygon);
        shortestPath->setPoint(0, 10.5, 11.0);
        shortestPath->setPoint(1, 8.0, 5.0);
        std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
        SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);
        SPV::EventSegment *eS = shortestPath->getFirstEvent();
        SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
        bC->calculateBendEvents();

        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(12,9));
        SPV::LineOfSight *loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(loS->getPointOnStartSide() , Point(9.75,12));
        QCOMPARE(loS->getPointOnEndSide(), Point(15, 5));
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(loS->getPointOnStartSide(), Point(9,12));
        QCOMPARE(loS->getPointOnEndSide(), Point(16, 5));
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), false);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 0);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(loS->getPointOnStartSide(), Point(9,12));
        QCOMPARE(loS->getPointOnEndSide(), Point(16, 5));
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(loS->getPointOnStartSide(), Point(6.5,12));
        QCOMPARE(loS->getPointOnEndSide(), Point(17, 5));
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 0);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(loS->getPointOnStartSide() , Point(11,9));
        QCOMPARE(loS->getPointOnEndSide(), Point(17, 5));
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(10.4773, 8.4773)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(18.7692, 5)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 0);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 1);
        QCOMPARE(eS->getExtraPointsOnStartSide().at(0), Point(11,9));
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(14,7));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(10.9, 8.3)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(18.7692, 5)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(10.7712, 8.0763)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(20, 5)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 0);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 2);
        QCOMPARE(eS->getExtraPointsOnStartSide().at(0), Point(11,9));
        QCOMPARE(gU.pointsAreEqual(eS->getExtraPointsOnStartSide().at(1), Point(10.9,8.3)), true);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(20,5));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(loS->getPointOnStartSide(), Point(14, 7));
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(21.0, 4.6667)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14.4, 7.8)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(21, 4.5)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 2);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), false);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), true);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(20,5));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14.4, 7.8)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(21, 4.5)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(14.75, 8.5)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(21, 4.3333)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 2);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(20,5));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(17, 7)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(21, 4.3333)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(17.8, 7.2)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(21, 4)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 2);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 1);
        QCOMPARE(eS->getExtraPointsOnStartSide().at(0), Point(17,7));
        QCOMPARE(eS->getStartSideLoSVisible(), false);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), true);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(20,5));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(17.8, 7.2)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(21, 4)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19.3529, 7.5882)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(20.3333, 3.6667)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 2);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 1);
        QCOMPARE(eS->getExtraPointsOnStartSide().at(0), Point(17,7));
        QCOMPARE(eS->getStartSideLoSVisible(), false);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), true);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(20,5));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19.3529, 7.5882)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(20.3333, 3.6667)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(20, 7.75)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(20, 3.5)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 2);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 1);
        QCOMPARE(eS->getExtraPointsOnStartSide().at(0), Point(17,7));
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(20,5));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(20, 7.75)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(20, 3.5)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 8)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(19.4, 3.2)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 2);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(20,5));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 8)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(19.4, 3.2)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 6)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(17, 2)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 3);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(20,5));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 6)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(17, 2)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 5.2)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(11.9231, 3.3846)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 3);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(15,4));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 5.2)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(11.9231, 3.3846)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 4.8571)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(11.5, 3.5)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 3);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(15,4));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 4.8571)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(8.56, 3.08)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 4)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(7.3333, 4)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 3);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(21, 4)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(7.3333, 4)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19.9243, 3.4621)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(7.2162, 4.0878)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 3);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), true);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(19.9243, 3.4621)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(7.2162, 4.0878)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(17.5714, 2.2857)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(6.7273, 4.4546)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 3);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 0);
        QCOMPARE(eS->getStartSideLoSVisible(), false);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), false);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(11.5, 3.5)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(6.7273, 4.4546)), true);
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnStartSide(), Point(11.25,3.25)), true);
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(6,5)), true);
        QCOMPARE(eS->hasSuccessor(), true);
        QCOMPARE(eS->hasPredecessor(), true);
        QCOMPARE(eS->getIndexOfLastSPPointOnStartSide(), 3);
        QCOMPARE(eS->getExtraPointsOnStartSide().size(), 1);
        QCOMPARE(gU.pointsAreEqual(eS->getExtraPointsOnStartSide().at(0), Point(11.5,3.5)), true);
        QCOMPARE(eS->getStartSideLoSVisible(), false);
        QCOMPARE(eS->getStartSideOnPolygonEdge(), true);

        eS = eS->getSuccessor();
        QCOMPARE(eS->getPivotPoint()->getPoint(), Point(9,4));
        loS = eS->getFirstLineOfSightFromStart();
        QCOMPARE(loS->getPointOnStartSide(), Point(11.25, 3.25));
        QCOMPARE(loS->getPointOnEndSide(), Point(6,5));
        loS = eS->getSecondLineOfSightFromStart();
        QCOMPARE(loS->getPointOnStartSide(), Point(10.5, 2.5));
        QCOMPARE(gU.pointsAreEqual(loS->getPointOnEndSide(), Point(7.3333, 5.6666)), true);
        QCOMPARE(eS->hasSuccessor(), false);
        QCOMPARE(eS->hasPredecessor(), true);
}

QTEST_APPLESS_MAIN(MinimumTest)

#include "tst_minimumtest.moc"
