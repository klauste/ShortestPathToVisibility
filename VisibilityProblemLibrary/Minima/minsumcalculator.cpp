#include "Minima/minsumcalculator.h"

void SPV::MinSumCalculator::calculateMinima()
{
    bool allSegmentsHandled = false;
    currentEventSegment = firstEventSegment;

    while (!allSegmentsHandled) {
        // First possiblity: minimum is at pivot point
        bool minAtPivotPoint = handleLocalMinimumAtPivotPoint();
        if (!minAtPivotPoint) {
            // Second possibility: the direct path to the line of sight is free on both sides
            if (currentEventSegment->isLoSVisible(true) && currentEventSegment->isLoSVisible(false)) {
                handleLocalMinimaWithBothPathsFree();
            // Third possibility: the direct path to the line of sight is obstructed on both sides
            } else if (!currentEventSegment->isLoSVisible(true) && !currentEventSegment->isLoSVisible(false)) {
                handleLocalMinimaWithBothPathsBlocked();
            // The fourth possibility: the direct path to the line of sight is obstruced on one side
            } else {
                handleLocalMinimaWithOnePathBlocked();
            }
        }
        if (currentEventSegment->hasSuccessor()) {
            currentEventSegment = currentEventSegment->getSuccessor();
        } else {
            allSegmentsHandled = true;
        }
    }
}

void SPV::MinSumCalculator::handleLocalMinimaWithBothPathsFree()
{
    double totalDistance = currentEventSegment->getDistanceToLastVertex(true) +
            currentEventSegment->getDistanceToLastVertex(false);
    Point intersectionStartSideFirstLoS = getIntersectionPointOnLoS(currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide(), true);
    Point intersectionEndSideFirstLoS = getIntersectionPointOnLoS(currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide(), false);

    double extraDistanceOnFirstLine = getDistanceToIntersectionPoint(intersectionStartSideFirstLoS, true) +
            getDistanceToIntersectionPoint(intersectionEndSideFirstLoS, false);

    Point intersectionStartSideSecondLoS = getIntersectionPointOnLoS(currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide(), true);
    Point intersectionEndSideSecondLoS = getIntersectionPointOnLoS(currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide(), false);
    double extraDistanceOnSecondLine = getDistanceToIntersectionPoint(intersectionStartSideSecondLoS, true) +
            getDistanceToIntersectionPoint(intersectionEndSideSecondLoS, false);

    if (gU.isLargerOrEqual(extraDistanceOnSecondLine, extraDistanceOnFirstLine )) {
        handleNewGlobalMinimum(
            totalDistance + extraDistanceOnFirstLine,
            intersectionStartSideFirstLoS,
            intersectionEndSideFirstLoS,
            getFurthestPointOnBoundary(true, true),
            getFurthestPointOnBoundary(false, true)
        );
    }
    if (gU.isLargerOrEqual(extraDistanceOnFirstLine, extraDistanceOnSecondLine)) {
        handleNewGlobalMinimum(
            totalDistance + extraDistanceOnSecondLine,
            intersectionStartSideSecondLoS,
            intersectionEndSideSecondLoS,
            getFurthestPointOnBoundary(true, false),
            getFurthestPointOnBoundary(false, false)
        );
    }
}

