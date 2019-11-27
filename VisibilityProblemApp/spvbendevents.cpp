#include "spvbendevents.h"

void SPV::BendEvents::calculateBendEvents() {
    std::vector<int> indices;
    CDT::Face_handle currentFace;
    EventOnShortestPath* spEvent;

    if (shortestPath.size() < 3) {
        return;
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
        previousGoLeft = goLeft;

        calculateEventsBetween2PathEvents(
            currentIntersection,
            nextIntersectionStart,
            i + 1,
            true,
            goLeft
        );
    }

    // Do the same thing from end to start
    for (int i = shortestPath.size() - 1; i > 1; i--) {
        Point firstOnShortestPath = shortestPath.at(i)->getPoint();
        Point secondOnShortestPath = shortestPath.at(i - 1)->getPoint();
        Point thirdOnShortestPath = shortestPath.at(i - 2)->getPoint();
        bool goLeft = gU.isOnRightSide(firstOnShortestPath, secondOnShortestPath, thirdOnShortestPath);

        // The face for the end point is the penultimate face
        if (i == shortestPath.size() - 1) {
            currentFace = shortestPath.at(i - 1)->getFaceHandle();
        } else {
            currentFace = shortestPath.at(i)->getFaceHandle();
        }
        spEvent = currentFace->info().getShortestPathEvent(secondOnShortestPath, firstOnShortestPath);
        Point firstIntersectionStart = spEvent->getSecondPointIntersection();
        Point firstIntersectionEnd = spEvent->getFirstPointIntersection();
        spEvent->setHandled(false);

        spEvent = shortestPath.at(i - 1)->getFaceHandle()->info().getShortestPathEvent(thirdOnShortestPath, secondOnShortestPath);
        Point nextIntersectionStart = spEvent->getSecondPointIntersection();
        Point nextIntersectionEnd = spEvent->getFirstPointIntersection();

        if (i == shortestPath.size() - 1) {
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

        previousGoLeft = goLeft;


        calculateEventsBetween2PathEvents(
            currentIntersection,
            nextIntersectionStart,
            i - 1,
            false,
            goLeft
        );
    }
}

void SPV::BendEvents:: calculateEventsBetween2PathEvents (
    EventIntersection *currentIntersection,
    Point nextIntersectionStart,
    unsigned pivotPointIndex,
    bool fromStart,
    bool goLeft
) {
    PolygonTriangle* currentTriangle = startTriangle;
    Point currentVertex;
    bool finished;
    CDT::Face_handle polygonEdgeFace = currentTriangle->getFace();
    CDT::Face_handle pivotPointHandle = shortestPath.at(pivotPointIndex)->getFaceHandle();

    for (unsigned i = 0; i < 3; i++) {
        std::cout << polygonEdgeFace->vertex(i)->point() << std::endl;
    }

     EventIntersection *firstIntersection = currentIntersection;
    // If the pivot point is the second point on the shortest path, the firstIntersection belongs to the start point
    if (fromStart && pivotPointIndex == 1) {
        firstIntersection->addToPathToLos(shortestPath.at(0)->getPoint(), fromStart);
    }
    if (!fromStart && pivotPointIndex == shortestPath.size() - 2) {
        firstIntersection->addToPathToLos(shortestPath.at(shortestPath.size() - 1)->getPoint(), fromStart);
    }

    do {
        EventIntersection* nextIntersection = getNextEvent(firstIntersection, goLeft, pivotPointIndex, fromStart);
        finished = nextIntersection->getEventType() == 1 && nextIntersection->getIntersection() == nextIntersectionStart;
        firstIntersection = calculateEventsBetween2Events(
            firstIntersection,
            nextIntersection,
            pivotPointIndex,
            goLeft,
            fromStart
        );

        // Default of start on polygon edge is that nothing changes
        nextIntersection->setSptToLineOfSightOnPolygonEdge(firstIntersection->getSptToLineOfSightOnPolygonEdge(fromStart), fromStart);
        firstIntersection = nextIntersection;
        startTriangle = findStartTriangleForCurrentEvent(startTriangle, firstIntersection, pivotPointIndex, goLeft, fromStart);
        endTriangle = findEndTriangleForCurrentEvent(endTriangle, firstIntersection, pivotPointIndex, goLeft);
    } while (finished == false);
}

SPV::EventIntersection* SPV::BendEvents::calculateEventsBetween2Events(
    EventIntersection *firstIntersection,
    EventIntersection *secondIntersection,
    unsigned pivotPointIndex,
    bool goLeft,
    bool fromStart
) {
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    std::vector<Point> pointsOnShortestPath = firstIntersection->getPathToLineOfSight(fromStart);
    Point lastPointToLos = pointsOnShortestPath.at(pointsOnShortestPath.size() - 1);

    // If the pivot point and the last point to the line of sight are the same, there is
    // nothing to do but to add the points to the los to the second event
    if (lastPointToLos == pivotPoint) {
        for (unsigned i = 0; i < pointsOnShortestPath.size(); i++) {
            secondIntersection->addToPathToLos(pointsOnShortestPath.at(i), fromStart);
        }
        return firstIntersection;
    }
    setStartOnPolygonEdge(firstIntersection, secondIntersection, pivotPointIndex, fromStart, goLeft);
    bool startOnPolygon = firstIntersection->getSptToLineOfSightOnPolygonEdge(fromStart);
    Point polygonEdgeStart = getPolygonEdgeStartPoint(firstIntersection, fromStart, pivotPointIndex);

    boost::variant<Point, bool> nextDegenerateResult = getNextDegenerateBendEvent(pivotPointIndex, firstIntersection, secondIntersection, polygonEdgeStart, fromStart);
    CDT::Face_handle pivotPointFace = shortestPath.at(pivotPointIndex)->getFaceHandle();
    SPV::EventOnShortestPath* spEvent;

    if (startOnPolygon) {
        // If no degenerate event was found, the path to the los did not move from the polygon edge. There is nothing to do
        // but to handle the end path or boundary event
        if (nextDegenerateResult.type() == typeid(bool)) {
            handlePathOrBoundaryEvents(
                pivotPointIndex,
                firstIntersection,
                secondIntersection,
                goLeft,
                fromStart,
                true
            );
            return firstIntersection;
        }
        Point circleIntersection = boost::get<Point>(nextDegenerateResult);
        firstIntersection = handleCircleIntersection(
            circleIntersection,
            pivotPointIndex,
            firstIntersection,
            goLeft,
            fromStart
        );
    }

    // If the path moves away from the polygon edge or no degenerate event was found, handle type 3 and type 2 events and then the last event
    if (startOnPolygon || nextDegenerateResult.type() == typeid(bool)) {
        firstIntersection = handleLosingPointBendEvents(pivotPointIndex, pivotPointFace, firstIntersection, secondIntersection->getIntersection(), goLeft, fromStart);
        firstIntersection = handleAddingPointBendEvents(pivotPointIndex, pivotPointFace, firstIntersection, secondIntersection->getIntersection(), goLeft, fromStart);
        handlePathOrBoundaryEvents(
            pivotPointIndex,
            firstIntersection,
            secondIntersection,
            goLeft,
            fromStart,
            false
        );
        return firstIntersection;
    }

    // At this point, the path to the LoS did not start on the current edge, but it touches it somewhere
    Point circleIntersection = boost::get<Point>(nextDegenerateResult);
    bool addDegenerateEvent = false;
    EventIntersection *newIntersection;

    bool finished = false;
    do {
        newIntersection = handleLosingPointBendEvents(pivotPointIndex, pivotPointFace, firstIntersection, circleIntersection, goLeft, fromStart);
        newIntersection = handleAddingPointBendEvents(pivotPointIndex, pivotPointFace, firstIntersection, circleIntersection, goLeft, fromStart);

        // No new intersection was found
        if (newIntersection == firstIntersection) {
            finished = true;
            addDegenerateEvent = true;
        } else {
            firstIntersection = newIntersection;
            // A new event was added, is there a new degenerate Event?
            nextDegenerateResult = getNextDegenerateBendEvent(pivotPointIndex, firstIntersection, secondIntersection, firstIntersection->getIntersection(), fromStart);
            if (nextDegenerateResult.type() == typeid(bool)) {
                // no new degenerate event was found end this without adding the new degenerate event
                finished = true;
            } else {
                // create the new degenerate event
                circleIntersection = boost::get<Point>(nextDegenerateResult);
            }
        }
    } while (!finished);
    if (addDegenerateEvent) {
        firstIntersection = handleCircleIntersection(circleIntersection, pivotPointIndex, firstIntersection, goLeft, fromStart);
        // Is there another degenerate event?
        nextDegenerateResult = getNextDegenerateBendEvent(pivotPointIndex, firstIntersection, secondIntersection, getPolygonEdgeStartPoint(firstIntersection, fromStart, pivotPointIndex), fromStart);
        if (nextDegenerateResult.type() == typeid(bool)) {
            // no new degenerate event was found, so add the type one event only
            handlePathOrBoundaryEvents(pivotPointIndex, firstIntersection, secondIntersection, goLeft, fromStart, true);
            return firstIntersection;
        }
        // Add the next degenerate event
        firstIntersection = handleCircleIntersection(circleIntersection, pivotPointIndex, firstIntersection, goLeft, fromStart);
    }
    // Again we are away from the polygon edge, so add all events which are still there (if any)
    firstIntersection = handleLosingPointBendEvents(pivotPointIndex, pivotPointFace, firstIntersection, secondIntersection->getIntersection(), goLeft, fromStart);
    firstIntersection = handleAddingPointBendEvents(pivotPointIndex, pivotPointFace, firstIntersection, secondIntersection->getIntersection(), goLeft, fromStart);
    handlePathOrBoundaryEvents(
        pivotPointIndex,
        firstIntersection,
        secondIntersection,
        goLeft,
        fromStart,
        false
    );
    return firstIntersection;
}

boost::variant<Point, bool> SPV::BendEvents::getNextDegenerateBendEvent(
        unsigned pivotPointIndex,
        EventIntersection *ei1,
        EventIntersection *ei2,
        Point polygonEdgeStart,
        bool fromStart
) {
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    std::vector<Point> verticesToLs = ei1->getPathToLineOfSight(fromStart);
    if (verticesToLs.empty()) {
        // Exception?
        std::cout << "Vertices to ls empty, we got a problem" << std::endl;
        return ei1;
    }
    Point startIntersection = ei1->getIntersection();
    Point lastVertexToLs = verticesToLs.back();
    Point centerPoint = Point((lastVertexToLs.x() + pivotPoint.x()) / 2, (lastVertexToLs.y() + pivotPoint.y()) / 2);
    boost::variant<std::vector<Point>, bool> intersectionResult =
        gU.getCircleSegmentIntersection(centerPoint, lastVertexToLs, polygonEdgeStart, ei2->getIntersection());

    // No intersection found, return false
    if (intersectionResult.type() == typeid(bool)) {
        return false;
    }

    std::vector<Point> circleIntersections = boost::get<std::vector<Point>>(intersectionResult);
    Point intersectionPoint;
    bool foundIntersectionPoint = false;
    K::FT distanceToStartIntersection = 0;

    for (unsigned i = 0; i < circleIntersections.size(); i++) {
        // If the intersections are equal, don't handle them
        if (gU.pointsAreEqual(polygonEdgeStart, circleIntersections.at(i))) {
            continue;
        }
        if (!foundIntersectionPoint) {
            foundIntersectionPoint = true;
            intersectionPoint = circleIntersections.at(i);
            distanceToStartIntersection = CGAL::squared_distance(intersectionPoint, startIntersection);
        } else {
            Point currentPoint = circleIntersections.at(i);
            // If a point has already been found, only set to the new point, if the distance is smaller
            if (distanceToStartIntersection > CGAL::squared_distance(currentPoint, startIntersection)) {
                // There can be a maximum of two circle intersections, so no need to reset the distance
                intersectionPoint = currentPoint;
            }
        }
    }
    if (foundIntersectionPoint) {
        return intersectionPoint;
    }
    return false;
}

void SPV::BendEvents::handlePathOrBoundaryEvents(
        unsigned pivotPointIndex,
        EventIntersection *ei1,
        EventIntersection *ei2,
        bool goLeft,
        bool fromStart,
        bool onPolygonEdge
) {
    std::vector<Point> verticesToLs = ei1->getPathToLineOfSight(fromStart);

    for (unsigned i = 0; i < verticesToLs.size(); i++) {
        ei2->addToPathToLos(verticesToLs.at(i), fromStart);
    }

    // If the next event is a bend event (can only occur if fromStart is false), then there is nothing else
    // to do after adding the points to the path to the LoS
    if (ei2->getEventType() == 3) {
        return;
    }
    Point secondIntersectionPoint = ei2->getIntersection();
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    Point lastPointToLos = verticesToLs.at(verticesToLs.size() - 1);
    EventOnShortestPath *spEvent = getSPEvent(pivotPointIndex, secondIntersectionPoint, fromStart);
    Point firstDefiningVertex = spEvent->getFirstDefiningPoint();

    if (ei2->getEventType() == 2) {
        if (ei2->belongsToStart() == fromStart) {
            // Add the defining vertex if it is protruding inside the polygon (i.e. if
            // the definig vertex and the intersection are different) and if it is closer to the pivot point
            // than the point on the LoS which is closest to the last point to the LoS
            if (secondIntersectionPoint != firstDefiningVertex) {
                Line l = Line(firstDefiningVertex, pivotPoint);
                Point iP = gU.getPerpendicularIntersectionPoint(l, lastPointToLos);
                if (CGAL::squared_distance(pivotPoint, iP) > CGAL::squared_distance(pivotPoint, firstDefiningVertex)) {
                    // Some of the points on the path to the LoS might become redundant
                    verticesToLs = ei2->getPathToLineOfSight(fromStart);
                    if (verticesToLs.size() > 1) {
                        for (unsigned i = verticesToLs.size() - 1; i > 0; i--) {
                            Point lastPoint = verticesToLs.at(i);
                            Point secondToLastPoint = verticesToLs.at(i - 1);
                            Line l = Line(firstDefiningVertex, secondToLastPoint);

                            // If the last point is on the other side of the line from the defining vertex to the
                            // second to last point than the pivot point, it can be removed
                            if (gU.isOnLeftSide(firstDefiningVertex, secondToLastPoint, pivotPoint)) {
                                if (gU.isOnRightSide(firstDefiningVertex, secondToLastPoint, lastPoint)) {
                                    ei2->removeLastElementOnPathToLos(fromStart);
                                    continue;
                                } else {
                                    break;
                                }
                            } else {
                                if (gU.isOnLeftSide(firstDefiningVertex, secondToLastPoint, lastPoint)) {
                                    ei2->removeLastElementOnPathToLos(fromStart);
                                    continue;
                                } else {
                                    break;
                                }
                            }
                        }
                    }
                    ei2->addToPathToLos(firstDefiningVertex, fromStart);
                }
                return;
            }
            // Otherwise, if the path is currently on the polygon edge, add the defining polygon vertex to the shortest path if
            // the next edge bends towards the outside of the polygon as seen from the current line to the line of sigth.
            if (onPolygonEdge) {
                EventIntersection *nextIntersection = getNextEvent(ei2, goLeft, pivotPointIndex, fromStart, false);
                Point nextIntersectionPoint = nextIntersection->getIntersection();

                if (gU.isOnLeftSide(lastPointToLos, firstDefiningVertex, pivotPoint)) {
                    if (gU.isOnRightSide(lastPointToLos, firstDefiningVertex, nextIntersectionPoint)) {
                        ei2->addToPathToLos(firstDefiningVertex, fromStart);
                    }
                } else {
                    if (gU.isOnLeftSide(lastPointToLos, firstDefiningVertex, nextIntersectionPoint)) {
                        ei2->addToPathToLos(firstDefiningVertex, fromStart);
                    }
                }
                return;
            }
        }
    } else {
        // If the next LoS will rotate in a different direction, add the first defining vertex
        if (!doesNextLoSRotateInTheSameDirection(pivotPointIndex, fromStart, goLeft)) {
            ei2->setHasChangeInDirection();

            // Change of direction -> new path to los is the shortest path to current pivot point
            ei2->clearPathToLoS(fromStart);

            unsigned index;
            if (fromStart) {
                for (index = 0 ; index <= pivotPointIndex; index++) {
                    ei2->addToPathToLos(shortestPath.at(index)->getPoint(), true);
                }
            } else {
                for (index = shortestPath.size() -1 ; index >= pivotPointIndex; index--) {
                    ei2->addToPathToLos(shortestPath.at(index)->getPoint(), false);
                }
            }
        }
    }
}

bool SPV::BendEvents::doesNextLoSRotateInTheSameDirection(unsigned pivotPointIndex, bool fromStart, bool goLeft) {
    Point nextPivotPoint;
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    bool nextGoLeft;
    if (fromStart) {
        if (pivotPointIndex < shortestPath.size() - 2) {
            nextPivotPoint = shortestPath.at(pivotPointIndex + 1)->getPoint();
            nextGoLeft = gU.isOnRightSide(pivotPoint, shortestPath.at(pivotPointIndex + 1)->getPoint(), shortestPath.at(pivotPointIndex + 2)->getPoint());
        } else {
            // The next Line of sight is the last one. It doesn't rotate, so we can return true
            return true;
        }


    } else {
        if (pivotPointIndex >= 2) {
            nextPivotPoint = shortestPath.at(pivotPointIndex - 1)->getPoint();
            nextGoLeft = gU.isOnRightSide(pivotPoint, nextPivotPoint, shortestPath.at(pivotPointIndex - 2)->getPoint());
        } else {
            // The next Line of sight is the last one. It doesn't rotate, so we can return true
            return true;
        }
    }
    return goLeft == nextGoLeft;
}

SPV::EventIntersection* SPV::BendEvents::handleCircleIntersection(
        Point circleIntersection,
        unsigned pivotPointIndex,
        EventIntersection *ei1,
        bool goLeft,
        bool fromStart
) {
    CDT::Face_handle pivotPointFace = shortestPath.at(pivotPointIndex)->getFaceHandle();
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    std::vector<Point> pointsToLoS = ei1->getPathToLineOfSight(fromStart);
    EventOnShortestPath *newSpEvent;

    EventIntersection *newEi = createEventIntersection(
        circleIntersection,
        pivotPoint,
        goLeft,
        fromStart
    );
    for (unsigned i = 0; i < pointsToLoS.size(); i++) {
        newEi->addToPathToLos(pointsToLoS.at(i), fromStart);
    }
    newEi->setPathToSemiCirclesIsFree(!ei1->getPathToSemiCirclesIsFree(fromStart), fromStart);
    newSpEvent = new EventOnShortestPath(circleIntersection, pivotPoint);
    newSpEvent->setFirstPointIntersection(circleIntersection);
    newSpEvent->setHandled(fromStart);
    endTriangle = handleIntersection(endTriangle, nextTriangleEnd, newSpEvent, goLeft, true, fromStart, 3);
    pivotPointFace->info().addShortestPathEvent(newSpEvent);

    return newEi;
}

SPV::EventIntersection* SPV::BendEvents::handleAddingPointBendEvents(
        unsigned pivotPointIndex,
        CDT::Face_handle pivotPointFace,
        EventIntersection *ei1,
        Point nextIntersection,
        bool goLeft,
        bool fromStart
) {
    std::vector<Point> verticesToLs = ei1->getPathToLineOfSight(fromStart);
    if (verticesToLs.empty()) {
        // Exception?
        std::cout << "Vertices to ls empty, we got a problem" << std::endl;
        return ei1;
    }
    Line shortestPathLine;
    Line lineToTest;
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();

    Point lastVertexToLs = verticesToLs.back();
    int indexOfLastVertexToLs = -1;
    EventIntersection* newIntersection = ei1;
    std::vector<Point> verticesToLineOfSight;
    EventOnShortestPath* newSpEvent;

    if (!fromStart) {
        for (unsigned i = shortestPath.size() - 1; i > pivotPointIndex; i--) {
            if (gU.pointsAreEqual(lastVertexToLs, shortestPath.at(i)->getPoint())) {
                indexOfLastVertexToLs = i;
                break;
            }
        }
        // If the current point is not a point on the shortest path, there is nothing to do
        if (indexOfLastVertexToLs == -1) {
            return newIntersection;
        }

        for (unsigned i = indexOfLastVertexToLs; i > pivotPointIndex; i--) {
            shortestPathLine = Line(shortestPath.at(i)->getPoint(), shortestPath.at(i - 1)->getPoint());
            // If the path to the semicircles is free, the line of sight perpendicular to the
            // shortest path line needs to intersect with the current edge. Otherwise, the
            // short path line needs to intersect.
            if (ei1->getPathToSemiCirclesIsFree(fromStart) == true) {
                lineToTest = shortestPathLine.perpendicular(pivotPoint);
            } else {
                lineToTest = shortestPathLine;
            }
            Point polygonStartPoint = getPolygonEdgeStartPoint(newIntersection, fromStart, pivotPointIndex);
            Segment currentSegment = Segment(polygonStartPoint, nextIntersection);
            CGAL::cpp11::result_of<Intersect_2(Line, Segment)>::type
                result = intersection(lineToTest, currentSegment);
            if (result) {
                if (const Point* p = boost::get<Point>(&*result)) {
                    Point intersectionPoint = Point(p->x(), p->y());
                    verticesToLineOfSight = newIntersection->getPathToLineOfSight(fromStart);
                    newIntersection = createEventIntersection(
                        intersectionPoint,
                        pivotPoint,
                        goLeft,
                        fromStart
                    );

                    // Add the points on the shortest path to the list of points
                    // of the new intersection
                    for (unsigned j = 0; j < verticesToLineOfSight.size(); j++) {
                        newIntersection->addToPathToLos(verticesToLineOfSight.at(j), fromStart);
                    }
                    // Add the point on the shortest path
                    newIntersection->addToPathToLos(shortestPath.at(i - 1)->getPoint(), fromStart);
                    newSpEvent = new EventOnShortestPath(intersectionPoint, pivotPoint);
                    newSpEvent->setFirstPointIntersection(intersectionPoint);
                    newSpEvent->setHandled(fromStart);
                    endTriangle = handleIntersection(endTriangle, nextTriangleEnd, newSpEvent, goLeft, true, fromStart, 3);
                    pivotPointFace->info().addShortestPathEvent(newSpEvent);
                }
            } else {
                break;
            }
        }
    } else {
        for (unsigned i = 0; i < pivotPointIndex; i++) {
            if (gU.pointsAreEqual(lastVertexToLs, shortestPath.at(i)->getPoint())) {
                indexOfLastVertexToLs = i;
                break;
            }
        }
        // If the current point is not a point on the shortest path, there is nothing to do
        if (indexOfLastVertexToLs == -1) {
            return newIntersection;
        }

        for (unsigned i = indexOfLastVertexToLs; i < pivotPointIndex; i++) {
            shortestPathLine = Line(shortestPath.at(i)->getPoint(), shortestPath.at(i + 1)->getPoint());
            // If the path to the semicircles is free, the line of sight perpendicular to the
            // shortest path line needs to intersect with the current edge. Otherwise, the
            // short path line needs to intersect.
            if (ei1->getPathToSemiCirclesIsFree(fromStart) == true) {
                lineToTest = shortestPathLine.perpendicular(pivotPoint);
            } else {
                lineToTest = shortestPathLine;
            }
            Point polygonEdgeStart = getPolygonEdgeStartPoint(newIntersection, fromStart, pivotPointIndex);
            Segment currentSegment = Segment(polygonEdgeStart, nextIntersection);
            CGAL::cpp11::result_of<Intersect_2(Line, Segment)>::type
                result = intersection(lineToTest, currentSegment);
            if (result) {
                if (const Point* p = boost::get<Point>(&*result)) {
                    Point intersectionPoint = Point(p->x(), p->y());
                    verticesToLineOfSight = newIntersection->getPathToLineOfSight(fromStart);
                    newIntersection = createEventIntersection(
                        intersectionPoint,
                        pivotPoint,
                        goLeft,
                        fromStart
                    );

                    // Add the points on the shortest path to the list of points
                    // of the new intersection
                    for (unsigned j = 0; j < verticesToLineOfSight.size(); j++) {
                        newIntersection->addToPathToLos(verticesToLineOfSight.at(j), fromStart);
                    }
                    // Add the point on the shortest path
                    newIntersection->addToPathToLos(shortestPath.at(i + 1)->getPoint(), fromStart);
                    newSpEvent = new EventOnShortestPath(intersectionPoint, pivotPoint);
                    newSpEvent->setFirstPointIntersection(intersectionPoint);
                    newSpEvent->setHandled(fromStart);
                    endTriangle = handleIntersection(endTriangle, nextTriangleEnd, newSpEvent, goLeft, true, fromStart, 3);
                    pivotPointFace->info().addShortestPathEvent(newSpEvent);
                }
            } else {
                break;
            }
        }
    }
    return newIntersection;
}

SPV::EventIntersection* SPV::BendEvents::handleLosingPointBendEvents(
    unsigned pivotPointIndex,
    CDT::Face_handle pivotPointFace,
    EventIntersection *ei1,
    Point nextIntersection,
    bool goLeft,
    bool fromStart
) {
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    std::vector<Point> verticesToLineOfSight = ei1->getPathToLineOfSight(fromStart);
    EventIntersection *newIntersection = ei1;
    EventOnShortestPath* newSpEvent;
    Line lineToTest;

    // If there is only 1 point on the list (it must be the start point)
    // there is nothing to do, so we can simply return the first intersection
    // event
    if (verticesToLineOfSight.size() <= 1) {
        return ei1;
    }


    // Go through the points on the list and see if a the perpendicular line through two points (where at
    // least one is not part of the shortest path) intersects the current edge
    for (unsigned i = verticesToLineOfSight.size() - 1; i > 0; i--) {
        // If the last point to the LoS is point on the shortest, return
        Point lastPointToLoS = verticesToLineOfSight.at(i);
        if (isPointOnShortestPathBeforePiovt(lastPointToLoS, pivotPointIndex, fromStart)) {
            break;
        }
        Line lineThroughVertices = Line(verticesToLineOfSight.at(i - 1), lastPointToLoS);
        // If the path to the semicircles is free, the line of sight perpendicular to the
        // shortest path line needs to intersect with the current edge. Otherwise, the
        // short path line needs to intersect.
        if (ei1->getPathToSemiCirclesIsFree(fromStart) == true) {
            lineToTest = lineThroughVertices.perpendicular(pivotPoint);
        } else {
            lineToTest = lineThroughVertices;
        }
        Point polygonEdgeStart = getPolygonEdgeStartPoint(newIntersection, fromStart, pivotPointIndex);
        Segment currentSegment = Segment(polygonEdgeStart, nextIntersection);
        CGAL::cpp11::result_of<Intersect_2(Line, Segment)>::type
            result = intersection(lineToTest, currentSegment);
        if (result) {
            if (const Point* p = boost::get<Point>(&*result)) {
                Point intersectionPoint = Point(p->x(), p->y());

                newIntersection = createEventIntersection(
                    intersectionPoint,
                    pivotPoint,
                    goLeft,
                    fromStart
                );

                // Add the points up to (but not including) i to the list of points
                // of the new intersection
                for (unsigned j = 0; j < i; j++) {
                    newIntersection->addToPathToLos(verticesToLineOfSight.at(j), fromStart);
                }
                newSpEvent = new EventOnShortestPath(intersectionPoint, pivotPoint);
                newSpEvent->setFirstPointIntersection(intersectionPoint);
                newSpEvent->setHandled(fromStart);
                endTriangle = handleIntersection(endTriangle, nextTriangleEnd, newSpEvent, goLeft, true, fromStart, 3);
                pivotPointFace->info().addShortestPathEvent(newSpEvent);
            }
        } else {
            break;
        }
    }
    return newIntersection;
}

SPV::EventIntersection* SPV::BendEvents::createEventIntersection(Point intersectionPoint, Point pivotPoint, bool goLeft, bool fromStart) {
    std::pair<PolygonTriangle*, Segment> resultPair = findTriangleWithIntersection(startTriangle, intersectionPoint, goLeft);

    startTriangle = resultPair.first;
    Segment s = resultPair.second;
    EventIntersection *ei = new EventIntersection(
        3,
        pivotPoint,
        intersectionPoint,
        s.source(),
        s.target()
    );
    ei->setBelongsToStart(fromStart);
    startTriangle->getFace()->info().addEventIntersection(ei);
    return ei;
}

void SPV::BendEvents::setStartOnPolygonEdge(EventIntersection *startIntersection, EventIntersection *endIntersection, unsigned pivotPointIndex, bool fromStart, bool goLeft) {
    // If the start intersection is a path event and the rotation direction remains the same, there is nothing to do
    if (startIntersection->getEventType() == 1 && startIntersection->getHasChangeInDirection() == false) {
        return;
    }
    // If the start intersection is a boundary event but its defining vertex is on the other side of the polygon, there is nothing to do
    if (startIntersection->getEventType() == 2 && startIntersection->belongsToStart() != fromStart) {
        return;
    }

    Point startPoint = getPolygonEdgeStartPoint(startIntersection, fromStart, pivotPointIndex);
    Point endPoint = endIntersection->getIntersection();
    Point pivotPoint = shortestPath.at(pivotPointIndex)->getPoint();
    std::vector<Point> verticesToLineOfSight = startIntersection->getPathToLineOfSight(fromStart);
    Point lastPointToLos = verticesToLineOfSight.at(verticesToLineOfSight.size() - 1);
    // If the path does not start at the edge start point, there is nothing do
    if (lastPointToLos != startPoint) {
        return;
    }

    bool isOnPolygonEdge = isPathToLoSOnPolygonEdge(startPoint, pivotPoint, endPoint, lastPointToLos);

    startIntersection->setSptToLineOfSightOnPolygonEdge(
       isOnPolygonEdge,
       fromStart
    );
    startIntersection->setPathToSemiCirclesIsFree(
       !isOnPolygonEdge,
       fromStart
    );
}
