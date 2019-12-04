#include "spvminimumcalculator.h"
void SPV::MinimumCalculator::calculateMinima() {
    std::vector<int> indices;
    CDT::Face_handle currentFace;
    EventOnShortestPath* spEvent;
    ShortestPathEntry *currentEntry;
    std::vector<EventOnShortestPath*> spEvents;

    if (shortestPath.size() < 3) {
        return;
    }

    // Go through all the shortest path events and unset handled
    for (unsigned i = 1; i < shortestPath.size() - 1; i++) {
        currentEntry = shortestPath.at(i);
        currentFace = currentEntry->getFaceHandle();
        if (currentFace->info().getHasShortestPathEvents()) {
            spEvents = currentFace->info().getShortestPathEvents();
            for (unsigned j = 0; j < spEvents.size(); j++) {
                spEvents.at(j)->unsetHandled();
            }
        }
    }
    boost::variant<bool, SPV::EventIntersection*> result;
    PolygonTriangle *goLeftStartTriangle = eventMap.getStartTriangle();
    PolygonTriangle *goRightStartTriangle = eventMap.getStartTriangle();
    PolygonTriangle *goLeftEndTriangle = eventMap.getStartTriangle();
    PolygonTriangle *goRightEndTriangle = eventMap.getStartTriangle();
    PolygonTriangle *goLeftNextStartTriangle = eventMap.getStartTriangle();
    PolygonTriangle *goRightNextStartTriangle = eventMap.getStartTriangle();
    PolygonTriangle *goLeftNextEndTriangle = eventMap.getStartTriangle();
    PolygonTriangle *goRightNextEndTriangle = eventMap.getStartTriangle();

    startTriangle = eventMap.getStartTriangle();
    endTriangle = eventMap.getStartTriangle();
    nextTriangleStart = eventMap.getStartTriangle();
    nextTriangleEnd = eventMap.getStartTriangle();
    bool previousGoLeft;

    for (int i = 0; i < shortestPath.size() - 2; i++) {
        Point firstOnShortestPath = shortestPath.at(i)->getPoint();
        Point secondOnShortestPath = shortestPath.at(i + 1)->getPoint();
        Point thirdOnShortestPath = shortestPath.at(i + 2)->getPoint();
        bool goLeft = gU.isOnRightSide(firstOnShortestPath, secondOnShortestPath, thirdOnShortestPath);

        currentFace = shortestPath.at(i + 1)->getFaceHandle();
        spEvent = shortestPath.at(i + 1)->getFaceHandle()->info().getShortestPathEvent(firstOnShortestPath, secondOnShortestPath);
        Point firstIntersectionStart = spEvent->getFirstPointIntersection();
        Point firstIntersectionEnd = spEvent->getSecondPointIntersection();
        spEvent->setHandled(true);
        if (shortestPath.at(i + 2)->isEndPoint()) {
            spEvent = shortestPath.at(i + 1)->getFaceHandle()->info().getShortestPathEvent(secondOnShortestPath, thirdOnShortestPath);
        } else {
            spEvent = shortestPath.at(i + 2)->getFaceHandle()->info().getShortestPathEvent(secondOnShortestPath, thirdOnShortestPath);
        }
        Point nextIntersectionStart = spEvent->getFirstPointIntersection();
        Point nextIntersectionEnd = spEvent->getSecondPointIntersection();

        if (i == 0) {
            startTriangle = findTriangleWithIntersectionEvent(startTriangle, firstIntersectionStart, goLeft);
            endTriangle = findTriangleWithIntersectionEvent(endTriangle, firstIntersectionEnd, goLeft);

            nextTriangleStart = findTriangleWithIntersectionEvent(nextTriangleStart, nextIntersectionStart, goLeft);
            nextTriangleEnd = findTriangleWithIntersectionEvent(nextTriangleEnd, nextIntersectionEnd, goLeft);
            result = startTriangle->getFace()->info().getEventIntersectionForIntersection(firstIntersectionStart);
            previousGoLeft = goLeft;
        } else {
            result = nextTriangleStart->getFace()->info().getEventIntersectionForIntersection(firstIntersectionStart);
            if (goLeft != previousGoLeft) {
                if (goLeft) {
                    startTriangle = findTriangleWithFirstPoint(goLeftStartTriangle, firstOnShortestPath, goLeft);
                    endTriangle = findTriangleWithIntersectionEvent(goLeftEndTriangle, firstIntersectionEnd, goLeft);
                    nextTriangleStart = findTriangleWithIntersectionEvent(goLeftNextStartTriangle, nextIntersectionStart, goLeft);
                    nextTriangleEnd = findTriangleWithIntersectionEvent(goLeftNextEndTriangle, nextIntersectionEnd, goLeft);
                } else {
                    startTriangle = findTriangleWithFirstPoint(goRightStartTriangle, firstOnShortestPath, goLeft);
                    endTriangle = findTriangleWithIntersectionEvent(goRightEndTriangle, firstIntersectionEnd, goLeft);
                    nextTriangleStart = findTriangleWithIntersectionEvent(goRightNextStartTriangle, nextIntersectionStart, goLeft);
                    nextTriangleEnd = findTriangleWithIntersectionEvent(goRightNextEndTriangle, nextIntersectionEnd, goLeft);
                }
            } else {
                startTriangle = nextTriangleStart;
                endTriangle = nextTriangleEnd;
                nextTriangleStart = findTriangleWithIntersectionEvent(nextTriangleStart, nextIntersectionStart, goLeft);
                nextTriangleEnd = findTriangleWithIntersectionEvent(nextTriangleEnd, nextIntersectionEnd, goLeft);
            }
        }
        if (goLeft == true) {
            goLeftStartTriangle = startTriangle;
            goLeftEndTriangle = endTriangle;
            goLeftNextStartTriangle = nextTriangleStart;
            goLeftNextEndTriangle = nextTriangleEnd;
        } else {
            goRightStartTriangle = startTriangle;
            goRightEndTriangle = endTriangle;
            goRightNextStartTriangle = nextTriangleStart;
            goRightNextEndTriangle = nextTriangleEnd;
        }
        if (result.type() == typeid(bool)) {
            // Throw exception?
            std::cout << "Couldn't find the event intersection, something went wrong" << std::endl;
            std::cout << shortestPath.at(0)->getPoint() <<std::endl;
            return;
        }

        EventIntersection *currentIntersection = boost::get<EventIntersection*>(result);
        if (goLeft != previousGoLeft) {
            currentIntersection->setHasChangeInDirection();
        }
        previousGoLeft = goLeft;

        calculateMinimaBetween2PathEvents(
            currentIntersection,
            nextIntersectionStart,
            i + 1,
            goLeft
        );
    }
}

