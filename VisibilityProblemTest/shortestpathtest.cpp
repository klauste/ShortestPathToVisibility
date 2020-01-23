#include "shortestpathtest.h"

ShortestPathTest::ShortestPathTest()
{

}

ShortestPathTest::~ShortestPathTest()
{

}

void ShortestPathTest::shortestPathTest1()
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
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    QCOMPARE(sP.size(), 3);
    QCOMPARE(Point(5.0, 6.0), sP.at(0)->getPoint());
    QCOMPARE(Point(9.0, 5.0), sP.at(2)->getPoint());
    QCOMPARE(Point(7.0, 4.0), sP.at(1)->getPoint());
    delete shortestPath;
}

void ShortestPathTest::shortestPathTest2()
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
    delete shortestPath;
}

void ShortestPathTest::shortestPathTest3()
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
    delete shortestPath;
}

void ShortestPathTest::shortestPathTest4()
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
    delete shortestPath;
}


void ShortestPathTest::shortestPathTest5()
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
    delete shortestPath;
}

void ShortestPathTest::shortestPathTest6()
{
    polygon = Polygon();
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
    delete shortestPath;
}

void ShortestPathTest::shortestPathTest7()
{
    polygon = Polygon();
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
    delete shortestPath;
}

void ShortestPathTest::shortestPathTest8()
{
    polygon = Polygon();
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
    eC->setCurrentSegmentOrderFromLeftToRight(false);
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
    segments.clear();
}

void ShortestPathTest::shortestPathTest9()
{
    polygon = Polygon();
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
    eC->setCurrentSegmentOrderFromLeftToRight(false);
    std::vector<SPV::SweptSegment*> segments = eC->getSegmentsForFinalPoint(false);
    QCOMPARE(segments.size(), 1);
    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->getLeftPoint(), Point(10.5,12));
    QCOMPARE(segments.at(0)->getRightPoint(), Point(9,12));

    segments.clear();
    eC->setCurrentSegmentOrderFromLeftToRight(true);
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
    segments.clear();
}

void ShortestPathTest::shortestPathTest10()
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
    delete shortestPath;
}

void ShortestPathTest::shortestPathTest11()
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
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 19.0, 11.0);
    shortestPath->setPoint(1, 11.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();
    SPV::PathAndBoundaryEventCalculator *eC = new SPV::PathAndBoundaryEventCalculator(sP);
    eC->setCurrentSegmentOrderFromLeftToRight(false);
    std::vector<SPV::SweptSegment*> segments = eC->getSegmentsForFinalPoint(false);
    QCOMPARE(segments.size(), 1);
    QCOMPARE(segments.at(0)->leftPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->rightPointIsPolygonVertex(), false);
    QCOMPARE(segments.at(0)->getLeftPoint(), Point(10.5,12));
    QCOMPARE(segments.at(0)->getRightPoint(), Point(9,12));

    segments.clear();
    eC->setCurrentSegmentOrderFromLeftToRight
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
    delete shortestPath;
}

void ShortestPathTest::shortestPathTest12()
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
    QCOMPARE(eS->hasPredecessor(), true);
    delete shortestPath;
}

void ShortestPathTest::shortestPathTest13()
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
    shortestPath = new SPV::ShortestPath();
    shortestPath->initialize(polygon);
    shortestPath->setPoint(0, 8.0, 5.0);
    shortestPath->setPoint(1, 11.0, 11.0);
    std::vector<SPV::PointOnShortestPath*> sP = shortestPath->calculateShortestPath();

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
    QCOMPARE(eS->hasPredecessor(), true);
    delete shortestPath;
}