void SPV::MinSumCalculator::handleLocalMinimaWithBothPathsBlocked()
{
    Point firstIntersectionPointOnStartSide = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
    Point secondIntersectionPointOnStartSide = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide();
    Point firstIntersectionPointOnEndSide = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide();
    Point secondIntersectionPointOnEndSide = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
    double sumOfDistances = currentEventSegment->getDistanceToLastVertex(true) +
            currentEventSegment->getDistanceToLastVertex(false);
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    double localMinimum = getDistanceToIntersectionPoint(firstIntersectionPointOnStartSide, true) +
            getDistanceToIntersectionPoint(firstIntersectionPointOnEndSide, false);
    std::vector<std::pair<Point, Point>> minimumEdgeIntersections;
    minimumEdgeIntersections.push_back(std::make_pair(getFurthestPointOnBoundary(true, true), getFurthestPointOnBoundary(false, true)));
    double currentParameter = stepPrecision;

    while (currentParameter < 1) {
        double currentX = (1 - currentParameter) * firstIntersectionPointOnStartSide.x() + currentParameter * secondIntersectionPointOnStartSide.x();
        double currentY = (1 - currentParameter) * firstIntersectionPointOnStartSide.y() + currentParameter * secondIntersectionPointOnStartSide.y();
        Point intersectionPointOnStartSide = Point(currentX, currentY);
        Line currentLine = Line(intersectionPointOnStartSide, pivotPoint);

        boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndLine(currentLine, firstIntersectionPointOnEndSide, secondIntersectionPointOnEndSide);

        if (result.type() == typeid(bool)) {
            // TODO throw an error
            std::cout << "No intersection found on the other side";
        } else {
            Point intersectionPointOnEndSide = boost::get<Point>(result);
            double currentDistance = getDistanceToIntersectionPoint(intersectionPointOnStartSide, true) +
                getDistanceToIntersectionPoint(intersectionPointOnEndSide, false);
            if (gU.isLargerOrEqual(localMinimum, currentDistance)) {
                if (gU.isLarger(localMinimum, currentDistance)) {
                    localMinimum = currentDistance;
                    minimumEdgeIntersections.clear();
                }
                minimumEdgeIntersections.push_back(std::make_pair(intersectionPointOnStartSide, intersectionPointOnEndSide));
            }
        }
        currentParameter += stepPrecision;
    }
    double minAtSecondEvent = getDistanceToIntersectionPoint(secondIntersectionPointOnStartSide, true) +
            getDistanceToIntersectionPoint(secondIntersectionPointOnEndSide, false);

    if (gU.isLargerOrEqual(localMinimum, minAtSecondEvent)) {
        if (gU.isLarger(localMinimum, minAtSecondEvent)) {
            localMinimum = minAtSecondEvent;
            minimumEdgeIntersections.clear();
        }
        minimumEdgeIntersections.push_back(std::make_pair(getFurthestPointOnBoundary(true, false), getFurthestPointOnBoundary(false, false)));
    }

    double newMinimumValue = sumOfDistances + localMinimum;
    bool shouldHandleSectors = minimumEdgeIntersections.size() > 1;

    // Create the minima
    for (unsigned i = 0; i < minimumEdgeIntersections.size(); i++) {
        std::pair<Point, Point> currentPair = minimumEdgeIntersections.at(i);
        handleNewGlobalMinimum(
            newMinimumValue,
            currentPair.first,
            currentPair.second,
            currentPair.first,
            currentPair.second,
            shouldHandleSectors
        );
    }
}

