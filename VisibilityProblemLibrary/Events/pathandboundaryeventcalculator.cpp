#include "Events/pathandboundaryeventcalculator.h"

void SPV::PathAndBoundaryEventCalculator::calculatePathAndBoundaryEvents()
{
    unsigned lastPointIndex = shortestPath.size() - 2;
    EventSegment *previousEvent;
    EventSegmentCreationResult result;

    for (unsigned i = 1; i <= lastPointIndex; i++) {
        bool isFirstPoint = false;
        currentSegmentOrderFromLeftToRight = isSegmentOrderFromLeftToRight(i);
        PointOnShortestPath *currentPoint = shortestPath.at(i);
        std::vector<SweptSegment*> segmentsOnStartSide = currentPoint->getSegmentsFromEnd();
        std::vector<SweptSegment*> segmentsOnEndSide = currentPoint->getSegmentsFromStart();
        if (i == 1) {
            segmentsOnStartSide = getSegmentsForFinalPoint(true);
            isFirstPoint = true;
        }
        if (i == lastPointIndex) {
            segmentsOnEndSide = getSegmentsForFinalPoint(false);
        }
        segmentsOnStartSide = getStartSegmentsForLoop(segmentsOnStartSide, i);
        segmentsOnEndSide = getEndSegmentsForLoop(segmentsOnEndSide, i);

        bool allSegmentsHandled = false;
        unsigned startSegmentIndex = 0;
        unsigned endSegmentIndex = 0;

        // Segments are now ordered in the correct way so that loop can start at 0
        while (!allSegmentsHandled) {
            SweptSegment *startSegment = segmentsOnStartSide.at(startSegmentIndex);
            SweptSegment *endSegment = segmentsOnEndSide.at(endSegmentIndex);

            if (startSegmentIndex == 0 && endSegmentIndex == 0) {
                result = createPathEventSegment(startSegment, endSegment, currentPoint);
            } else {
                result = createBoundaryEventSegment(
                            startSegment,
                            endSegment,
                            currentPoint,
                            result.startSideIsEndOfSegment,
                            result.endSideIsEndOfSegment
                );
            }
            if (isFirstPoint) {
                currentEventSegment = result.newEventSegment;
                isFirstPoint = false;
                firstEventSegment = currentEventSegment;
            } else {
                currentEventSegment->setSuccessor(result.newEventSegment);
                result.newEventSegment->setPredecessor(currentEventSegment);
                currentEventSegment = result.newEventSegment;
            }

            if (!result.endSideIsEndOfSegment && !result.startSideIsEndOfSegment) {
                // If neither end of the segments has been reached, a boundary event with
                // protruding vertex must have been encountered. Check which side the event
                // is on.
                SweptSegment *nextSegment;
                if (startSegmentIndex + 1 < segmentsOnStartSide.size()) {
                    nextSegment = segmentsOnStartSide.at(startSegmentIndex + 1);

                }
            } else {
                if (result.endSideIsEndOfSegment) {
                    endSegmentIndex++;
                }
                if (result.startSideIsEndOfSegment) {
                    startSegmentIndex++;
                }
            }
            allSegmentsHandled = (startSegmentIndex >= segmentsOnStartSide.size() || endSegmentIndex >= segmentsOnEndSide.size());
        }
    }
}

