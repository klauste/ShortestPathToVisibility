#include "Minima/minmaxcalculator.h"

void SPV::MinMaxCalculator::calculateMinima()
{
    calculateBendEvents();
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
    Point firstPointOnStartSide = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
    Point secondPointOnStartSide = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide();
    Point firstPointOnEndSide = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide();
    Point secondPointOnEndSide = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
    double distanceFromStart = currentEventSegment->getDistanceToLastVertex(true);
    double distanceFromEnd = currentEventSegment->getDistanceToLastVertex(false);

    Point firstIntersectionOnStartSide = getIntersectionPointOnLoS(firstPointOnStartSide, true);
    Point secondIntersectionOnStartSide = getIntersectionPointOnLoS(secondPointOnStartSide, true);
    Point firstIntersectionOnEndSide = getIntersectionPointOnLoS(firstPointOnEndSide, false);
    Point secondIntersectionOnEndSide = getIntersectionPointOnLoS(secondPointOnEndSide, false);

    double extraDistanceStartSideFirstLoS = getDistanceToIntersectionPoint(firstIntersectionOnStartSide, true);
    double extraDistanceStartSideSecondLoS = getDistanceToIntersectionPoint(secondIntersectionOnStartSide, true);
    double extraDistanceEndSideFirstLoS = getDistanceToIntersectionPoint(firstIntersectionOnEndSide, false);
    double extraDistanceEndSideSecondLoS = getDistanceToIntersectionPoint(secondIntersectionOnEndSide, false);

    if (gU.valuesAreEqualHighPrecision(distanceFromStart + extraDistanceStartSideFirstLoS, distanceFromEnd + extraDistanceEndSideFirstLoS)) {
        return true;
    }

    if (gU.valuesAreEqualHighPrecision(distanceFromStart + extraDistanceStartSideSecondLoS, distanceFromEnd + extraDistanceEndSideSecondLoS)) {
        return true;
    }
    return (distanceFromStart + extraDistanceStartSideFirstLoS < distanceFromEnd + extraDistanceEndSideFirstLoS &&
            distanceFromEnd + extraDistanceEndSideSecondLoS < distanceFromStart + extraDistanceStartSideSecondLoS);
}

void SPV::MinMaxCalculator::handleMinimum()
{
    // Check if the minimum is at a pivot point
    bool minAtPivotPoint = handleMinimumAtPivotPoint();

    // If not try to find the minimum within the segment
    if (!minAtPivotPoint) {
        findInnerMinimum(
            currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide(),
            currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide(),
            currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide(),
            currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide()
        );
    }
}

void SPV::MinMaxCalculator::findInnerMinimum(
        Point firstPointOnStartSide,
        Point secondPointOnStartSide,
        Point firstPointOnEndSide,
        Point secondPointOnEndSide
)
{
    double distanceFromStart = currentEventSegment->getDistanceToLastVertex(true);
    double distanceFromEnd = currentEventSegment->getDistanceToLastVertex(false);
    Point firstIntersectionOnStartSide = getIntersectionPointOnLoS(firstPointOnStartSide, true);
    Point firstIntersectionOnEndSide = getIntersectionPointOnLoS(firstPointOnEndSide, false);
    double extraDistanceStartSideAtFirstLoS = getDistanceToIntersectionPoint(firstIntersectionOnStartSide, true);
    double extraDistanceEndSideAtFirstLoS = getDistanceToIntersectionPoint(firstIntersectionOnEndSide, false);

    // End of recursion: the points or the distances at the first LoS are the same.
    if (
        gU.valuesAreEqualHighPrecision(distanceFromStart + extraDistanceStartSideAtFirstLoS, distanceFromEnd + extraDistanceEndSideAtFirstLoS)
    ) {
        handleNewGlobalMinimum(
           distanceFromStart + extraDistanceStartSideAtFirstLoS,
           firstIntersectionOnStartSide,
           firstIntersectionOnEndSide,
           firstPointOnStartSide,
           firstPointOnEndSide
        );
        return;
    }

    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    double middleX = 0.5 * (firstPointOnStartSide.x() + secondPointOnStartSide.x());
    double middleY = 0.5 * (firstPointOnStartSide.y() + secondPointOnStartSide.y());
    Point middlePointOnStartSide = Point(middleX, middleY);
    Line currentLine = Line(middlePointOnStartSide, pivotPoint);

    boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndSegment(
                currentLine,
                currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide(),
                currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide()
    );

    if (result.type() == typeid(bool)) {
        // TODO throw an error
        std::cout << "No intersection found on the other side";
    } else {
        Point middlePointOnEndSide = boost::get<Point>(result);
        Point middleIntersectionOnStartSide = getIntersectionPointOnLoS(middlePointOnStartSide, true);
        Point middleIntersectionOnEndSide = getIntersectionPointOnLoS(middlePointOnEndSide, false);

        double middleDistanceStartSide = getDistanceToIntersectionPoint(middleIntersectionOnStartSide, true);
        double middleDistanceEndSide = getDistanceToIntersectionPoint(middleIntersectionOnEndSide, false);
        if (distanceFromStart + middleDistanceStartSide < distanceFromEnd + middleDistanceEndSide) {
            findInnerMinimum(
                middlePointOnStartSide,
                secondPointOnStartSide,
                middlePointOnEndSide,
                secondPointOnEndSide
            );
        } else {
            findInnerMinimum(
                firstPointOnStartSide,
                middlePointOnStartSide,
                firstPointOnEndSide,
                middlePointOnEndSide
            );
        }
    }
}