void SPV::MinSumCalculator::handleLocalMinimaWithOnePathBlocked()
{
    Point firstIntersectionPointOnStartSide = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
    Point secondIntersectionPointOnStartSide = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide();
    Point firstIntersectionPointOnEndSide = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide();
    Point secondIntersectionPointOnEndSide = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
    double sumOfDistances = currentEventSegment->getDistanceToLastVertex(true) +
            currentEventSegment->getDistanceToLastVertex(false);
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    bool startSideFree = currentEventSegment->getStartSideLoSVisible();
    double localMinimum;

    std::vector<std::pair<Point, Point>> minimumEdgeIntersections;
    std::vector<std::pair<Point, Point>> minimumIntersectionsOnLos;
    Point intersectionOnLos, obstructedEdgePoint1, obstructedEdgePoint2, freeEdgePoint1, freeEdgePoint2;
    minimumEdgeIntersections.push_back(std::make_pair(getFurthestPointOnBoundary(true, true), getFurthestPointOnBoundary(false, true)));
    if (startSideFree) {
        freeEdgePoint1 = firstIntersectionPointOnStartSide;
        freeEdgePoint2 = secondIntersectionPointOnStartSide;
        obstructedEdgePoint1 = firstIntersectionPointOnEndSide;
        obstructedEdgePoint2 = secondIntersectionPointOnEndSide;
        intersectionOnLos = getIntersectionPointOnLoS(firstIntersectionPointOnStartSide, true);
        localMinimum = getDistanceToIntersectionPoint(intersectionOnLos, true) +
                getDistanceToIntersectionPoint(firstIntersectionPointOnEndSide, false);
        minimumIntersectionsOnLos.push_back(std::make_pair(intersectionOnLos, firstIntersectionPointOnEndSide));
    } else {
        freeEdgePoint1 = firstIntersectionPointOnEndSide;
        freeEdgePoint2 = secondIntersectionPointOnEndSide;
        obstructedEdgePoint1 = firstIntersectionPointOnStartSide;
        obstructedEdgePoint2 = secondIntersectionPointOnStartSide;
        intersectionOnLos = getIntersectionPointOnLoS(firstIntersectionPointOnEndSide, false);
        localMinimum = getDistanceToIntersectionPoint(firstIntersectionPointOnStartSide, true) +
                getDistanceToIntersectionPoint(intersectionOnLos, false);
        minimumIntersectionsOnLos.push_back(std::make_pair(firstIntersectionPointOnStartSide, intersectionOnLos));
    }
    double currentParameter = stepPrecision;

    while (currentParameter < 1) {
        double currentX = currentParameter * obstructedEdgePoint1.x() + (1 - currentParameter) * obstructedEdgePoint2.x();
        double currentY = currentParameter * obstructedEdgePoint1.y() + (1 - currentParameter) * obstructedEdgePoint2.y();
        Point intersectionPoint = Point(currentX, currentY);
        Line currentLine = Line(intersectionPoint, pivotPoint);
        boost::variant<Point, bool> result =
                gU.getIntersectionBetweenLineAndLine(currentLine, freeEdgePoint1, freeEdgePoint2);

        if (result.type() == typeid(bool)) {
            std::cout << "No intersection found on the other side";
        } else {
            Point pointOnFreeEdge = boost::get<Point>(result);
            intersectionOnLos = getIntersectionPointOnLoS(pointOnFreeEdge, startSideFree);
            double extraDistance = getDistanceToIntersectionPoint(intersectionOnLos, startSideFree) +
                getDistanceToIntersectionPoint(intersectionPoint, !startSideFree);
            if (gU.isLargerOrEqual(localMinimum, extraDistance)) {
                if (gU.isLarger(localMinimum, extraDistance)) {
                    localMinimum = extraDistance;
                    minimumEdgeIntersections.clear();
                    minimumIntersectionsOnLos.clear();
                }
                if (startSideFree) {
                    minimumEdgeIntersections.push_back(std::make_pair(pointOnFreeEdge, intersectionPoint));
                    minimumIntersectionsOnLos.push_back(std::make_pair(intersectionOnLos, intersectionPoint));
                } else {
                    minimumEdgeIntersections.push_back(std::make_pair(intersectionPoint, pointOnFreeEdge));
                    minimumIntersectionsOnLos.push_back(std::make_pair(intersectionPoint, intersectionOnLos));
                }
            }
        }
        currentParameter += stepPrecision;
    }

    double minAtSecondEvent;
    if (startSideFree) {
        intersectionOnLos =
                getIntersectionPointOnLoS(currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide(), true);
        minAtSecondEvent = getDistanceToIntersectionPoint(intersectionOnLos, true) +
                getDistanceToIntersectionPoint(currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide(), false);
    } else {
        intersectionOnLos =
                getIntersectionPointOnLoS(currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide(), false);
        minAtSecondEvent = getDistanceToIntersectionPoint(currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide(), true) +
                getDistanceToIntersectionPoint(intersectionOnLos, false);
    }

    if (gU.isLargerOrEqual(localMinimum, minAtSecondEvent)) {
        if (gU.isLarger(localMinimum, minAtSecondEvent)) {
            localMinimum = minAtSecondEvent;
            minimumEdgeIntersections.clear();
            minimumIntersectionsOnLos.clear();
        }
        minimumEdgeIntersections.push_back(
            std::make_pair(
                getFurthestPointOnBoundary(true, false),
                getFurthestPointOnBoundary(false, false)
            )
        );
        if (startSideFree) {
            minimumIntersectionsOnLos.push_back(std::make_pair(intersectionOnLos, currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide()));
        } else {
            minimumIntersectionsOnLos.push_back(std::make_pair(currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide(), intersectionOnLos));
        }
    }

    double newMinimumValue = sumOfDistances + localMinimum;
    bool shouldHandleSectors = minimumEdgeIntersections.size() > 1;
    // Create the minima
    for (unsigned i = 0; i < minimumEdgeIntersections.size(); i++) {
        std::pair<Point, Point> currentEdgePair = minimumEdgeIntersections.at(i);
        std::pair<Point, Point> currentLoSPair = minimumIntersectionsOnLos.at(i);
        handleNewGlobalMinimum(
            newMinimumValue,
            currentLoSPair.first,
            currentLoSPair.second,
            currentEdgePair.first,
            currentEdgePair.second,
            shouldHandleSectors
        );
    }
}