void SPV::MinimumCalculator::calculateMinimaBetween2PathEvents (
    EventIntersection *currentIntersection,
    Point nextIntersectionStart,
    unsigned pivotPointIndex,
    bool goLeft
) {
    Point currentVertex;
    bool finished;
    EventIntersection *firstIntersection = currentIntersection;

    do {
        EventIntersection* nextIntersection = getNextEvent(firstIntersection, goLeft, pivotPointIndex, true);
        finished = nextIntersection->getEventType() == 1 && nextIntersection->getIntersection() == nextIntersectionStart;
        calculateMinimumBetween2Events(
            firstIntersection,
            nextIntersection,
            pivotPointIndex,
            goLeft
        );
        firstIntersection = nextIntersection;
        startTriangle = findStartTriangleForCurrentEvent(startTriangle, firstIntersection, pivotPointIndex, goLeft, true);
        endTriangle = findEndTriangleForCurrentEvent(endTriangle, firstIntersection, pivotPointIndex, goLeft);
    } while (finished == false);
}

void SPV::MinimumCalculator::calculateMinimumBetween2Events (
    EventIntersection *firstIntersection,
    EventIntersection *secondIntersection,
    unsigned pivotPointIndex,
    bool goLeft
) {
    // Remember the last intersection which contains information about the shorts path
    // from the start
    if (firstIntersection->getEventType() != 3 || firstIntersection->belongsToStart()) {
        lastIntersectionFromStart = firstIntersection;
    }
    // If the second intersection is a type 3 event and it does not belong to the start,
    // set shortest path information herehere as it wasn't set on the second run when
    // calculating the bend events
    if (secondIntersection->getEventType() == 3 && !secondIntersection->belongsToStart()) {
        secondIntersection->setSptToLineOfSightOnPolygonEdge(lastIntersectionFromStart->getSptToLineOfSightOnPolygonEdge(true), true);
        secondIntersection->setPathToSemiCirclesIsFree(lastIntersectionFromStart->getPathToSemiCirclesIsFree(true), true);
        std::vector<Point> lastPathToLoS = lastIntersectionFromStart->getPathToLineOfSight(true);
        for(unsigned j = 0; j < lastPathToLoS.size(); j++) {
            secondIntersection->addToPathToLos(lastPathToLoS.at(j), true);
        }
    }

    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    Point firstIntersectionOnOppositeSide = getIntersectionOnOppositeSide(firstIntersection, pivotPointIndex);
    Point secondIntersectionOnOppositeSide = getIntersectionOnOppositeSide(secondIntersection, pivotPointIndex);
    PolygonTriangle *oppositeSideTriangle = findTriangleWithIntersectionEvent(endTriangle, firstIntersectionOnOppositeSide, goLeft);
    boost::variant<bool, SPV::EventIntersection*> result = oppositeSideTriangle->getFace()->info().getEventIntersectionForIntersection(firstIntersectionOnOppositeSide);
    if (result.type() == typeid(bool)) {
        // Throw exception?
        std::cout << "Couldn't find the event intersection, something went wrong" << std::endl;
        return;
    }
    EventIntersection *oppositeFirstIntersection = boost::get<EventIntersection*>(result);
    oppositeSideTriangle = findTriangleWithIntersectionEvent(oppositeSideTriangle, secondIntersectionOnOppositeSide, goLeft);
    result = oppositeSideTriangle->getFace()->info().getEventIntersectionForIntersection(secondIntersectionOnOppositeSide);
    if (result.type() == typeid(bool)) {
        // Throw exception?
        std::cout << "Couldn't find the event intersection, something went wrong" << std::endl;
        return;
    }
    EventIntersection *oppositeSecondIntersection = boost::get<EventIntersection*>(result);

    // First possibility: the last point on one of the shortest paths is the pivot point. In that case the minimum path is
    // either at event intersection 1 or 2
    if (handleMinimumAtPivotPoint(firstIntersection, secondIntersection, oppositeFirstIntersection, oppositeSecondIntersection, pivotPointIndex)) {
        return;
    }
    // Second possiblity: the paths to the semicircles on both sides of the lines of sight are free. In this case the minimum
    // is either at intersection 1 or intersection 2
    if (firstIntersection->getPathToSemiCirclesIsFree(true) && oppositeFirstIntersection->getPathToSemiCirclesIsFree(false)) {
        handleMinimaWithBothPathsFree(firstIntersection, secondIntersection, oppositeFirstIntersection, oppositeSecondIntersection, pivotPointIndex);
        return;
    }

    // Second possibility: both paths are on the polygon edge
    if (!firstIntersection->getPathToSemiCirclesIsFree(true) && !oppositeFirstIntersection->getSptToLineOfSightOnPolygonEdge(false)) {
        handleMinimaWithBothPathsBlocked(firstIntersection, secondIntersection, oppositeFirstIntersection, oppositeSecondIntersection, pivotPointIndex);
        return;
    }

    // Third possibility: one path lies on the polygon edge
    handleMinimaWithOnePathBlocked(firstIntersection, secondIntersection, oppositeFirstIntersection, oppositeSecondIntersection, pivotPointIndex);
}