SPV::PathAndBoundaryEventCalculator::EventSegmentCreationResult SPV::PathAndBoundaryEventCalculator::createEventSegment(
        Point firstStartPoint,
        bool firstStartPointIsVertex,
        Point firstEndPoint,
        bool firstEndPointIsVertex,
        Point secondStartPoint,
        bool secondStartPointIsVertex,
        Point secondEndPoint,
        bool secondEndPointIsVertex,
        PointOnShortestPath *pivotPoint
)
{
    LineOfSight *firstLineOfSight = new LineOfSight(
        firstStartPoint,
        firstStartPointIsVertex,
        firstEndPoint,
        firstEndPointIsVertex
    );

    LineOfSight *secondLineOfSight;
    bool startSideIsEndOfSegment = false;
    bool endSideIsEndOfSegment = false;
    bool startSideIsVertex = false;
    bool endSideIsVertex = false;

    // Calculate the intersection with the start side segment
    boost::variant<Point, bool> startResult = gU.getIntersectionBetweenLineAndSegment(
        Line(secondEndPoint, pivotPoint->getPoint()),
        firstStartPoint,
        secondStartPoint
    );

    // Calculate the intersection with the end side segment
    boost::variant<Point, bool> endResult = gU.getIntersectionBetweenLineAndSegment(
        Line(secondStartPoint, pivotPoint->getPoint()),
        firstEndPoint,
        secondEndPoint
    );
    if (startResult.type() == typeid(Point) && endResult.type() == typeid(bool)) {
        endSideIsEndOfSegment = true;
        Point startSideIntersection = boost::get<Point>(startResult);
        if (gU.pointsAreEqual(startSideIntersection, secondStartPoint)) {
            startSideIntersection = secondStartPoint;
            startSideIsEndOfSegment = true;
            startSideIsVertex = secondStartPointIsVertex;
        }

        secondLineOfSight = new LineOfSight(
            startSideIntersection,
            startSideIsVertex,
            secondEndPoint,
            secondEndPointIsVertex
        );
    } else if (startResult.type() == typeid(bool) && endResult.type() == typeid(Point)) {
        startSideIsEndOfSegment = true;
        Point endSideIntersection = boost::get<Point>(endResult);
        if (gU.pointsAreEqual(endSideIntersection, secondEndPoint)) {
            endSideIntersection = secondEndPoint;
            endSideIsEndOfSegment = true;
            endSideIsVertex = secondEndPointIsVertex;
        }

        secondLineOfSight = new LineOfSight(
            secondStartPoint,
            secondStartPointIsVertex,
            endSideIntersection,
            endSideIsVertex
        );
    } else {
        // If both or no end of segment is reached, create the end line of sight at the vertices
        secondLineOfSight = new LineOfSight(
            secondStartPoint,
            secondStartPointIsVertex,
            secondEndPoint,
            secondEndPointIsVertex
        );
        startSideIsEndOfSegment = true;
        endSideIsEndOfSegment = true;
    }

    EventSegment *newSegment = new EventSegment(firstLineOfSight, secondLineOfSight, pivotPoint);

    return EventSegmentCreationResult(newSegment, startSideIsEndOfSegment, endSideIsEndOfSegment);
}

SPV::PathAndBoundaryEventCalculator::EventSegmentCreationResult SPV::PathAndBoundaryEventCalculator::createPathEventSegment(
        SPV::SweptSegment* startSideSegment,
        SPV::SweptSegment* endSideSegment,
        PointOnShortestPath *pivotPoint
) {
    Point firstStartPoint, firstEndPoint, secondStartPoint, secondEndPoint;
    bool firstStartPointIsVertex, firstEndPointIsVertex, secondStartPointIsVertex, secondEndPointIsVertex;

    if (currentSegmentOrderFromLeftToRight) {
        firstStartPoint = startSideSegment->getLeftPoint();
        firstStartPointIsVertex = startSideSegment->leftPointIsPolygonVertex();
        secondStartPoint = startSideSegment->getRightPoint();
        secondStartPointIsVertex = startSideSegment->rightPointIsPolygonVertex();

        firstEndPoint = endSideSegment->getLeftPoint();
        firstEndPointIsVertex = endSideSegment->leftPointIsPolygonVertex();
        secondEndPoint = endSideSegment->getRightPoint();
        secondEndPointIsVertex = endSideSegment->rightPointIsPolygonVertex();
    } else {
        firstStartPoint = startSideSegment->getRightPoint();
        firstStartPointIsVertex = startSideSegment->rightPointIsPolygonVertex();
        secondStartPoint = startSideSegment->getLeftPoint();
        secondStartPointIsVertex = startSideSegment->leftPointIsPolygonVertex();

        firstEndPoint = endSideSegment->getRightPoint();
        firstEndPointIsVertex = endSideSegment->rightPointIsPolygonVertex();
        secondEndPoint = endSideSegment->getLeftPoint();
        secondEndPointIsVertex = endSideSegment->leftPointIsPolygonVertex();
    }

    return createEventSegment(
        firstStartPoint,
        firstStartPointIsVertex,
        firstEndPoint,
        firstStartPointIsVertex,
        secondStartPoint,
        secondStartPointIsVertex,
        secondEndPoint,
        secondEndPointIsVertex,
        pivotPoint
    );
}

