#include "cgalgeometryconnector.h"

bool CGALGeometryConnector::shouldClosePolyline(QPointF p)
{
    if (polygon.size() < 3) {
        return false;
    }
    Point firstPointInPolygon = polygon.vertex(0);
    Point currentCgalPoint = Point(p.x(), p.y());
    double distance = CGAL::squared_distance(currentCgalPoint, firstPointInPolygon);

    return (distance < minSquaredDistanceToStartPoint);
}

void CGALGeometryConnector::addPointToCGALPolygon(QPointF p)
{
    Point currentCgalPoint = Point(p.x(), p.y());
    if (polygon.size() > 0) {
        addedSegments.push_back(Segment(polygon.vertex(polygon.size() - 1), currentCgalPoint));
    }
    polygon.push_back(currentCgalPoint);
}

bool CGALGeometryConnector::isPointInPolygon(QPointF p)
{
    Point pointToCheck = Point(p.x(), p.y());
    return (polygon.bounded_side(pointToCheck) == CGAL::ON_BOUNDED_SIDE);
}

void CGALGeometryConnector::handleFinalPoint(QPointF p, bool isStart)
{
    if (isStart) {
        startPoint = Point(p.x(), p.y());
    } else {
        endPoint = Point(p.x(), p.y());
        calculateMinima();
    }
}

bool CGALGeometryConnector::doSegmentsIntersect(QPointF p)
{
    if (polygon.size() < 2) {
        return false;
    }
    Point lastPointInPolygon = polygon.vertex(polygon.size() - 1);
    Segment newSegment = Segment(lastPointInPolygon, Point(p.x(), p.y()));

    for (auto &currentSegment : addedSegments) {
        Point currentEndPoint = currentSegment.target();
        bool checkIntersect = currentEndPoint != lastPointInPolygon;

        if (checkIntersect && CGAL::do_intersect(currentSegment, newSegment)) {
            return true;
        }
    }
    return false;
}

void CGALGeometryConnector::reset()
{
    if (minMaxCalculator) {
        delete minMaxCalculator;
        minMaxCalculator = nullptr;
    }
    if (minSumCalculator) {
        delete minSumCalculator;
        minSumCalculator = nullptr;
    }
    polygon.clear();
    addedSegments.clear();
    pathEvents.clear();
    boundaryEvents.clear();
    bendEvents.clear();
    minMaxMinima.clear();
    minSumMinima.clear();
    sweptSegments.clear();
    shortestPathGraph.clear();
}

void CGALGeometryConnector::calculateMinima()
{
    unsigned i;
    minMaxCalculator = new SPV::MinMaxCalculator(polygon, startPoint, endPoint);
    minMaxCalculator->calculateMinima();
    firstSegment = minMaxCalculator->getFirstEventSegment();
    shortestPath = minMaxCalculator->getShortestPath();
    minSumCalculator = new SPV::MinSumCalculator(polygon, startPoint, endPoint);
    minSumCalculator->calculateMinima();

    for (i = 0; i < shortestPath.size() - 1; i++) {
        Point currentPoint = shortestPath.at(i)->getPoint();
        Point nextPoint = shortestPath.at(i + 1)->getPoint();
        QLineF *newLine = new QLineF(currentPoint.x(), currentPoint.y(), nextPoint.x(), nextPoint.y());
        shortestPathGraph.push_back(newLine);
    }
    setEvents();
    setMinima();
}

