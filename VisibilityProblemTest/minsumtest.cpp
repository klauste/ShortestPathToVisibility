#include "minsumtest.h"

MinSumTest::MinSumTest()
{

}

MinSumTest::~MinSumTest()
{

}

void MinSumTest::minSumTest1()
{
    return;
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
    shortestPath->setPoint(0, 5.0, 5.0);
    shortestPath->setPoint(1, 9.0, 6.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    SPV::MinSumCalculator mS = SPV::MinSumCalculator(eS, sP);
    mS.calculateMinima();
    std::vector<SPV::Minimum*> minima = mS.getAllMinima();
    QCOMPARE(minima.size(), 1);
    SPV::Minimum *min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 2.1213), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(6.5,3.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(9,6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5,2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(11,8)), true);
    QCOMPARE(min->getIsInDiscArea(), false);
}

void MinSumTest::minSumTest2()
{
    return;
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
    shortestPath->setPoint(0, 9.0, 6.0);
    shortestPath->setPoint(1, 5.0, 5.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    SPV::MinSumCalculator mS = SPV::MinSumCalculator(eS, sP);
    mS.calculateMinima();
    std::vector<SPV::Minimum*> minima = mS.getAllMinima();
    QCOMPARE(minima.size(), 1);
    SPV::Minimum *min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 2.1213), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(6.5,3.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(9,6)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5,2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(11,8)), true);
    QCOMPARE(min->getIsInDiscArea(), false);
}

void MinSumTest::minSumTest3()
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
    shortestPath->setPoint(1, 9.0, 5.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    SPV::MinSumCalculator mS = SPV::MinSumCalculator(eS, sP);
    mS.calculateMinima();
    std::vector<SPV::Minimum*> minima = mS.getAllMinima();
    QCOMPARE(minima.size(), 2);
    SPV::Minimum *min = minima.at(0);
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
    QCOMPARE(min->getIsInDiscArea(), false);*/
}

void MinSumTest::minSumTest4()
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
    shortestPath->setPoint(0, 9.0, 5.0);
    shortestPath->setPoint(1, 5.0, 5.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    SPV::MinSumCalculator mS = SPV::MinSumCalculator(eS, sP);
    mS.calculateMinima();
    std::vector<SPV::Minimum*> minima = mS.getAllMinima();
    QCOMPARE(minima.size(), 2);
    SPV::Minimum *min = minima.at(0);
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
    QCOMPARE(min->getIsInDiscArea(), false);*/
}

void MinSumTest::minSumTest5()
{
    return;
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(0.0, 0.0));

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 1.0, 4.0);
    shortestPath->setPoint(1, 11.1, 4.04);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    SPV::MinSumCalculator mS = SPV::MinSumCalculator(eS, sP);
    mS.calculateMinima();
    std::vector<SPV::Minimum*> minima = mS.getAllMinima();
    QCOMPARE(minima.size(), 2);

    SPV::Minimum *min = minima.at(0);
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
}

void MinSumTest::minSumTest6()
{
    return;
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(0.0, 0.0));

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 11.10, 4.040);
    shortestPath->setPoint(1, 1.0, 4.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator mS = SPV::MinSumCalculator(eS, sP);
    mS.calculateMinima();
    std::vector<SPV::Minimum*> minima = mS.getAllMinima();
    QCOMPARE(minima.size(), 2);

    SPV::Minimum *min = minima.at(0);
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
}

void MinSumTest::minSumTest7()
{
    return;
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 0.0));
    polygon.push_back(Point(0.0, 3.0));

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 0.9, 4.04);
    shortestPath->setPoint(1, 11.0, 4.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator mS = SPV::MinSumCalculator(eS, sP);
    mS.calculateMinima();
    std::vector<SPV::Minimum*> minima = mS.getAllMinima();
    QCOMPARE(minima.size(), 2);

    SPV::Minimum *min = minima.at(0);
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
}

void MinSumTest::minSumTest8()
{
    return;
    polygon = Polygon();
    polygon.push_back(Point(0.0, 6.0));
    polygon.push_back(Point(4.0, 6.0));
    polygon.push_back(Point(6.0, 2.0));
    polygon.push_back(Point(8.0, 6.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 0.0));
    polygon.push_back(Point(0.0, 3.0));

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 11.0, 4.0);
    shortestPath->setPoint(1, 0.9, 4.04);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator mS = SPV::MinSumCalculator(eS, sP);
    mS.calculateMinima();
    std::vector<SPV::Minimum*> minima = mS.getAllMinima();
    QCOMPARE(minima.size(), 2);

    SPV::Minimum *min = minima.at(0);
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
}