SPV::PathAndBoundaryEventCalculator::EventSegmentCreationResult SPV::PathAndBoundaryEventCalculator::createBoundaryEventSegment(
    SweptSegment* startSideSegment,
    SweptSegment* endSideSegment,
    PointOnShortestPath *pivotPoint,
    bool endOfStartSegmentReached,
    bool endOfEndSegmentReached
)
{
    Point firstStartPoint, firstEndPoint, secondStartPoint, secondEndPoint;
    bool firstStartPointIsVertex, firstEndPointIsVertex, secondStartPointIsVertex, secondEndPointIsVertex;
    LineOfSight *loS = currentEventSegment->getSecondLineOfSightFromStart();

    // The intersections are already ordered from left to right, so no
    // need to differentiate there
    if (!endOfStartSegmentReached) {
        firstStartPoint = loS->getPointOnStartSide();
        firstStartPointIsVertex = loS->isStartPointVertex();
    }
    if (!endOfEndSegmentReached) {
        firstEndPoint = loS->getPointOnEndSide();
        firstEndPointIsVertex = loS->isEndPointVertex();
    }
    if (currentSegmentOrderFromLeftToRight) {
        if (endOfStartSegmentReached) {
            firstStartPoint = startSideSegment->getLeftPoint();
            firstStartPointIsVertex = startSideSegment->leftPointIsPolygonVertex();
        }
        secondStartPoint = startSideSegment->getRightPoint();
        secondStartPointIsVertex = startSideSegment->rightPointIsPolygonVertex();
        if (endOfEndSegmentReached) {
            firstEndPoint = endSideSegment->getLeftPoint();
            firstEndPointIsVertex = endSideSegment->leftPointIsPolygonVertex();
        }
        secondEndPoint = endSideSegment->getRightPoint();
        secondEndPointIsVertex = endSideSegment->rightPointIsPolygonVertex();
    } else {
        if (endOfStartSegmentReached) {
            firstStartPoint = startSideSegment->getRightPoint();
            firstStartPointIsVertex = startSideSegment->rightPointIsPolygonVertex();
        }
        secondStartPoint = startSideSegment->getLeftPoint();
        secondStartPointIsVertex = startSideSegment->leftPointIsPolygonVertex();

        if (endOfEndSegmentReached) {
            firstEndPoint = endSideSegment->getRightPoint();
            firstEndPointIsVertex = endSideSegment->rightPointIsPolygonVertex();
        }
        secondEndPoint = endSideSegment->getLeftPoint();
        secondEndPointIsVertex = endSideSegment->leftPointIsPolygonVertex();
    }

    return createEventSegment(
        firstStartPoint,
        firstStartPointIsVertex,
        firstEndPoint,
        firstStartPointIsVertex,
        secondStartPoint,
        secondStartPointIsVertex,
        secondEndPoint,
        secondEndPointIsVertex,
        pivotPoint
    );
}

std::vector<SPV::SweptSegment*> SPV::PathAndBoundaryEventCalculator::getEndSegmentsForLoop(
    const std::vector<SweptSegment* > &segments,
    unsigned currentIndex
)
{
    std::vector<SweptSegment*> newSegments;
    bool willChangeOrder = false;
    Point nextPoint = shortestPath.at(currentIndex + 1)->getPoint();
    if (currentIndex < shortestPath.size() - 2) {
        willChangeOrder = isSegmentOrderFromLeftToRight(currentIndex + 1) != currentSegmentOrderFromLeftToRight;
    }
    if (currentSegmentOrderFromLeftToRight) {
        if (willChangeOrder) {
            for (unsigned i = 0; i < segments.size(); i++) {
                newSegments.push_back(segments.at(i));
                if (segments.at(i)->getRightPoint() == nextPoint) {
                    break;
                }
            }
        } else {
            // Check if the edge between the current pivot point and the previous one is not
            // part of the polygon boundary. If so there is a pocket which is not needed
            for (unsigned i = 0; i < segments.size(); i++) {
                if (segments.at(i)->getRightPoint() == nextPoint) {
                    break;
                }
                newSegments.push_back(segments.at(i));
            }
        }
        return newSegments;
    }

    if (willChangeOrder) {
        for (int i = segments.size() - 1; i >= 0; i--) {
            newSegments.push_back(segments.at(i));
            if (nextPoint == segments.at(i)->getLeftPoint()) {
                break;
            }
        }
    } else {
        for (int i = segments.size() - 1; i >= 0; i--) {
            if (segments.at(i)->getRightPoint() == nextPoint) {
                break;
            }
            newSegments.push_back(segments.at(i));
        }
    }
    return newSegments;
}