bool SPV::MinimumCalculator::handleMinimumAtPivotPoint(
    EventIntersection *firstIntersection,
    EventIntersection *secondIntersection,
    EventIntersection *oppositeFirstIntersection,
    EventIntersection *oppositeSecondIntersection,
    unsigned pivotPointIndex
) {
    double distanceFromStart = getDistanceSoFar(firstIntersection, true);
    double distanceFromEnd = getDistanceSoFar(oppositeFirstIntersection, false);
    double sumOfDistances = distanceFromStart + distanceFromEnd;
    double totalDistance;
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();

    std::vector<Point> pathToLoS = firstIntersection->getPathToLineOfSight(true);
    Point lastPointOnPath = pathToLoS.at(pathToLoS.size() - 1);

    // If the last point on the start path is the pivotPoint, then the minimum is where the end path goes to the
    // intersection on the second event
    if (gU.pointsAreEqual(lastPointOnPath, pivotPoint)) {
        Point secondOppositeIntersectionOnLoS = getIntersectionPointOnLoS(oppositeFirstIntersection, oppositeSecondIntersection->getIntersection(), pivotPointIndex, false);
        double extraDistanceOppositeMoving = getDistanceToIntersectionPoint(oppositeSecondIntersection, secondOppositeIntersectionOnLoS, false);
        totalDistance = sumOfDistances + extraDistanceOppositeMoving;

        // If the path to the pivot point is added on the start side, the
        // point on the end side is the last point on the path to the LoS
        pathToLoS = oppositeSecondIntersection->getPathToLineOfSight(false);
        lastPointOnPath = pathToLoS.at(pathToLoS.size() - 1);
        handleNewMinimum(
            totalDistance,
            firstIntersection,
            oppositeFirstIntersection,
            pivotPoint,
            secondOppositeIntersectionOnLoS,
            secondIntersection->getIntersection(),
            oppositeSecondIntersection->getIntersection(),
            pivotPointIndex
        );
        return true;
    }

    pathToLoS = oppositeFirstIntersection->getPathToLineOfSight(false);
    lastPointOnPath = pathToLoS.at(pathToLoS.size() - 1);

    // If the last point on the start path is the pivotPoint, then the minimum is where the start path goes
    // to the first event intersection
    if (gU.pointsAreEqual(lastPointOnPath, pivotPoint)) {
        Point firstIntersectionOnLoS = getIntersectionPointOnLoS(firstIntersection, secondIntersection->getIntersection(), pivotPointIndex, true);
        double extraDistanceOppositeMoving = getDistanceToIntersectionPoint(firstIntersection, firstIntersectionOnLoS, true);
        totalDistance = sumOfDistances + extraDistanceOppositeMoving;

        // If the path to the pivot point is added on the start side, the
        // point on the end side is the last point on the path to the LoS
        pathToLoS = oppositeSecondIntersection->getPathToLineOfSight(false);
        lastPointOnPath = pathToLoS.at(pathToLoS.size() - 1);
        handleNewMinimum(
            totalDistance,
            firstIntersection,
            oppositeFirstIntersection,
            firstIntersectionOnLoS,
            pivotPoint,
            firstIntersection->getIntersection(),
            oppositeFirstIntersection->getIntersection(),
            pivotPointIndex
        );
        return true;
    }
    return false;
}

