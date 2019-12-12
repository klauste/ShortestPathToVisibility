#include "Events/eventcalculator.h"

void SPV::EventCalculator::calculatePathAndBoundaryEvents()
{

}

std::vector<SPV::SweptSegment *> SPV::EventCalculator::getSegmentsForFinalPoint(bool forFirstPoint)
{
    std::vector<SweptSegment *> segments;
    Point currentPivotPoint;
    Point finalPoint;
    if (forFirstPoint) {
        segments = shortestPath.at(1)->getSegmentsFromEnd();
        currentPivotPoint = shortestPath.at(1)->getPoint();
        finalPoint = shortestPath.at(0)->getPoint();
    } else {
        unsigned pathLength = shortestPath.size();
        segments = shortestPath.at(pathLength - 2)->getSegmentsFromStart();
        currentPivotPoint = shortestPath.at(pathLength - 2)->getPoint();
        finalPoint = shortestPath.back()->getPoint();
    }
    std::vector<SweptSegment *> newSegments;
    Line lineToCheck = Line(currentPivotPoint, finalPoint);
    unsigned i;
    Point leftPoint, rightPoint;

    if (currentSegmentOrderFromLeftToRight) {
        bool foundIntersection = false;
        for (i = 0; i < segments.size(); i++) {
            SweptSegment *currentSegment = segments.at(i);

            if (foundIntersection) {
                newSegments.push_back(currentSegment->getClone());
            } else {
                leftPoint = currentSegment->getLeftPoint();
                rightPoint = currentSegment->getRightPoint();

                boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndSegment(
                    lineToCheck,
                    leftPoint,
                    rightPoint
                );
                if (result.type() == typeid(bool)) {
                    continue;
                } else {
                    Point newLeftPoint = boost::get<Point>(result);
                    SweptSegment *newSegment;

                    if (gU.pointsAreEqual(newLeftPoint, leftPoint)) {
                        newSegment = currentSegment->getClone();
                    } else {
                        newSegment = new SweptSegment(
                            newLeftPoint, false, currentSegment->getRightPoint(), currentSegment->rightPointIsPolygonVertex()
                        );
                    }
                    newSegments.push_back(newSegment);
                    foundIntersection = true;
                }
            }
        }
    } else {
        for (i = 0; i < segments.size(); i++) {
            SweptSegment *currentSegment = segments.at(i);
            leftPoint = currentSegment->getLeftPoint();
            rightPoint = currentSegment->getRightPoint();

            boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndSegment(
                lineToCheck,
                leftPoint,
                rightPoint
            );
            if (result.type() == typeid(bool)) {
                newSegments.push_back(currentSegment->getClone());
            } else {
                Point newRightPoint = boost::get<Point>(result);
                SweptSegment *newSegment;

                if (gU.pointsAreEqual(newRightPoint, rightPoint)) {
                    newSegment = currentSegment->getClone();
                } else {
                    newSegment = new SweptSegment(
                        leftPoint, currentSegment->leftPointIsPolygonVertex(), newRightPoint, false
                    );
                }
                newSegments.push_back(newSegment);
                break;
            }
        }
    }
    return newSegments;
}

