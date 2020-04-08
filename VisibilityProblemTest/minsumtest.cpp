#include "minsumtest.h"

void MinSumTest::minSumTest1()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(5.0, 5.0), Point(9.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 2.1213), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(6.5,3.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(9,6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5,2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(11,8)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest2()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(9.0, 6.0), Point(5.0, 5.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 2.1213), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(6.5,3.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(9,6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5,2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(11,8)), true);
    QCOMPARE(min->getIsInDiscArea(), false);


    delete minSumCalculator;
}

void MinSumTest::minSumTest3()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(5.0, 5.0), Point(9.0, 5.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 1.7889), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5,5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.2,3.4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(3,6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(11,2)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 1.7889), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.8,3.4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(9,5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(3,2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(12,6.5)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest4()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(9.0, 5.0), Point(5.0, 5.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 1.7889), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.8,3.4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(9,5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(3,2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(12,6.5)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 1.7889), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5,5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.2, 3.4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(3,6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(11,2)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest5()
{
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(0.0, 0.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(1.0, 4.0), Point(11.1, 4.04));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(0);
    QCOMPARE(min->isMinSectorStart(), true);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.7264), true);
    Point startSideEdgeStart = min->getStartSideIntersectionOnEdge();
    Point startSideLoSStart = min->getStartSideIntersectionOnLoS();
    Point endSideEdgeStart = min->getEndSideIntersectionOnEdge();
    Point endSideLoSStart = min->getEndSideIntersectionOnLoS();
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    QCOMPARE(min->isMinSectorEnd(), true);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.7264), true);
    Point startSideEdgeEnd = min->getStartSideIntersectionOnEdge();
    Point startSideLoSEnd = min->getStartSideIntersectionOnLoS();
    Point endSideEdgeEnd = min->getEndSideIntersectionOnEdge();
    Point endSideLoSEnd = min->getEndSideIntersectionOnLoS();
    QCOMPARE(gU.pointsAreEqual(startSideLoSStart, startSideEdgeStart), true);
    QCOMPARE(gU.pointsAreEqual(startSideLoSEnd, startSideEdgeEnd), true);
    QCOMPARE(gU.isPointOnSegment(Segment(startSideEdgeStart, startSideEdgeEnd), Point(2.5986,0.6497)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(startSideLoSStart, startSideLoSEnd), Point(2.5986,0.6497)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(endSideEdgeStart, endSideEdgeEnd), Point(12,4.382)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(endSideLoSStart, endSideLoSEnd), Point(11.1052,4.0268)), true);

    delete minSumCalculator;
}

void MinSumTest::minSumTest6()
{
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(0.0, 0.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(11.1, 4.04), Point(1.0, 4.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(0);
    QCOMPARE(min->isMinSectorStart(), true);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.7264), true);
    Point startSideEdgeStart = min->getStartSideIntersectionOnEdge();
    Point startSideLoSStart = min->getStartSideIntersectionOnLoS();
    Point endSideEdgeStart = min->getEndSideIntersectionOnEdge();
    Point endSideLoSStart = min->getEndSideIntersectionOnLoS();
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    QCOMPARE(min->isMinSectorEnd(), true);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.7264), true);
    Point startSideEdgeEnd = min->getStartSideIntersectionOnEdge();
    Point startSideLoSEnd = min->getStartSideIntersectionOnLoS();
    Point endSideEdgeEnd = min->getEndSideIntersectionOnEdge();
    Point endSideLoSEnd = min->getEndSideIntersectionOnLoS();
    QCOMPARE(gU.pointsAreEqual(endSideLoSStart, endSideEdgeStart), true);
    QCOMPARE(gU.pointsAreEqual(endSideLoSEnd, endSideEdgeEnd), true);
    QCOMPARE(gU.isPointOnSegment(Segment(endSideEdgeStart, endSideEdgeEnd), Point(2.5986,0.6497)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(endSideLoSStart, endSideLoSEnd), Point(2.5986,0.6497)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(startSideEdgeStart, startSideEdgeEnd), Point(12,4.382)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(startSideLoSStart, startSideLoSEnd), Point(11.1052,4.0268)), true);

    delete minSumCalculator;
}