void SPV::MinimumCalculator::handleMinimaWithBothPathsFree(
    EventIntersection *firstIntersection,
    EventIntersection *secondIntersection,
    EventIntersection *oppositeFirstIntersection,
    EventIntersection *oppositeSecondIntersection,
    unsigned pivotPointIndex
) {
    double distanceFromStart = getDistanceSoFar(firstIntersection, true);
    double distanceFromEnd = getDistanceSoFar(oppositeFirstIntersection, false);
    double sumOfDistances = distanceFromStart + distanceFromEnd;
    double totalDistance;
    Point intersectionOnSecondLoS = getIntersectionPointOnLoS(firstIntersection, secondIntersection->getIntersection(), pivotPointIndex, true);
    Point oppositeIntersectionOnSecondLoS = getIntersectionPointOnLoS(oppositeSecondIntersection, oppositeSecondIntersection->getIntersection(), pivotPointIndex, false);

    double extraDistanceOnSecondLoS = getDistanceToIntersectionPoint(firstIntersection, intersectionOnSecondLoS, true) +
            getDistanceToIntersectionPoint(oppositeSecondIntersection, oppositeIntersectionOnSecondLoS, false);

    Point intersectionOnFirstLoS = getIntersectionPointOnLoS(firstIntersection, firstIntersection->getIntersection(), pivotPointIndex, true);
    Point oppositeIntersectionOnFirstLoS = getIntersectionPointOnLoS(oppositeSecondIntersection, oppositeFirstIntersection->getIntersection(), pivotPointIndex, false);
    double extraDistanceOnFirstLoS = getDistanceToIntersectionPoint(firstIntersection, intersectionOnFirstLoS, true) +
            getDistanceToIntersectionPoint(oppositeSecondIntersection, oppositeIntersectionOnFirstLoS, false);

    bool extraIsEqual = valuesAreEqual(extraDistanceOnSecondLoS, extraDistanceOnFirstLoS);

    if (extraIsEqual || extraDistanceOnSecondLoS < extraDistanceOnFirstLoS) {
        totalDistance = sumOfDistances + extraDistanceOnSecondLoS;
        handleNewMinimum(
            totalDistance,
            firstIntersection,
            oppositeFirstIntersection,
            intersectionOnSecondLoS,
            oppositeIntersectionOnSecondLoS,
            secondIntersection->getIntersection(),
            oppositeSecondIntersection->getIntersection(),
            pivotPointIndex
        );
    }
    if (extraIsEqual || extraDistanceOnFirstLoS < extraDistanceOnSecondLoS) {
        totalDistance = sumOfDistances + extraDistanceOnFirstLoS;
        handleNewMinimum(
            totalDistance,
            firstIntersection,
            oppositeFirstIntersection,
            intersectionOnFirstLoS,
            oppositeIntersectionOnFirstLoS,
            firstIntersection->getIntersection(),
            oppositeFirstIntersection->getIntersection(),
            pivotPointIndex
        );
    }
}