void CGALGeometryConnector::setMinima()
{
    unsigned i;
    std::vector<std::shared_ptr<SPV::Minimum>> allMinima = minMaxCalculator->getAllMinima();
    for (i = 0; i < allMinima.size(); i++) {
        auto min = allMinima.at(i);
        double minValue = min->getDistance();
        Point p1 = min->getStartSideIntersectionOnEdge();
        Point p2 = min->getEndSideIntersectionOnEdge();
        QLineF *loS = new QLineF(p1.x(), p1.y(), p2.x(), p2.y());
        p1 = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), true);
        p2 = min->getStartSideIntersectionOnLoS();
        QLineF *lineOnStartSide = new QLineF(p1.x(), p1.y(), p2.x(), p2.y());
        p1 = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), false);
        p2 = min->getEndSideIntersectionOnLoS();
        QLineF *lineOnEndSide = new QLineF(p1.x(), p1.y(), p2.x(), p2.y());
        minData *newMin = new minData(loS, lineOnStartSide, lineOnEndSide, minValue);
        if (min->getIsInDiscArea()) {
            newMin->hasRadius = true;
            newMin->radius = min->getDiscRadius();
            Point cP;
            if (min->isDiscOnStartSide()) {
                cP = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), true);
            } else {
                cP = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), false);
            }
            newMin->centerPoint = QPointF(cP.x(), cP.y());
        }
        minMaxMinima.push_back(newMin);

    }

    allMinima.clear();
    allMinima = minSumCalculator->getAllMinima();
    for (i = 0; i < allMinima.size(); i++) {
        auto min = allMinima.at(i);
        double minValue = min->getDistance();
        Point p1 = min->getStartSideIntersectionOnEdge();
        Point p2 = min->getEndSideIntersectionOnEdge();
        QLineF *loS = new QLineF(p1.x(), p1.y(), p2.x(), p2.y());
        p1 = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), true);
        p2 = min->getStartSideIntersectionOnLoS();
        QLineF *lineOnStartSide = new QLineF(p1.x(), p1.y(), p2.x(), p2.y());
        p1 = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), false);
        p2 = min->getEndSideIntersectionOnLoS();
        QLineF *lineOnEndSide = new QLineF(p1.x(), p1.y(), p2.x(), p2.y());
        minSumMinima.push_back(new minData(loS, lineOnStartSide, lineOnEndSide, minValue));
    }
}

void CGALGeometryConnector::setEvents()
{
    SPV::EventSegment *currentSegment = firstSegment;
    Point furthestPointStartSide, furthestPointEndSide;
    SPV::EventSegment *previousSegment;
    Point pivotPoint;
    bool allEventsHandled = false;

    while (!allEventsHandled) {
        pivotPoint = currentSegment->getPivotPoint()->getPoint();
        auto currentLos = currentSegment->getFirstLineOfSightFromStart();
        furthestPointStartSide = currentLos->getPointOnStartSide();
        furthestPointEndSide = currentLos->getPointOnEndSide();
        if (currentSegment->hasPredecessor()) {
            previousSegment =  currentSegment->getPredecessor();
            auto previousLos = previousSegment->getSecondLineOfSightFromStart();
            if (CGAL::squared_distance(previousLos->getPointOnStartSide(), pivotPoint) >
                    CGAL::squared_distance(furthestPointStartSide, pivotPoint)) {
                furthestPointStartSide = previousLos->getPointOnStartSide();
            }
            if (CGAL::squared_distance(previousLos->getPointOnEndSide(), pivotPoint) >
                    CGAL::squared_distance(furthestPointEndSide, pivotPoint)) {
                furthestPointEndSide = previousLos->getPointOnEndSide();
            }
        }
        switch (currentLos->getEventType()) {
            case PATH: pathEvents.push_back(new QLineF(
                furthestPointStartSide.x(),
                furthestPointStartSide.y(),
                furthestPointEndSide.x(),
                furthestPointEndSide.y()
            ));
            break;
            case BOUNDARY: boundaryEvents.push_back(new QLineF(
                furthestPointStartSide.x(),
                furthestPointStartSide.y(),
                furthestPointEndSide.x(),
                furthestPointEndSide.y()
            ));
            break;
            case BEND: bendEvents.push_back(new QLineF(
                furthestPointStartSide.x(),
                furthestPointStartSide.y(),
                furthestPointEndSide.x(),
                furthestPointEndSide.y()
            ));
        }
        if (currentSegment->hasSuccessor()) {
            currentSegment = currentSegment->getSuccessor();
        } else {
            allEventsHandled = true;
        }
    }
    // The last event is a path event
    auto lastLos = currentSegment->getSecondLineOfSightFromStart();
    pathEvents.push_back(new QLineF(
        lastLos->getPointOnStartSide().x(),
        lastLos->getPointOnStartSide().y(),
        lastLos->getPointOnEndSide().x(),
        lastLos->getPointOnEndSide().y()
    ));
}