void MinSumTest::minSumTest7()
{
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 0.0));
    polygon.push_back(Point(0.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(0.9, 4.04), Point(11.0, 4.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(0);
    QCOMPARE(min->isMinSectorStart(), true);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.7264), true);
    Point startSideEdgeStart = min->getStartSideIntersectionOnEdge();
    Point startSideLoSStart = min->getStartSideIntersectionOnLoS();
    Point endSideEdgeStart = min->getEndSideIntersectionOnEdge();
    Point endSideLoSStart = min->getEndSideIntersectionOnLoS();
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    QCOMPARE(min->isMinSectorEnd(), true);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.7264), true);
    Point startSideEdgeEnd = min->getStartSideIntersectionOnEdge();
    Point startSideLoSEnd = min->getStartSideIntersectionOnLoS();
    Point endSideEdgeEnd = min->getEndSideIntersectionOnEdge();
    Point endSideLoSEnd = min->getEndSideIntersectionOnLoS();
    QCOMPARE(gU.pointsAreEqual(endSideLoSStart, endSideEdgeStart), true);
    QCOMPARE(gU.pointsAreEqual(endSideLoSEnd, endSideEdgeEnd), true);
    QCOMPARE(gU.isPointOnSegment(Segment(startSideEdgeStart, startSideEdgeEnd), Point(0.0,4.382)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(startSideLoSStart, startSideLoSEnd), Point(0.8948, 4.0268)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(endSideEdgeStart, endSideEdgeEnd), Point(9.4014, 0.6497)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(endSideLoSStart, endSideLoSEnd), Point(9.4014, 0.6497)), true);

    delete minSumCalculator;
}

void MinSumTest::minSumTest8()
{
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 0.0));
    polygon.push_back(Point(0.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(11.0, 4.0), Point(0.9, 4.04));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(0);
    QCOMPARE(min->isMinSectorStart(), true);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.7264), true);
    Point startSideEdgeStart = min->getStartSideIntersectionOnEdge();
    Point startSideLoSStart = min->getStartSideIntersectionOnLoS();
    Point endSideEdgeStart = min->getEndSideIntersectionOnEdge();
    Point endSideLoSStart = min->getEndSideIntersectionOnLoS();
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    QCOMPARE(min->isMinSectorEnd(), true);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.7264), true);
    Point startSideEdgeEnd = min->getStartSideIntersectionOnEdge();
    Point startSideLoSEnd = min->getStartSideIntersectionOnLoS();
    Point endSideEdgeEnd = min->getEndSideIntersectionOnEdge();
    Point endSideLoSEnd = min->getEndSideIntersectionOnLoS();
    QCOMPARE(gU.pointsAreEqual(startSideLoSStart, startSideEdgeStart), true);
    QCOMPARE(gU.pointsAreEqual(startSideLoSEnd, startSideEdgeEnd), true);
    QCOMPARE(gU.isPointOnSegment(Segment(endSideEdgeStart, endSideEdgeEnd), Point(0.0,4.382)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(endSideLoSStart, endSideLoSEnd), Point(0.8948, 4.0268)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(startSideEdgeStart, startSideEdgeEnd), Point(9.4014, 0.6497)), true);
    QCOMPARE(gU.isPointOnSegment(Segment(startSideLoSStart, startSideLoSEnd), Point(9.4014, 0.6497)), true);

    delete minSumCalculator;
}