bool SPV::MinimumCalculator::valuesAreEqual(double dist1, double dist2, double factor) {
    double difference = abs(dist1 - dist2);
    return difference <= precision * factor;
}


void SPV::MinimumCalculator::handleNewMinimum (
    double newMinimumValue,
    EventIntersection* startIntersection,
    EventIntersection* endIntersection,
    Point startIntersectionOnLoS,
    Point endIntersectionOnLoS,
    Point startIntersectionOnEdge,
    Point endIntersectionOnEdge,
    unsigned pivotPointIndex
) {
    bool minsEqual = valuesAreEqual(newMinimumValue, currentMinimum);

    if (currentMinimum >= 0 && !minsEqual && newMinimumValue > currentMinimum) {
        return;
    }

    if (!minsEqual) {
        currentMinimum = newMinimumValue;

        if (allMinima.size() > 0) {
            allMinima.clear();
        }
    }
    Minimum *newMinimum = new Minimum();
    newMinimum->setLastIntersectionFromStart(startIntersection);
    newMinimum->setLastIntersectionFromEnd(endIntersection);
    newMinimum->setStartIntersectionOnLoS(startIntersectionOnLoS);
    newMinimum->setEndIntersectionOnLoS(endIntersectionOnLoS);
    newMinimum->setStartIntersectionOnEdge(startIntersectionOnEdge);
    newMinimum->setEndIntersectionOnEdge(endIntersectionOnEdge);
    newMinimum->setPivotPointIndex(pivotPointIndex);
    newMinimum->setDistance(currentMinimum);
    allMinima.push_back(newMinimum);
}

double SPV::MinimumCalculator::getDistanceToIntersectionPoint(EventIntersection *ei, Point intersectionPoint, bool fromStart) {
    std::vector<Point> pathToLoS = ei->getPathToLineOfSight(fromStart);
    Point lastPointOnPath = pathToLoS.at(pathToLoS.size() - 1);

    return sqrt(CGAL::squared_distance(lastPointOnPath, intersectionPoint));

}