void MinSumTest::minSumTest9()
{
    return;
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

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 1.0, 4.0);
    shortestPath->setPoint(1, 11.1, 4.04);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    SPV::MinSumCalculator *mS = new SPV::MinSumCalculator(eS, sP);
    mS->calculateMinima();
    std::vector<SPV::Minimum*> minima = mS->getAllMinima();
    QCOMPARE(minima.size(), 1);

    SPV::Minimum *min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 4.8192), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5.2308, 1.6923)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.2308, 1.6923)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(12, 4.4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(11.1, 4.04)), true);
    QCOMPARE(min->getIsInDiscArea(), false);
}

void MinSumTest::minSumTest10()
{
    return;
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

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 11.10, 4.040);
    shortestPath->setPoint(1, 1.0, 4.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator mS = SPV::MinSumCalculator(eS, sP);
    mS.calculateMinima();
    std::vector<SPV::Minimum*> minima = mS.getAllMinima();
    QCOMPARE(minima.size(), 1);

    SPV::Minimum *min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.valuesAreEqual(distance, 4.8192), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5.2308, 1.6923)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.2308, 1.6923)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(12, 4.4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(11.1, 4.04)), true);
    QCOMPARE(min->getIsInDiscArea(), false);
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

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 4.0, 6.0);
    shortestPath->setPoint(1, 10.0, 6.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    QCOMPARE(sP.size(), 7);
    QCOMPARE(sP.at(0)->getDistanceFromStartPoint(), 0);
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

    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator *mS = new SPV::MinSumCalculator(eS, sP);
    mS->calculateMinima();
    std::vector<SPV::Minimum*> minima = mS->getAllMinima();
    bool allEventsChecked = false;
    SPV::EventSegment *cS = eS;
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
    QCOMPARE(minima.size(), 6);

    SPV::Minimum *min = minima.at(0);
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

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 10.0, 6.0);
    shortestPath->setPoint(1, 4.0, 6.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator *mS = new SPV::MinSumCalculator(eS, sP);
    mS->calculateMinima();
    std::vector<SPV::Minimum*> minima = mS->getAllMinima();
    QCOMPARE(minima.size(), 6);

    SPV::Minimum *min = minima.at(5);
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

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 4.0, 6.0);
    shortestPath->setPoint(1, 10.0, 6.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator *mS = new SPV::MinSumCalculator(eS, sP);
    mS->calculateMinima();
    std::vector<SPV::Minimum*> minima = mS->getAllMinima();
    QCOMPARE(minima.size(), 2);

    SPV::Minimum *min = minima.at(0);
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

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 10.0, 6.0);
    shortestPath->setPoint(1, 4.0, 6.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator *mS = new SPV::MinSumCalculator(eS, sP);
    mS->calculateMinima();
    std::vector<SPV::Minimum*> minima = mS->getAllMinima();
    QCOMPARE(minima.size(), 2);

    SPV::Minimum *min = minima.at(1);
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

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 4.0, 6.0);
    shortestPath->setPoint(1, 10.0, 4.0);

    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator *mS = new SPV::MinSumCalculator(eS, sP);
    mS->calculateMinima();
    std::vector<SPV::Minimum*> minima = mS->getAllMinima();
    QCOMPARE(minima.size(), 1);

    SPV::Minimum *min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5.6667, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(7.3333,2.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(7.0, 3.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);
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

    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 10.0, 4.0);
    shortestPath->setPoint(1, 4.0, 6.0);

    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::EventSegment *eS = shortestPath->getFirstEvent();
    SPV::BendEventCalculator *bC = new SPV::BendEventCalculator(eS, sP);
    bC->calculateBendEvents();
    eS = bC->getFirstEventSegment();
    SPV::MinSumCalculator *mS = new SPV::MinSumCalculator(eS, sP);
    mS->calculateMinima();
    std::vector<SPV::Minimum*> minima = mS->getAllMinima();
    QCOMPARE(minima.size(), 1);

    SPV::Minimum *min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqual(distance, 7.0711), true);
    QCOMPARE(min->isMinSectorStart(), false);
    QCOMPARE(min->isMinSectorEnd(), false);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5.6667, 7.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(6.0, 6.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(7.3333,2.0)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(7.0, 3.0)), true);
    QCOMPARE(min->getIsInDiscArea(), false);
    sP.clear();
    delete bC;
    delete mS;
}
