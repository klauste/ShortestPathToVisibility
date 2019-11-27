#include "spvminimumcalculatorminmax.h"
void SPV::MinimumCalculatorMinMax::calculateMinimumBetween2Events (
    EventIntersection *firstIntersection,
    EventIntersection *secondIntersection,
    unsigned pivotPointIndex,
    bool goLeft
) {
    if (this->getAllMinima().size() == 1) {
        return;
    }
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
    EventIntersection *oppositeSecondIntersection = boost::get<EventIntersection*>(result);
    oppositeSideTriangle = findTriangleWithIntersectionEvent(oppositeSideTriangle, secondIntersectionOnOppositeSide, goLeft);
    result = oppositeSideTriangle->getFace()->info().getEventIntersectionForIntersection(secondIntersectionOnOppositeSide);
    if (result.type() == typeid(bool)) {
        // Throw exception?
        std::cout << "Couldn't find the event intersection, something went wrong" << std::endl;
        return;
    }
    EventIntersection *oppositeFirstIntersection = boost::get<EventIntersection*>(result);

    double distanceFromStart = getDistanceSoFar(firstIntersection, true);
    double distanceFromEnd = getDistanceSoFar(oppositeFirstIntersection, false);
    double currentParameter = precision;
    bool minFound = false;
    double factor = 1.0;

    Point firstIntersectionPoint = firstIntersection->getIntersection();
    Point secondIntersectionPoint = secondIntersection->getIntersection();
    Point oppositeFirstIntersectionPoint = oppositeFirstIntersection->getIntersection();
    Point oppositeSecondIntersectionPoint = oppositeSecondIntersection->getIntersection();
    Point firstIntersectionPointOnLos = getIntersectionPointOnLoS(firstIntersection,firstIntersectionPoint, pivotPointIndex, true);
    Point secondIntersectionPointOnLos = getIntersectionPointOnLoS(firstIntersection,secondIntersectionPoint, pivotPointIndex, true);
    Point oppositeFirstIntersectionPointOnLos = getIntersectionPointOnLoS(oppositeFirstIntersection, oppositeFirstIntersectionPoint, pivotPointIndex, false);
    Point oppositeSecondIntersectionPointOnLos = getIntersectionPointOnLoS(oppositeSecondIntersection, oppositeSecondIntersectionPoint, pivotPointIndex, false);

    double distanceToFirstPoint = distanceFromStart + getDistanceToIntersectionPoint(firstIntersection, firstIntersectionPointOnLos, true);
    double distanceToSecondPoint = distanceFromStart + getDistanceToIntersectionPoint(firstIntersection, secondIntersectionPointOnLos, true);
    double oppositeDistanceToFirstPoint = distanceFromEnd + getDistanceToIntersectionPoint(oppositeFirstIntersection, oppositeFirstIntersectionPointOnLos, false);
    double oppositeDistanceToSecondPoint = distanceFromEnd + getDistanceToIntersectionPoint(oppositeFirstIntersection, oppositeSecondIntersectionPointOnLos, false);

    // Is the minimum to be found here?
    if (distanceToFirstPoint <= oppositeDistanceToFirstPoint &&  oppositeDistanceToSecondPoint <= distanceToSecondPoint) {
        // check equality at the first intersection
        if (distanceToFirstPoint == oppositeDistanceToSecondPoint) {
            handleNewMinimum(
                distanceToFirstPoint,
                firstIntersection,
                oppositeFirstIntersection,
                firstIntersectionPointOnLos,
                oppositeSecondIntersectionPointOnLos,
                firstIntersectionPoint,
                oppositeSecondIntersectionPoint,
                pivotPointIndex
            );
            return;
        }

        while (!minFound) {
            // reset the current parameter and increase the factor for equality check if 1 is reached
            if (currentParameter == 1) {
                currentParameter = precision;
                factor = factor + factor;
            }
            double currentX = currentParameter * firstIntersectionPoint.x() + (1 - currentParameter) * secondIntersectionPoint.x();
            double currentY = currentParameter * firstIntersectionPoint.y() + (1 - currentParameter) * secondIntersectionPoint.y();
            Point intersectionPoint = Point(currentX, currentY);
            Line currentLine = Line(intersectionPoint, pivotPoint);
            boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndSegment(currentLine, oppositeFirstIntersectionPoint, oppositeSecondIntersectionPoint);

            if (result.type() == typeid(bool)) {
                std::cout << "No intersection found on the other side";
            } else {
                Point oppositeIntersectionPoint = boost::get<Point>(result);
                double currentDistanceFromStart = distanceFromStart + getDistanceToIntersectionPoint(firstIntersection, intersectionPoint, true);
                double currentDistanceFromEnd = distanceFromEnd + getDistanceToIntersectionPoint(oppositeFirstIntersection, oppositeIntersectionPoint, false);
                if (valuesAreEqual(currentDistanceFromStart, currentDistanceFromEnd, factor)) {
                    handleNewMinimum(
                        distanceToFirstPoint,
                        firstIntersection,
                        oppositeFirstIntersection,
                        getIntersectionPointOnLoS(firstIntersection, intersectionPoint, pivotPointIndex, true),
                        getIntersectionPointOnLoS(oppositeSecondIntersection, oppositeIntersectionPoint, pivotPointIndex, false),
                        intersectionPoint,
                        oppositeIntersectionPoint,
                        pivotPointIndex
                    );
                    minFound = true;
                }
            }
            currentParameter = currentParameter + precision;
        }
    }
}
