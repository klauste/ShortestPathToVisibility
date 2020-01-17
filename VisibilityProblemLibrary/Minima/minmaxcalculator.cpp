#include "Minima/minmaxcalculator.h"

void SPV::MinMaxCalculator::calculateMinima()
{
    bool minimumFound = false;
    currentEventSegment = firstEventSegment;

    while (!minimumFound) {
        if (isMinimumInCurrentSegment()) {
            minimumFound = true;
            handleMinimum();
        }
        if (currentEventSegment->hasSuccessor()) {
            currentEventSegment = currentEventSegment->getSuccessor();
        } else {
            break;
        }
    }
}

bool SPV::MinMaxCalculator::isMinimumInCurrentSegment()
{
    Point secondIntersectionPointOnStartSide = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide();
    Point firstIntersectionPointOnEndSide = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide();
    double distanceFromStart = currentEventSegment->getDistanceToLastVertex(true);
    double distanceFromEnd = currentEventSegment->getDistanceToLastVertex(false);

    Point lOSIntersectionOnStartSide = getIntersectionPointOnLoS(secondIntersectionPointOnStartSide, true);
    Point lOSIntersectionOnEndSide = getIntersectionPointOnLoS(firstIntersectionPointOnEndSide, false);
    double extraDistanceStartSide = getDistanceToIntersectionPoint(lOSIntersectionOnStartSide, true);
    double extraDistanceEndSide = getDistanceToIntersectionPoint(lOSIntersectionOnEndSide, false);
    return (distanceFromStart + extraDistanceStartSide) >= distanceFromEnd &&
            (distanceFromEnd + extraDistanceEndSide) >= distanceFromStart;
}