Point SPV::MinimumCalculator::getIntersectionPointOnLoS(EventIntersection *ei, Point intersectionPoint, unsigned pivotPointIndex, bool fromStart) {
    std::vector<Point> pathToLoS = ei->getPathToLineOfSight(fromStart);
    Point lastPointOnPath = pathToLoS.at(pathToLoS.size() - 1);
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();

    // If the last point on the path is the pivotPoint, return that as intersection
    if (gU.pointsAreEqual(lastPointOnPath, pivotPoint)) {
        return pivotPoint;
    }

    // If the last point on the path is on the LoS return the last point on the path
    if (gU.isPointOnSegment(Segment(intersectionPoint, pivotPoint), lastPointOnPath)) {
        return lastPointOnPath;
    }

    if (ei->getPathToSemiCirclesIsFree(fromStart) == false) {
        return intersectionPoint;
    }

    return gU.getPerpendicularIntersectionPoint(Line(intersectionPoint, pivotPoint), lastPointOnPath);
}

void SPV::MinimumCalculator::handleMinimaWithBothPathsBlocked(
        EventIntersection *firstIntersection,
        EventIntersection *secondIntersection,
        EventIntersection *oppositeFirstIntersection,
        EventIntersection *oppositeSecondIntersection,
        unsigned pivotPointIndex
) {
    Point firstIntersectionPoint = firstIntersection->getIntersection();
    Point secondIntersectionPoint = secondIntersection->getIntersection();
    Point oppositeFirstIntersectionPoint = oppositeFirstIntersection->getIntersection();
    Point oppositeSecondIntersectionPoint = oppositeSecondIntersection->getIntersection();
    double distanceFromStart = getDistanceSoFar(firstIntersection, true);
    double distanceFromEnd = getDistanceSoFar(oppositeFirstIntersection, false);
    double sumOfDistances = distanceFromStart + distanceFromEnd;
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    double minSoFar = getDistanceToIntersectionPoint(firstIntersection, firstIntersectionPoint, true) +
            getDistanceToIntersectionPoint(oppositeFirstIntersection, oppositeFirstIntersectionPoint, false);
    std::vector<std::pair<Point, Point>> minimumEdgeIntersections;
    minimumEdgeIntersections.push_back(std::make_pair(firstIntersectionPoint, oppositeFirstIntersectionPoint));
    double currentParameter = precision;

    while (currentParameter < 1) {
        double currentX = currentParameter * firstIntersectionPoint.x() + (1 - currentParameter) * secondIntersectionPoint.x();
        double currentY = currentParameter * firstIntersectionPoint.y() + (1 - currentParameter) * secondIntersectionPoint.y();
        Point intersectionPoint = Point(currentX, currentY);
        Line currentLine = Line(intersectionPoint, pivotPoint);

        boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndSegment(currentLine, oppositeFirstIntersectionPoint, oppositeSecondIntersectionPoint);

        if (result.type() == typeid(bool)) {
            std::cout << "No intersection found on the other side";
        } else {
            Point oppositeIntersectionPoint = boost::get<Point>(result);
            double currentDistance = getDistanceToIntersectionPoint(firstIntersection, intersectionPoint, true) +
                getDistanceToIntersectionPoint(oppositeFirstIntersection, oppositeIntersectionPoint, false);
            if (currentDistance <= minSoFar) {
                if (currentDistance < minSoFar) {
                    minSoFar = currentDistance;
                    minimumEdgeIntersections.clear();
                }
                minimumEdgeIntersections.push_back(std::make_pair(intersectionPoint, oppositeIntersectionPoint));
            }
        }
        currentParameter += precision;
    }
    double minAtSecondEvent = getDistanceToIntersectionPoint(firstIntersection, secondIntersectionPoint, true) +
            getDistanceToIntersectionPoint(oppositeFirstIntersection, oppositeSecondIntersectionPoint, false);

    if (minAtSecondEvent <= minSoFar) {
        if (minAtSecondEvent < minSoFar) {
            minSoFar = minAtSecondEvent;
            minimumEdgeIntersections.clear();
        }
        minimumEdgeIntersections.push_back(std::make_pair(secondIntersectionPoint, oppositeSecondIntersectionPoint));
    }

    double newMinimumValue = sumOfDistances + minSoFar;
    // Create the minima
    for (unsigned i = 0; i < minimumEdgeIntersections.size(); i++) {
        std::pair<Point, Point> currentPair = minimumEdgeIntersections.at(i);
        handleNewMinimum(newMinimumValue, firstIntersection, secondIntersection, currentPair.first, currentPair.second, currentPair.first, currentPair.second, pivotPointIndex);
    }

}

