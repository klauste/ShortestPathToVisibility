#include "minmaxtest.h"
MinMaxTest::MinMaxTest()
{

}

MinMaxTest::~MinMaxTest()
{

}

void MinMaxTest::minMaxTest1()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));
    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(5.0, 5.0), Point(9.0, 5.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 1), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(9, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(3,4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(12, 4)), true);
    QCOMPARE(min->getIsInDiscArea(), false);
    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest2()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));
    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(5.0, 5.0), Point(9.0, 5.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 1), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5,4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(9, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(3,4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(12, 4)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest3()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));
    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(5.0, 5.0), Point(9.0, 5.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 1.455213), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.3529, 3.5882)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(9.3529, 4.5882)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(3,3)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(12, 5.25)), true);
    QCOMPARE(min->getIsInDiscArea(), false);
    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest4()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(9.0, 5.0), Point(5.0, 5.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 1.455213), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.3529, 3.5882)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(9.3529, 4.5882)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(3,3)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(12, 5.25)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest5()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(6.5, 5.0), Point(8.5, 7.5));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 1.11803399), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(7,4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.5, 7.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(6.1429, 2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(8.7143, 8)), true);
    QCOMPARE(min->getIsInDiscArea(), true);
    QCOMPARE(gU.valuesAreEqualHighPrecision(min->getDiscRadius(), 1.11803399), true);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest6()
{
    polygon = Polygon();
    polygon.push_back(Point(3.0, 8.0));
    polygon.push_back(Point(3.0, 2.0));
    polygon.push_back(Point(12.0, 2.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(8.5, 7.5), Point(6.5, 5.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 1.11803399), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(7,4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.5, 7.5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(6.1429, 2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(8.7143, 8)), true);
    QCOMPARE(min->getIsInDiscArea(), true);
    QCOMPARE(gU.valuesAreEqualHighPrecision(min->getDiscRadius(), 1.11803399), true);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest7()
{
    polygon = Polygon();
    polygon.push_back(Point(2.0, 8.0));
    polygon.push_back(Point(2.0, 6.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(5.0, 6.0), Point(9.0, 6.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 2.0275875), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.3333,4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.6667, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5.3333, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(8.6667, 4)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest8()
{
    polygon = Polygon();
    polygon.push_back(Point(2.0, 8.0));
    polygon.push_back(Point(2.0, 6.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(12.0, 6.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(9.0, 6.0), Point(5.0, 6.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 2.0275875), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.3333,4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.6667, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5.3333, 4)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(8.6667, 4)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest9()
{
    polygon = Polygon();
    polygon.push_back(Point(2.0, 8.0));
    polygon.push_back(Point(2.0, 7.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(5.0, 6.0), Point(9.0, 6.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 2.07111585), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.6907,4.0475)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.925,3.9302)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(5.6907,4.0475)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(12, 3.8188)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest10()
{
    polygon = Polygon();
    polygon.push_back(Point(2.0, 8.0));
    polygon.push_back(Point(2.0, 7.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(12.0, 3.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(9.0, 6.0), Point(5.0, 6.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 2.07111585), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.6907,4.0475)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.925,3.9302)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(5.6907,4.0475)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(12, 3.8188)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest11()
{
    polygon = Polygon();
    polygon.push_back(Point(2.0, 8.0));
    polygon.push_back(Point(2.0, 3.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(12.0, 7.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(9.0, 6.0), Point(5.0, 6.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 2.07111585), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(5.075, 3.9302)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(8.3093,4.0475)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(2, 3.8188)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(8.3093, 4.0475)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest12()
{
    polygon = Polygon();
    polygon.push_back(Point(2.0, 8.0));
    polygon.push_back(Point(2.0, 3.0));
    polygon.push_back(Point(7.0, 3.0));
    polygon.push_back(Point(12.0, 7.0));
    polygon.push_back(Point(12.0, 8.0));
    polygon.push_back(Point(8.0, 8.0));
    polygon.push_back(Point(7.0, 4.0));
    polygon.push_back(Point(6.0, 8.0));

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(9.0, 6.0), Point(5.0, 6.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 2.07111585), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(5.075, 3.9302)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(8.3093,4.0475)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(2, 3.8188)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(8.3093, 4.0475)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest13()
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

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(11.0, 11.0), Point(19.0, 11.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 4.11540798), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(11.0959, 6.8858)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(18.0222,7.0471)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(10.4678, 6.87107)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(18.9316, 7.0683)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest14()
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

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(19.0, 11.0), Point(11.0, 11.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 4.11540798), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(11.0959, 6.8858)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(18.0222,7.0471)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(10.4678, 6.87107)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(18.9316, 7.0683)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest15()
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

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(17.0, 11.0), Point(17.0, 4.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 5.2474648), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(13.5746, 7.6322)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(12.4569, 6.4025)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(13.5746, 7.6322)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(12.3151, 6.2465)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest16()
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

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(17.0, 4.0), Point(17.0, 11.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 5.2474648), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(13.5746, 7.6322)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(12.4569, 6.4025)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(13.5746, 7.6322)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(12.3151, 6.2465)), true);
    QCOMPARE(min->getIsInDiscArea(), false);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest17()
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

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(10.5, 11.0), Point(8.0, 5.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 11.65298245), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(20, 5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(11.9231, 3.3846)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(21, 5.2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(11.9231, 3.3846)), true);
    QCOMPARE(min->getIsInDiscArea(), true);
    QCOMPARE(gU.valuesAreEqual(min->getDiscRadius(), 7.2507), true);

    delete minMaxCalculator;
}

void MinMaxTest::minMaxTest18()
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

    minMaxCalculator = new SPV::MinMaxCalculator(polygon, Point(8.0, 5.0), Point(10.5, 11.0));
    minMaxCalculator->calculateMinima();
    std::vector<std::shared_ptr<SPV::Minimum>> minima = minMaxCalculator->getAllMinima();

    QCOMPARE(minima.size(), 1);
    auto min = minima.at(0);
    double distance = min->getDistance();
    QCOMPARE(gU.valuesAreEqualHighPrecision(distance, 11.65298245), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnLoS(), Point(20, 5)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnLoS(), Point(11.9231, 3.3846)), true);
    QCOMPARE(gU.pointsAreEqual(min->getEndSideIntersectionOnEdge(), Point(21, 5.2)), true);
    QCOMPARE(gU.pointsAreEqual(min->getStartSideIntersectionOnEdge(), Point(11.9231, 3.3846)), true);
    QCOMPARE(min->getIsInDiscArea(), true);
    QCOMPARE(gU.valuesAreEqual(min->getDiscRadius(), 7.2507), true);

    delete minMaxCalculator;
}