void SPV::MinMaxCalculator::handleMinimum()
{
    // Check if the minimum is at a pivot point
    bool minAtPivotPoint = handleMinimumAtPivotPoint();

    // If not try to find the minimum within the segment
    if (!minAtPivotPoint) {
        Point firstIntersectionPointOnStartSide = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
        Point secondIntersectionPointOnStartSide = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide();
        Point firstIntersectionPointOnEndSide = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide();
        Point secondIntersectionPointOnEndSide = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
        Point loSIntersectionOnStartSide = getIntersectionPointOnLoS(firstIntersectionPointOnStartSide, true);
        Point loSIntersectionOnEndSide = getIntersectionPointOnLoS(firstIntersectionPointOnEndSide, false);
        double distanceFromStart = currentEventSegment->getDistanceToLastVertex(true);
        double distanceFromEnd = currentEventSegment->getDistanceToLastVertex(false);
        Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
        double extraDistanceStartSide = getDistanceToIntersectionPoint(loSIntersectionOnStartSide, true);
        double extraDistanceEndSide = getDistanceToIntersectionPoint(loSIntersectionOnEndSide, false);
        if (gU.valuesAreEqual(distanceFromStart + extraDistanceStartSide, distanceFromEnd + extraDistanceEndSide)) {
            handleNewGlobalMinimum(
               distanceFromStart + extraDistanceStartSide,
               getIntersectionPointOnLoS(secondIntersectionPointOnStartSide, true),
               getIntersectionPointOnLoS(loSIntersectionOnEndSide, false),
               firstIntersectionPointOnStartSide,
               firstIntersectionPointOnEndSide
            );
            return;
        }

        double currentParameter = stepPrecision;

        while (currentParameter < 1) {
            double currentX = (1 - currentParameter) * firstIntersectionPointOnStartSide.x() + currentParameter * secondIntersectionPointOnStartSide.x();
            double currentY = (1 - currentParameter) * firstIntersectionPointOnStartSide.y() + currentParameter * secondIntersectionPointOnStartSide.y();
            Point intersectionPointOnStartSide = Point(currentX, currentY);
            Line currentLine = Line(intersectionPointOnStartSide, pivotPoint);

            boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndSegment(currentLine, firstIntersectionPointOnEndSide, secondIntersectionPointOnEndSide);

            if (result.type() == typeid(bool)) {
                // TODO throw an error
                std::cout << "No intersection found on the other side";
            } else {
                Point intersectionPointOnEndSide = boost::get<Point>(result);
                loSIntersectionOnStartSide = getIntersectionPointOnLoS(intersectionPointOnStartSide, true);
                loSIntersectionOnEndSide = getIntersectionPointOnLoS(intersectionPointOnEndSide, false);

                extraDistanceStartSide = getDistanceToIntersectionPoint(loSIntersectionOnStartSide, true);
                extraDistanceEndSide = getDistanceToIntersectionPoint(loSIntersectionOnEndSide, false);
                if (gU.valuesAreEqual(distanceFromStart + extraDistanceStartSide, distanceFromEnd + extraDistanceEndSide)) {
                    handleNewGlobalMinimum(
                       distanceFromStart + extraDistanceStartSide,
                       getIntersectionPointOnLoS(secondIntersectionPointOnStartSide, true),
                       getIntersectionPointOnLoS(loSIntersectionOnEndSide, false),
                       firstIntersectionPointOnStartSide,
                       firstIntersectionPointOnEndSide
                    );
                    return;
                }
            }
            currentParameter += stepPrecision;
        }

        // Check the second line of sight
        loSIntersectionOnStartSide = getIntersectionPointOnLoS(secondIntersectionPointOnStartSide, true);
        loSIntersectionOnEndSide = getIntersectionPointOnLoS(secondIntersectionPointOnEndSide, false);

        extraDistanceStartSide = getDistanceToIntersectionPoint(loSIntersectionOnStartSide, true);
        extraDistanceEndSide = getDistanceToIntersectionPoint(loSIntersectionOnEndSide, false);
        if (gU.valuesAreEqual(distanceFromStart + extraDistanceStartSide, distanceFromEnd + extraDistanceEndSide)) {
            handleNewGlobalMinimum(
               distanceFromStart + extraDistanceStartSide,
               getIntersectionPointOnLoS(secondIntersectionPointOnStartSide, true),
               getIntersectionPointOnLoS(loSIntersectionOnEndSide, false),
               firstIntersectionPointOnStartSide,
               firstIntersectionPointOnEndSide
            );
        } else {
            // TODO: throw an exception
        }
    }
}
bool SPV::MinMaxCalculator::handleMinimumAtPivotPoint()
{
    double totalDistance ;
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    Point lastPointBeforeLoS = getLastPointOnShortestPath(currentEventSegment, true);
    Point oppositePointOnBoundary, oppositePointOnLoS;

    // If the last point on the start side is equal to the pivot point, then the closest point
    // on the end side is on the second line of sight
    if (gU.pointsAreEqual(lastPointBeforeLoS, pivotPoint)) {
        oppositePointOnBoundary = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
        oppositePointOnLoS = getIntersectionPointOnLoS(oppositePointOnBoundary, false);
        totalDistance = currentEventSegment->getDistanceToLastVertex(true);

        handleNewGlobalMinimum(
            totalDistance,
            pivotPoint,
            oppositePointOnLoS,
            currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide(),
            oppositePointOnBoundary
        );
        Minimum *min = allMinima.at(0);
        min->setIsInDiscArea(true);
        min->setDiscRadius(totalDistance - currentEventSegment->getDistanceToLastVertex(false));
        return true;
    }

    lastPointBeforeLoS = getLastPointOnShortestPath(currentEventSegment, true);

    // If the last point on the end side is equal to the pivot point, then the closest point
    // on the start side is on the first line of sight
    if (gU.pointsAreEqual(lastPointBeforeLoS, pivotPoint)) {
        oppositePointOnBoundary = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
        oppositePointOnLoS = getIntersectionPointOnLoS(oppositePointOnBoundary, true);
        totalDistance = currentEventSegment->getDistanceToLastVertex(false);

        handleNewGlobalMinimum(
            totalDistance,
            oppositePointOnLoS,
            pivotPoint,
            oppositePointOnBoundary,
            currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide()
        );
        Minimum *min = allMinima.at(0);
        min->setIsInDiscArea(true);
        min->setDiscRadius(totalDistance - currentEventSegment->getDistanceToLastVertex(true));
        return true;
    }
    return false;
}