std::vector<SPV::SweptSegment*> SPV::PathAndBoundaryEventCalculator::getStartSegmentsForLoop(
    const std::vector<SweptSegment* > &segments,
    unsigned currentIndex
)
{
    std::vector<SweptSegment*> newSegments;
    bool hasChangedOrder = false;
    Point previousPoint = shortestPath.at(currentIndex - 1)->getPoint();
    if (currentIndex > 1) {
        hasChangedOrder = isSegmentOrderFromLeftToRight(currentIndex - 1) != currentSegmentOrderFromLeftToRight;
    }
    if (currentSegmentOrderFromLeftToRight) {
        bool foundLeftEdgePoint = false;
        if (hasChangedOrder) {
            for (unsigned i = 0; i < segments.size(); i++) {
                if (foundLeftEdgePoint) {
                    newSegments.push_back(segments.at(i));
                } else {
                    if (segments.at(i)->getLeftPoint() == previousPoint) {
                        newSegments.push_back(segments.at(i));
                        foundLeftEdgePoint = true;
                    }
                }
            }
        } else {
            // Check if the edge between the current pivot point and the previous one is not
            // part of the polygon boundary. If so there is a pocket which is not needed
            int indexOfFoundPoint = -1;
            for (int i = 0; i < segments.size(); i++) {
                if (segments.at(i)->getRightPoint() == previousPoint) {
                    indexOfFoundPoint = i;
                    break;
                }
            }
            for (int i = indexOfFoundPoint + 1; i < segments.size(); i++) {
                newSegments.push_back(segments.at(i));
            }
        }
        return newSegments;
    }

    bool foundRightEdgePoint = false;
    if (hasChangedOrder) {
        for (int i = segments.size() - 1; i >= 0; i--) {
                if (foundRightEdgePoint) {
                    newSegments.push_back(segments.at(i));
                } else if (previousPoint == segments.at(i)->getRightPoint()) {
                    foundRightEdgePoint = true;
                    newSegments.push_back(segments.at(i));
            }
        }
    } else {
        // Check if the edge between the current pivot point and the previous one is not
        // part of the polygon boundary. If so there is a pocket which is not needed
        int indexFoundPoint = segments.size();
        for (int i = segments.size() - 1; i >= 0; i--) {
            if (segments.at(i)->getLeftPoint() == previousPoint) {
                indexFoundPoint = i;
                break;
            }
        }
        for (int i = indexFoundPoint - 1; i >= 0; i--) {
            newSegments.push_back(segments.at(i));
        }
    }
    return newSegments;
}

std::vector<SPV::SweptSegment *> SPV::PathAndBoundaryEventCalculator::getSegmentsForFinalPoint(bool forFirstPoint)
{
    std::vector<SweptSegment *> segments;
    Point currentPivotPoint;
    Point finalPoint;
    bool addAfterFind;
    if (forFirstPoint) {
        segments = shortestPath.at(1)->getSegmentsFromEnd();
        currentPivotPoint = shortestPath.at(1)->getPoint();
        finalPoint = shortestPath.at(0)->getPoint();
        addAfterFind = currentSegmentOrderFromLeftToRight;
    } else {
        unsigned pathLength = shortestPath.size();
        segments = shortestPath.at(pathLength - 2)->getSegmentsFromStart();
        currentPivotPoint = shortestPath.at(pathLength - 2)->getPoint();
        finalPoint = shortestPath.back()->getPoint();
        addAfterFind = !currentSegmentOrderFromLeftToRight;
    }
    std::vector<SweptSegment *> newSegments;
    Line lineToCheck = Line(currentPivotPoint, finalPoint);
    unsigned i;
    Point leftPoint, rightPoint;

    if (addAfterFind) {
        bool foundIntersection = false;

        for (i = 0; i < segments.size(); i++) {
            if (foundIntersection) {
                newSegments.push_back(segments.at(i)->getClone());
            } else {
                SweptSegment *currentSegment = segments.at(i);
                leftPoint = currentSegment->getLeftPoint();
                rightPoint = currentSegment->getRightPoint();

                boost::variant<Point, bool> result = gU.getIntersectionBetweenLineAndSegment(
                    lineToCheck,
                    leftPoint,
                    rightPoint
                );
                if (result.type() == typeid(Point)) {
                    Point newLeftPoint = boost::get<Point>(result);
                    SweptSegment *newSegment;

                    if (gU.pointsAreEqual(newLeftPoint, rightPoint)) {
                        newSegment = currentSegment->getClone();
                    } else {
                        newSegment = new SweptSegment(
                            newLeftPoint, false, rightPoint, currentSegment->rightPointIsPolygonVertex()
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