bool SPV::MinMaxCalculator::handleMinimumAtPivotPoint()
{
    double totalDistance, distanceOnOppositeSide;
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    Point lastPointBeforeLoS = getLastPointBeforeLoS(currentEventSegment, true);
    Point oppositePointOnBoundary, oppositePointOnLoS;

    // If the last point on the start side is equal to the pivot point, then the closest point
    // on the end side is on the second line of sight
    if (gU.pointsAreEqual(lastPointBeforeLoS, pivotPoint)) {
        bool finalSegmentFound = false;
        while (!finalSegmentFound) {
            if (currentEventSegment->hasSuccessor()) {
                Point nextPivotPoint = currentEventSegment->getSuccessor()->getPivotPoint()->getPoint();
                if (gU.pointsAreEqual(pivotPoint, nextPivotPoint)) {
                    currentEventSegment = currentEventSegment->getSuccessor();
                } else {
                    finalSegmentFound = true;
                }
            } else {
                finalSegmentFound = true;
            }
        }
        oppositePointOnBoundary = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
        oppositePointOnLoS = getIntersectionPointOnLoS(oppositePointOnBoundary, false);
        totalDistance = currentEventSegment->getDistanceToLastVertex(true);
        distanceOnOppositeSide = currentEventSegment->getDistanceToLastVertex(false) +
                getDistanceToIntersectionPoint(oppositePointOnLoS, false);

        handleNewGlobalMinimum(
            totalDistance,
            pivotPoint,
            oppositePointOnLoS,
            currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide(),
            oppositePointOnBoundary
        );
        auto min = allMinima.at(0);
        min->setIsInDiscArea(true);
        min->setDiscRadius(totalDistance - distanceOnOppositeSide);
        min->setDiscOnStartSide(false);
        return true;
    }

    lastPointBeforeLoS = getLastPointBeforeLoS(currentEventSegment, false);

    // If the last point on the end side is equal to the pivot point, then the closest point
    // on the start side is on the first line of sight
    if (gU.pointsAreEqual(lastPointBeforeLoS, pivotPoint)) {
        bool finalSegmentFound = false;
        while (!finalSegmentFound) {
            if (currentEventSegment->hasPredecessor()) {
                Point nextPivotPoint = currentEventSegment->getPredecessor()->getPivotPoint()->getPoint();
                if (gU.pointsAreEqual(pivotPoint, nextPivotPoint)) {
                    currentEventSegment = currentEventSegment->getPredecessor();
                } else {
                    finalSegmentFound = true;
                }
            } else {
                finalSegmentFound = true;
            }
        }
        oppositePointOnBoundary = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
        oppositePointOnLoS = getIntersectionPointOnLoS(oppositePointOnBoundary, true);
        totalDistance = currentEventSegment->getDistanceToLastVertex(false);
        distanceOnOppositeSide = currentEventSegment->getDistanceToLastVertex(true) +
                getDistanceToIntersectionPoint(oppositePointOnLoS, true);

        handleNewGlobalMinimum(
            totalDistance,
            oppositePointOnLoS,
            pivotPoint,
            oppositePointOnBoundary,
            currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide()
        );
        auto min = allMinima.at(0);
        min->setIsInDiscArea(true);
        min->setDiscRadius(totalDistance - distanceOnOppositeSide);
        min->setDiscOnStartSide(true);
        return true;
    }
    return false;
}