void MinSumTest::minSumTest9()
{
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(6.0, 1.5));
    polygon.push_back(Point(0.0, 3.0));
    polygon.push_back(Point(0.0, 0.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(1.0, 4.0), Point(11.1, 4.04));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 4.8192), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5.2308, 1.6923)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.2308, 1.6923)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(12, 4.4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(11.1, 4.04)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest10()
{
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(6.0, 1.5));
    polygon.push_back(Point(0.0, 3.0));
    polygon.push_back(Point(0.0, 0.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(11.1, 4.04), Point(1.0, 4.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.valuesAreEqual(distance, 4.8192), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5.2308, 1.6923)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.2308, 1.6923)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(12, 4.4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(11.1, 4.04)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest11()
{
    polygon = Polygon();
    polygon.push_back(Point(1.0, 8.0));
    polygon.push_back(Point(4.0, 8.0));
    polygon.push_back(Point(5.0, 5.0));
    polygon.push_back(Point(6.0, 8.0));
    polygon.push_back(Point(7.0, 5.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(9.0, 5.0));
    polygon.push_back(Point(10.0, 8.0));
    polygon.push_back(Point(13.0, 8.0));
    polygon.push_back(Point(13.0, 3.0));
    polygon.push_back(Point(9.0, 3.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(6.0, 6.0));
    polygon.push_back(Point(5.0, 3.0));
    polygon.push_back(Point(1.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(4.0, 6.0), Point(10.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();
    std::vector<std::shared_ptr<SPV::PointOnShortestPath>> sP = minSumCalculator->getShortestPath();

    QCOMPARE((int) sP.size(), 7);
    QCOMPARE(sP.at(0)->getDistanceFromStartPoint(), 0.0);
    QCOMPARE(gU.valuesAreEqual(sP.at(0)->getDistanceFromEndPoint(), 8.4853), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(1)->getDistanceFromStartPoint(), 1.4142), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(1)->getDistanceFromEndPoint(), 7.0711), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(2)->getDistanceFromStartPoint(), 2.8284), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(2)->getDistanceFromEndPoint(), 5.6569), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(3)->getDistanceFromStartPoint(), 4.2426), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(3)->getDistanceFromEndPoint(), 4.2426), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(4)->getDistanceFromStartPoint(), 5.6569), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(4)->getDistanceFromEndPoint(), 2.8284), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(5)->getDistanceFromStartPoint(), 7.0711), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(5)->getDistanceFromEndPoint(), 1.4142), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(6)->getDistanceFromStartPoint(), 8.4853), true);
    QCOMPARE(gU.valuesAreEqual(sP.at(6)->getDistanceFromEndPoint(), 0), true);

    bool allEventsChecked = false;
    SPV::EventSegment *cS = minima.at(0)->getEventSegment();
    while(!allEventsChecked) {
        double distance = cS->getDistanceToLastVertex(true);
        bool value = distance == 0.0 || distance > 1;
        QCOMPARE(value, true);
        value = cS->getDistanceToLastVertex(false) == 0.0 || cS->getDistanceToLastVertex(false) > 1;
        QCOMPARE(value, true);
        if (cS->hasSuccessor()) {
            cS = cS->getSuccessor();
        } else {
            allEventsChecked = true;
        }
    }
    QCOMPARE((int) minima.size(), 6);

    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(2.0, 8.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(4.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5.5, 4.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.0, 5.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(3.0, 3.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.0, 5.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(6.5, 6.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(2);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5.5, 6.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(7.5, 4.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(7.0, 5)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(3);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(6.5, 4.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(7.0, 5.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(8.5, 6.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.0, 6.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(4);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(7.5, 6.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(11.0, 3.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(9.0, 5.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(5);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(8.5, 4.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(9.0, 5.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(12.0, 8.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(10.0, 6.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest12()
{
    polygon = Polygon();
    polygon.push_back(Point(1.0, 8.0));
    polygon.push_back(Point(4.0, 8.0));
    polygon.push_back(Point(5.0, 5.0));
    polygon.push_back(Point(6.0, 8.0));
    polygon.push_back(Point(7.0, 5.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(9.0, 5.0));
    polygon.push_back(Point(10.0, 8.0));
    polygon.push_back(Point(13.0, 8.0));
    polygon.push_back(Point(13.0, 3.0));
    polygon.push_back(Point(9.0, 3.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(6.0, 6.0));
    polygon.push_back(Point(5.0, 3.0));
    polygon.push_back(Point(1.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(10.0, 6.0), Point(4.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 6);
    auto min = minima.at(5);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(2.0, 8.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(4.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5.5, 4.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.0, 5.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(4);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(3.0, 3.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.0, 5.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(6.5, 6.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(3);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5.5, 6.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(7.5, 4.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(7.0, 5)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(2);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(6.5, 4.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(7.0, 5.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(8.5, 6.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.0, 6.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(7.5, 6.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(11.0, 3.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(9.0, 5.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(0);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(8.5, 4.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(9.0, 5.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(12.0, 8.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(10.0, 6.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest13()
{
    polygon = Polygon();
    polygon.push_back(Point(1.0, 8.0));
    polygon.push_back(Point(4.0, 8.0));
    polygon.push_back(Point(5.0, 5.0));
    polygon.push_back(Point(6.0, 8.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(9.0, 5.0));
    polygon.push_back(Point(10.0, 8.0));
    polygon.push_back(Point(13.0, 8.0));
    polygon.push_back(Point(13.0, 3.0));
    polygon.push_back(Point(9.0, 3.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(7.0, 1.0));
    polygon.push_back(Point(6.0, 6.0));
    polygon.push_back(Point(5.0, 3.0));
    polygon.push_back(Point(1.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(4.0, 6.0), Point(10.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 8.8191), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5.6667, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(7.25,2.25)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(7.0, 3.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 8.8191), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(6.75, 2.25)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(7.0, 3.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(8.3333, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.0, 6.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest14()
{
    polygon = Polygon();
    polygon.push_back(Point(1.0, 8.0));
    polygon.push_back(Point(4.0, 8.0));
    polygon.push_back(Point(5.0, 5.0));
    polygon.push_back(Point(6.0, 8.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(9.0, 5.0));
    polygon.push_back(Point(10.0, 8.0));
    polygon.push_back(Point(13.0, 8.0));
    polygon.push_back(Point(13.0, 3.0));
    polygon.push_back(Point(9.0, 3.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(7.0, 1.0));
    polygon.push_back(Point(6.0, 6.0));
    polygon.push_back(Point(5.0, 3.0));
    polygon.push_back(Point(1.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(10.0, 6.0), Point(4.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(1);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 8.8191), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5.6667, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(7.25,2.25)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(7.0, 3.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(0);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 8.8191), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(6.75, 2.25)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(7.0, 3.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(8.3333, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.0, 6.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest15()
{
    polygon = Polygon();
    polygon.push_back(Point(1.0, 8.0));
    polygon.push_back(Point(4.0, 8.0));
    polygon.push_back(Point(5.0, 5.0));
    polygon.push_back(Point(6.0, 8.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(9.0, 3.0));
    polygon.push_back(Point(10.0, 8.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(9.0, 1.0));
    polygon.push_back(Point(8.0, 4.0));
    polygon.push_back(Point(7.0, 1.0));
    polygon.push_back(Point(6.0, 6.0));
    polygon.push_back(Point(5.0, 3.0));
    polygon.push_back(Point(1.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(4.0, 6.0), Point(10.0, 4.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5.6667, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(7.3333,2.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(7.0, 3.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest16()
{
    polygon = Polygon();
    polygon.push_back(Point(1.0, 8.0));
    polygon.push_back(Point(4.0, 8.0));
    polygon.push_back(Point(5.0, 5.0));
    polygon.push_back(Point(6.0, 8.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(9.0, 3.0));
    polygon.push_back(Point(10.0, 8.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(9.0, 1.0));
    polygon.push_back(Point(8.0, 4.0));
    polygon.push_back(Point(7.0, 1.0));
    polygon.push_back(Point(6.0, 6.0));
    polygon.push_back(Point(5.0, 3.0));
    polygon.push_back(Point(1.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(10.0, 4.0), Point(4.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5.6667, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(7.3333,2.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(7.0, 3.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest17()
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

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(11.0, 11.0), Point(8.0, 5.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 11.5366), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(7.3333, 4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.0, 4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(19.0,4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(18.0, 4.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest18()
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

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(8.0, 5.0), Point(11.0, 11.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 11.5366), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(7.3333, 4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.0, 4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(19.0,4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(18.0, 4.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest19()
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
    polygon.push_back(Point(7.0, 2.0));
    polygon.push_back(Point(8.5,3.5));
    polygon.push_back(Point(7.0, 3.5));
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

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(10.5, 11.0), Point(8.0, 5.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 13.6530), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(21.0, 4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(20.0, 4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(6.6667,4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.0, 4.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest20()
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
    polygon.push_back(Point(7.0, 2.0));
    polygon.push_back(Point(8.5,3.5));
    polygon.push_back(Point(7.0, 3.5));
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

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(8.0, 5.0), Point(10.5, 11.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 13.6530), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(21.0, 4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(20.0, 4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(6.6667,4.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.0, 4.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest21()
{
    polygon = Polygon();
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

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(17.0, 11.0), Point(17.0, 4.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 6.7317), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(17.6667,12.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(17,11.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(14.3333, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(14.3333, 7.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest22()
{
    polygon = Polygon();
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

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(17.0, 4.0), Point(17.0, 11.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 6.7317), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(17.6667,12.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(17,11.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(14.3333, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(14.3333, 7.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest23()
{
    polygon = Polygon();
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

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(11.0, 11.0), Point(19.0, 11.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 6.6645), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(13.6,3.8)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(15.28,6.04)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(19.75,12.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(19.0,11.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest24()
{
    polygon = Polygon();
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

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(19.0, 11.0), Point(11.0, 11.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 6.6645), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(13.6,3.8)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(15.28,6.04)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(19.75,12.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(19.0,11.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest25()
{
    polygon = Polygon();
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 6.0));
    polygon.push_back(Point(6.0, 4.0));
    polygon.push_back(Point(8.0, 4.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(10.0, 6.0));
    polygon.push_back(Point(11.0, 3.0));
    polygon.push_back(Point(3.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(5.0, 5.0), Point(9.0, 5.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 2), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(9, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(3.3333, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(10.6667, 4)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest26()
{
    polygon = Polygon();
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 6.0));
    polygon.push_back(Point(6.0, 4.0));
    polygon.push_back(Point(8.0, 4.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(10.0, 6.0));
    polygon.push_back(Point(11.0, 3.0));
    polygon.push_back(Point(3.0, 3.0));

    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(9.0, 5.0), Point(5.0, 5.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 2), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(9, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(3.3333, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(10.6667, 4)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest27()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 7.0));
    polygon.push_back(Point(6.0, 7.0));
    polygon.push_back(Point(7.0, 5.0));
    polygon.push_back(Point(9.0, 4.0));
    polygon.push_back(Point(11.0, 5.0));
    polygon.push_back(Point(12.0, 7.0));
    polygon.push_back(Point(15.0, 7.0));
    polygon.push_back(Point(15.0, 2.0));
    polygon.push_back(Point(3.0, 2.0));
    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(6.0, 6.0), Point(12.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.57771), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.8, 5.6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(10.6, 3.2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(3, 7)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(13, 2)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.57771), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(7.4, 3.2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(12.2, 5.6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5, 2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(15, 7)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest28()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 7.0));
    polygon.push_back(Point(6.0, 7.0));
    polygon.push_back(Point(7.0, 5.0));
    polygon.push_back(Point(9.0, 4.0));
    polygon.push_back(Point(11.0, 5.0));
    polygon.push_back(Point(12.0, 7.0));
    polygon.push_back(Point(15.0, 7.0));
    polygon.push_back(Point(15.0, 2.0));
    polygon.push_back(Point(3.0, 2.0));
    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(12.0, 6.0), Point(6.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 2);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.57771), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(7.4, 3.2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(12.2, 5.6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5, 2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(15, 7)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    min = minima.at(1);
    distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 3.57771), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.8, 5.6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(10.6, 3.2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(3, 7)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(13, 2)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest29()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 7.0));
    polygon.push_back(Point(8.0, 7.0));
    polygon.push_back(Point(8.0, 5.0));
    polygon.push_back(Point(6.0, 4.0));
    polygon.push_back(Point(11.0, 4.0));
    polygon.push_back(Point(9.0, 5.0));
    polygon.push_back(Point(9.0, 7.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(14.0, 2.0));
    polygon.push_back(Point(3.0, 2.0));
    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(6.0, 6.0), Point(11.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 4), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(6, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(11, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(3, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(14, 4)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}

void MinSumTest::minSumTest30()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 7.0));
    polygon.push_back(Point(8.0, 7.0));
    polygon.push_back(Point(8.0, 5.0));
    polygon.push_back(Point(6.0, 4.0));
    polygon.push_back(Point(11.0, 4.0));
    polygon.push_back(Point(9.0, 5.0));
    polygon.push_back(Point(9.0, 7.0));
    polygon.push_back(Point(14.0, 7.0));
    polygon.push_back(Point(14.0, 2.0));
    polygon.push_back(Point(3.0, 2.0));
    minSumCalculator = new SPV::MinSumCalculator(polygon, Point(11.0, 6.0), Point(6.0, 6.0));
    minSumCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minSumCalculator->getAllMinima();

    QCOMPARE((int) minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 4), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(6, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(11, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(3, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(14, 4)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minSumCalculator;
}