void SPV::MinimumCalculator::handleMinimaWithOnePathBlocked(
        EventIntersection *firstIntersection,
        EventIntersection *secondIntersection,
        EventIntersection *oppositeFirstIntersection,
        EventIntersection *oppositeSecondIntersection,
        unsigned pivotPointIndex
) {
    Point firstIntersectionPoint = firstIntersection->getIntersection();
    Point secondIntersectionPoint = secondIntersection->getIntersection();
    Point oppositeFirstIntersectionPoint = oppositeFirstIntersection->getIntersection();
    Point oppositeSecondIntersectionPoint = oppositeSecondIntersection->getIntersection();
    double distanceFromStart = getDistanceSoFar(firstIntersection, true);
    double distanceFromEnd = getDistanceSoFar(oppositeFirstIntersection, false);
    double sumOfDistances = distanceFromStart + distanceFromEnd;
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    bool startSideFree = firstIntersection->getPathToSemiCirclesIsFree(true);
    Point edgePoint1;
    Point edgePoint2;

    if (startSideFree) {
        edgePoint1 = oppositeFirstIntersectionPoint;
        edgePoint2 = oppositeSecondIntersectionPoint;
    } else {
        edgePoint1 = firstIntersectionPoint;
        edgePoint2 = secondIntersectionPoint;
    }
    double minSoFar;
    std::vector<std::pair<Point, Point>> minimumEdgeIntersections;
    std::vector<std::pair<Point, Point>> minimumIntersectionsOnLos;
    Point intersectionOnLos;
    minimumEdgeIntersections.push_back(std::make_pair(firstIntersectionPoint, oppositeFirstIntersectionPoint));

    if (startSideFree) {
        intersectionOnLos = getIntersectionPointOnLoS(firstIntersection, firstIntersectionPoint, pivotPointIndex, true);
        minSoFar = getDistanceToIntersectionPoint(firstIntersection, intersectionOnLos, true) +
                getDistanceToIntersectionPoint(oppositeFirstIntersection, oppositeFirstIntersectionPoint, false);
        minimumIntersectionsOnLos.push_back(std::make_pair(intersectionOnLos, oppositeFirstIntersectionPoint));
    } else {
        intersectionOnLos = getIntersectionPointOnLoS(oppositeFirstIntersection, oppositeFirstIntersectionPoint, pivotPointIndex, false);
        minSoFar = getDistanceToIntersectionPoint(firstIntersection, firstIntersectionPoint, true) +
                getDistanceToIntersectionPoint(oppositeFirstIntersection, intersectionOnLos, false);
        minimumIntersectionsOnLos.push_back(std::make_pair(intersectionOnLos, intersectionOnLos));
    }
    double currentParameter = precision;

    while (currentParameter < 1) {
        double currentX = currentParameter * edgePoint1.x() + (1 - currentParameter) * edgePoint2.x();
        double currentY = currentParameter * edgePoint1.y() + (1 - currentParameter) * edgePoint2.y();
        Point intersectionPoint = Point(currentX, currentY);
        Line currentLine = Line(intersectionPoint, pivotPoint);
        double currentDistance;

        if (startSideFree) {
            boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndSegment(currentLine, firstIntersectionPoint, secondIntersectionPoint);

            if (result.type() == typeid(bool)) {
                std::cout << "No intersection found on the other side";
            } else {
                Point startPointOnEdge = boost::get<Point>(result);
                intersectionOnLos = getIntersectionPointOnLoS(firstIntersection, startPointOnEdge, pivotPointIndex, true);
                currentDistance = getDistanceToIntersectionPoint(firstIntersection, intersectionOnLos, true) +
                    getDistanceToIntersectionPoint(oppositeFirstIntersection, intersectionPoint, false);
                if (currentDistance <= minSoFar) {
                    if (currentDistance < minSoFar) {
                        minSoFar = currentDistance;
                        minimumEdgeIntersections.clear();
                    }
                    minimumEdgeIntersections.push_back(std::make_pair(startPointOnEdge, intersectionPoint));
                    minimumIntersectionsOnLos.push_back(std::make_pair(intersectionOnLos, intersectionPoint));

                }
            }
        } else {
            boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndSegment(currentLine, oppositeFirstIntersectionPoint, oppositeSecondIntersectionPoint);

            if (result.type() == typeid(bool)) {
                std::cout << "No intersection found on the other side";
            } else {
                Point endPointOnEdge = boost::get<Point>(result);
                intersectionOnLos = getIntersectionPointOnLoS(firstIntersection, endPointOnEdge, pivotPointIndex, true);
                double currentDistance = getDistanceToIntersectionPoint(firstIntersection, intersectionPoint, true) +
                    getDistanceToIntersectionPoint(oppositeFirstIntersection, intersectionOnLos, false);
                if (currentDistance <= minSoFar) {
                    if (currentDistance < minSoFar) {
                        minSoFar = currentDistance;
                        minimumEdgeIntersections.clear();
                    }
                    minimumEdgeIntersections.push_back(std::make_pair(intersectionPoint, endPointOnEdge));
                    minimumIntersectionsOnLos.push_back(std::make_pair(intersectionPoint, intersectionOnLos));

                }
            }
        }
        currentParameter += precision;
    }
    double minAtSecondEvent;
    if (startSideFree) {
        intersectionOnLos = getIntersectionPointOnLoS(firstIntersection, secondIntersectionPoint, pivotPointIndex, true);
        minAtSecondEvent = getDistanceToIntersectionPoint(firstIntersection, intersectionOnLos, true) +
                getDistanceToIntersectionPoint(oppositeFirstIntersection, oppositeSecondIntersectionPoint, false);
    } else {
        intersectionOnLos = getIntersectionPointOnLoS(oppositeFirstIntersection, oppositeSecondIntersectionPoint, pivotPointIndex, false);
        minAtSecondEvent = getDistanceToIntersectionPoint(firstIntersection, secondIntersectionPoint, true) +
                getDistanceToIntersectionPoint(oppositeFirstIntersection, intersectionOnLos, false);
    }

    if (minAtSecondEvent <= minSoFar) {
        if (minAtSecondEvent < minSoFar) {
            minSoFar = minAtSecondEvent;
            minimumEdgeIntersections.clear();
        }
        minimumEdgeIntersections.push_back(std::make_pair(secondIntersectionPoint, oppositeSecondIntersectionPoint));
        if (startSideFree) {
            minimumIntersectionsOnLos.push_back(std::make_pair(intersectionOnLos, oppositeSecondIntersectionPoint));
        } else {
            minimumIntersectionsOnLos.push_back(std::make_pair(secondIntersectionPoint, intersectionOnLos));
        }
    }

    double newMinimumValue = sumOfDistances + minSoFar;
    // Create the minima
    for (unsigned i = 0; i < minimumEdgeIntersections.size(); i++) {
        std::pair<Point, Point> currentEdgePair = minimumEdgeIntersections.at(i);
        std::pair<Point, Point> currentLoSPair = minimumEdgeIntersections.at(i);
        handleNewMinimum(newMinimumValue, firstIntersection, secondIntersection, currentEdgePair.first, currentEdgePair.second, currentLoSPair.first, currentLoSPair.second, pivotPointIndex);
    }
}