bool SPV::MinSumCalculator::handleLocalMinimumAtPivotPoint()
{
    double totalDistance = currentEventSegment->getDistanceToLastVertex(true) + currentEventSegment->getDistanceToLastVertex(false);
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    Point lastPointBeforeLoSOnStartSide = getLastPointOnShortestPath(currentEventSegment, true);
    Point oppositePointOnBoundary, oppositePointOnLoS, pointOnBoundary;

    // If the last point on the start side is equal to the pivot point, then the closest point
    // on the end side is on the second line of sight
    if (gU.pointsAreEqual(lastPointBeforeLoSOnStartSide, pivotPoint)) {
        pointOnBoundary = getFurthestPointOnBoundary(true, false);
        oppositePointOnBoundary = getFurthestPointOnBoundary(false, false);
        oppositePointOnLoS = getIntersectionPointOnLoS(oppositePointOnBoundary, false);
        totalDistance += getDistanceToIntersectionPoint(oppositePointOnLoS, false);

        handleNewGlobalMinimum(
            totalDistance,
            pivotPoint,
            oppositePointOnLoS,
            pointOnBoundary,
            oppositePointOnBoundary
        );
        return true;
    }

    Point lastPointBeforeLoSOnEndSide = getLastPointOnShortestPath(currentEventSegment, true);

    // If the last point on the end side is equal to the pivot point, then the closest point
    // on the start side is on the first line of sight
    if (gU.pointsAreEqual(lastPointBeforeLoSOnEndSide, pivotPoint)) {
        pointOnBoundary = getFurthestPointOnBoundary(false, true);
        oppositePointOnBoundary = getFurthestPointOnBoundary(true, true);
        oppositePointOnLoS = getIntersectionPointOnLoS(oppositePointOnBoundary, true);
        totalDistance += getDistanceToIntersectionPoint(oppositePointOnLoS, true);

        handleNewGlobalMinimum(
            totalDistance,
            oppositePointOnLoS,
            pivotPoint,
            oppositePointOnBoundary,
            pointOnBoundary
        );
        return true;
    }

    return false;
}

Point SPV::MinSumCalculator::getFurthestPointOnBoundary(bool onStartSide, bool firstLoS)
{
    bool hasNeighbor = false;
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    Point currentPoint, otherPotentialPoint;
    LineOfSight *loS, *neighborLoS;

    if (firstLoS) {
        loS = currentEventSegment->getFirstLineOfSightFromStart();
        if (currentEventSegment->hasPredecessor()) {
            hasNeighbor = true;
            neighborLoS = currentEventSegment->getPredecessor()->getSecondLineOfSightFromStart();
        }
    } else {
        loS = currentEventSegment->getSecondLineOfSightFromStart();
        if (currentEventSegment->hasSuccessor()) {
            hasNeighbor = true;
            neighborLoS = currentEventSegment->getSuccessor()->getFirstLineOfSightFromStart();
        }
    }
    if (onStartSide) {
        currentPoint = loS->getPointOnStartSide();
        // If this is not a vertex, it is already furthest on the boundary
        if (!loS->isStartPointVertex() || !hasNeighbor) {
            return currentPoint;
        }
        otherPotentialPoint = neighborLoS->getPointOnStartSide();
    } else {
        currentPoint = loS->getPointOnEndSide();
        // If this is not a vertex, it is already furthest on the boundary
        if (!loS->isEndPointVertex() || !hasNeighbor) {
            return currentPoint;
        }
        otherPotentialPoint = neighborLoS->getPointOnEndSide();
    }
    if (CGAL::squared_distance(pivotPoint, otherPotentialPoint) > CGAL::squared_distance(pivotPoint, currentPoint)) {
        return otherPotentialPoint;
    }
    return currentPoint;
}
