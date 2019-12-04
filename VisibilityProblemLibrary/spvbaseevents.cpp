#include "spvbaseevents.h"

SPV::PolygonTriangle* SPV::BaseEvents::handleIntersection(PolygonTriangle *startTriangle, PolygonTriangle *endTriangle, EventOnShortestPath *spEvent, bool goLeft, bool calculateEndpoint, bool intersectionBelongsToStart, int eventType) {
    PolygonTriangle *currentTriangle = startTriangle;
    PolygonTriangle *lastTriangleWithIntersection = startTriangle;
    Point pOnShortestPath = spEvent->getSecondDefiningPoint();
    Point currentVertex = spEvent->getFirstDefiningPoint();
    Point lastIntersection;
    Point lastFoundSeg1;
    Point lastFoundSeg2;
    Ray r;
    bool finished = false;
    bool found = false;
    K::FT lastDistanceToIntersection = -1;
    K::FT currentDistanceToIntersection;
    if (calculateEndpoint) {
        r = Ray(spEvent->getFirstDefiningPoint(), spEvent->getSecondDefiningPoint());
    } else {
        r = Ray(spEvent->getSecondDefiningPoint(), spEvent->getFirstDefiningPoint());
    }

    std::vector<int> indices;
    do {
        finished = currentTriangle == endTriangle;
        for (int j = 0; j < 3; j++) {
            std::cout << currentTriangle->getFace()->vertex(j)->point() << std::endl;
        }
        std::cout << "" << std::endl;

        indices = currentTriangle->getRightToLeftIndices();
        for (int i = 0; i < indices.size() - 1; i++) {
            int index1 = indices.at(i);
            int index2 = indices.at(i + 1);
            Point seg1 = currentTriangle->getFace()->vertex(index1)->point();
            Point seg2 = currentTriangle->getFace()->vertex(index2)->point();
            Segment s = Segment(seg1, seg2);
            if (CGAL::do_intersect(r, s)) {
                CGAL::cpp11::result_of<Intersect_2(Ray, Segment)>::type
                    result = intersection(r, s);
                if (result) {
                    if (const Point* p = boost::get<Point>(&*result)) {
                        Point is = Point(p->x(), p->y());
                        currentDistanceToIntersection = CGAL::squared_distance(pOnShortestPath, is);
                        if ((lastDistanceToIntersection == -1 || currentDistanceToIntersection <= lastDistanceToIntersection) && !gU.pointsAreEqual(is, pOnShortestPath) && !gU.pointsAreEqual(is, currentVertex)) {
                            lastDistanceToIntersection = CGAL::squared_distance(pOnShortestPath, is);
                            lastIntersection = Point(p->x(), p->y());
                            lastFoundSeg1 = seg1;
                            lastFoundSeg2 = seg2;
                            lastTriangleWithIntersection = currentTriangle;
                            found = true;
                        }
                    }
                }
            }
        }
        if (goLeft) {
            currentTriangle = currentTriangle->getLeftTriangle();
        } else {
            currentTriangle = currentTriangle->getRightTriangle();
        }
    } while(!finished);

    if (!found) {
        return startTriangle;
    }
    if (calculateEndpoint) {
        spEvent->setSecondPointIntersection(lastIntersection);
    } else {
        spEvent->setFirstPointIntersection(lastIntersection);
    }
    EventIntersection* newIntersection = new EventIntersection(
        eventType,
        pOnShortestPath,
        lastIntersection,
        lastFoundSeg1,
        lastFoundSeg2
    );
    newIntersection->setBelongsToStart(intersectionBelongsToStart);
    lastTriangleWithIntersection->getFace()->info().addEventIntersection(newIntersection);
    eventIntersections.push_back(newIntersection);
    return lastTriangleWithIntersection;
}

SPV::PolygonTriangle* SPV::BaseEvents::findTriangleWithIntersectionEvent(PolygonTriangle *startTriangle, Point intersection, bool goLeft) {
    CDT::Face_handle currentFace;
    PolygonTriangle* currentTriangle = startTriangle;
int j = 1;
    do {
        currentFace = currentTriangle->getFace();
        for (unsigned i = 0; i < 3; i++) {
            if (i == 0) {
                std::cout << "Triangle " << j <<std::endl;
                j++;
            }
            std::cout << i << ": " << currentFace->vertex(i)->point() <<std::endl;
        }
        boost::variant<bool, SPV::EventIntersection*> intersectResult =
                currentFace->info().getEventIntersectionForIntersection(intersection);
        if (intersectResult.type() != typeid(bool)) {
            return currentTriangle;
        }
        if (goLeft) {
            currentTriangle = currentTriangle->getLeftTriangle();
        } else {
            currentTriangle = currentTriangle->getRightTriangle();
        }
    } while (currentTriangle != startTriangle);
    return currentTriangle;
}

std::pair<SPV::PolygonTriangle*, Segment> SPV::BaseEvents::findTriangleWithIntersection(PolygonTriangle *startTriangle, Point intersection, bool goLeft) {
    CDT::Face_handle currentFace;
    PolygonTriangle* currentTriangle = startTriangle;
    do {
        std::vector<int> indices = currentTriangle->getRightToLeftIndices();
        currentFace = currentTriangle->getFace();
        for (unsigned i = 0; i < indices.size() - 1; i++) {
            Segment s = Segment(currentFace->vertex(indices.at(i))->point(), currentFace->vertex(indices.at(i + 1))->point());
            if (gU.isPointOnSegment(s, intersection)) {
                return std::make_pair(currentTriangle, s);
            }
        }
        if (goLeft) {
            currentTriangle = currentTriangle->getLeftTriangle();
        } else {
            currentTriangle = currentTriangle->getRightTriangle();
        }
    } while (currentTriangle != startTriangle);
    std::cout << "A so a schmarrn" << std::endl;
}

SPV::PolygonTriangle* SPV::BaseEvents::findTriangleWithFirstPoint(PolygonTriangle *startTriangle, Point firstPoint, bool goLeft) {
    CDT::Face_handle currentFace;
    Point currentPoint;
    PolygonTriangle* currentTriangle = startTriangle;
    std::vector<EventIntersection*> intersections;
    std::vector<int> indices;

    do {
        indices = currentTriangle->getRightToLeftIndices();
        currentFace = currentTriangle->getFace();
        if (goLeft) {
            currentPoint = currentFace->vertex(indices.at(0))->point();
            if (currentPoint == firstPoint) {
                return currentTriangle;
            }
            currentTriangle = currentTriangle->getLeftTriangle();
        } else {
            currentPoint = currentFace->vertex(indices.at(indices.size() - 1))->point();
            if (currentPoint == firstPoint) {
                return currentTriangle;
            }
            currentTriangle = currentTriangle->getRightTriangle();
        }
    } while (currentTriangle != startTriangle);
    return currentTriangle;
}

Point SPV::BaseEvents::getIntersectionOnOppositeSide(EventIntersection* ei, unsigned pivotPointIndex) {
    unsigned shortestPathSize = shortestPath.size();
    boost::variant<bool, EventOnShortestPath*> result = shortestPath.at(pivotPointIndex)->getFaceHandle()->info().getShortestPathEventByIntersection(ei->getIntersection());

    // Check the surrounding pivot points if the event is not found
    if (result.type() == typeid(bool)) {
        if (pivotPointIndex < shortestPathSize - 2) {
            result = shortestPath.at(pivotPointIndex + 1)->getFaceHandle()->info().getShortestPathEventByIntersection(ei->getIntersection());
        }
        if (result.type() == typeid(bool) && pivotPointIndex >= 2) {
            result = shortestPath.at(pivotPointIndex - 1)->getFaceHandle()->info().getShortestPathEventByIntersection(ei->getIntersection());
        }
    }
    if (result.type() == typeid(bool)) {
        std::cout << "Problem in gewtIntersectionOnOppositeSide" << std::endl;
    }

    EventOnShortestPath* spEvent = boost::get<EventOnShortestPath*>(result);
    if (spEvent->getFirstPointIntersection() == ei->getIntersection() || spEvent->getSecondPointIntersection() == ei->getIntersection()) {
        return spEvent->getFirstPointIntersection() == ei->getIntersection() ? spEvent->getSecondPointIntersection() : spEvent->getFirstPointIntersection();
    }
    std::cout << "Problem in gewtIntersectionOnOppositeSide 2" << std::endl;
    return spEvent->getFirstPointIntersection();
}

SPV::PolygonTriangle* SPV::BaseEvents::findStartTriangleForCurrentEvent(PolygonTriangle* currentTriangle, EventIntersection* ei, unsigned pivotPointIndex, bool goLeft, bool fromStart) {
    // If we're looking for the triangle for a path event, we can return early as the loop is finished
    if (ei->getEventType() == 1) {
        return currentTriangle;
    }
    // Event is boundary
    boost::variant<bool, EventOnShortestPath*> result = shortestPath.at(pivotPointIndex)->getFaceHandle()->info().getShortestPathEventByIntersection(ei->getIntersection());

    if (result.type() == typeid(bool)) {
        std::cout << "Problem in findStartTriangleForCurrentEvent" << std::endl;
    }
    EventOnShortestPath* spEvent = boost::get<EventOnShortestPath*>(result);
    Point polygonVertex = spEvent->getFirstDefiningPoint();

    if (ei->belongsToStart() == fromStart) {
        return findTriangleWithIntersectionEvent(currentTriangle, polygonVertex, goLeft);
    }
    return findTriangleWithIntersectionEvent(currentTriangle, ei->getIntersection(), goLeft);
}

SPV::PolygonTriangle* SPV::BaseEvents::findEndTriangleForCurrentEvent(PolygonTriangle* currentTriangle, EventIntersection* ei, unsigned pivotPointIndex, bool goLeft) {
    // If we're looking for the triangle for a path event, we can return early as the loop is finished
    if (ei->getEventType() == 1) {
        return currentTriangle;
    }
    // Event is boundary
    boost::variant<bool, EventOnShortestPath*> result = shortestPath.at(pivotPointIndex)->getFaceHandle()->info().getShortestPathEventByIntersection(ei->getIntersection());

    if (result.type() == typeid(bool)) {
        std::cout << "Problem in findEndTriangleForCurrentEvent" << std::endl;
    }
    return findTriangleWithIntersectionEvent(currentTriangle, getIntersectionOnOppositeSide(ei, pivotPointIndex), goLeft);
}

SPV::EventOnShortestPath* SPV::BaseEvents::getSPEvent(unsigned pivotPointIndex, Point intersection, bool fromStart) {
    boost::variant<bool, EventOnShortestPath*> result = shortestPath.at(pivotPointIndex)->getFaceHandle()->info().getShortestPathEventByIntersection(intersection);
    if (result.type() == typeid(bool)) {
        ShortestPathEntry* nextShortestPathEntry = shortestPath.at(pivotPointIndex);
        // No shortest path events are stored in the last and first entry, so be sure to set the indices correctly
        if (fromStart && pivotPointIndex < shortestPath.size() - 2) {
            nextShortestPathEntry = shortestPath.at(pivotPointIndex + 1);
        } else if (pivotPointIndex > 1) {
            nextShortestPathEntry = shortestPath.at(pivotPointIndex - 1);
        }
        result = nextShortestPathEntry->getFaceHandle()->info().getShortestPathEventByIntersection(intersection);

        // The spEvent must belong to a different pivot point, try and find it
        if (result.type() == typeid(bool)) {
            bool finished = false;
            unsigned numberOfLoops = 1;
            while (!finished) {
                if (fromStart) {
                    if (pivotPointIndex - numberOfLoops >= 0) {
                        nextShortestPathEntry = shortestPath.at(pivotPointIndex - numberOfLoops);
                        result = nextShortestPathEntry->getFaceHandle()->info().getShortestPathEventByIntersection(intersection);
                    } else {
                        finished = true;
                    }
                } else {
                    if (pivotPointIndex + numberOfLoops < shortestPath.size()) {
                        nextShortestPathEntry = shortestPath.at(pivotPointIndex + numberOfLoops);
                        result = nextShortestPathEntry->getFaceHandle()->info().getShortestPathEventByIntersection(intersection);
                    } else {
                        finished = true;
                    }

                }
                numberOfLoops++;
                finished = finished || result.type() != typeid(bool);
            }
        }
    }
    if (result.type() == typeid(bool)) {
        std::cout << "No event for " << intersection << " at pivot point " << pivotPointIndex << std:: endl;
    }
    return boost::get<EventOnShortestPath*>(result);
}

Point SPV::BaseEvents::getClosestDefiningPoint(EventIntersection *startIntersection, bool fromStart, unsigned pivotPointIndex) {
    EventOnShortestPath *spEvent = getSPEvent(pivotPointIndex, startIntersection->getIntersection(), fromStart);
    if (fromStart) {
        return spEvent->getFirstDefiningPoint();
    } else {
        return spEvent->getSecondDefiningPoint();
    }
}

/**
 * All intersections on a polygon edge are orderd from start to end. If the polygon is traversed in the
 * same order, then intersections should be traversered from the start, otherwise from the end
 *
 * @brief SPV::BendEvents::shouldTraverseIntersectionsFromStart
 * @param startEdge
 * @param ei
 * @return
 */
bool SPV::BaseEvents::shouldTraverseIntersectionsFromStart(Point startEdge, EventIntersection *ei) {
    return startEdge == ei->getSegmentStart();
}


SPV::EventIntersection* SPV::BaseEvents::getNextEvent
(
    EventIntersection* startIntersection,
    bool goLeft,
    unsigned pivotPointIndex,
    bool fromStart,
    bool setStartTriangleAndHandled
) {
    PolygonTriangle* currentTriangle = startTriangle;
    CDT::Face_handle polygonEdgeFace;
    EventIntersection *intersectionOnEdge;
    bool foundCurrentIntersection = false;
    std::vector<int> rightToLeftIndices;
    Point segStart;
    Point segEnd;
    bool finished = false;
    EventOnShortestPath *spEvent;

    do {
        polygonEdgeFace = currentTriangle->getFace();
        rightToLeftIndices = currentTriangle->getRightToLeftIndices();
        int numberOfEdges = rightToLeftIndices.size() - 1;
        int numberOfLoops = 0;
        while (numberOfLoops < numberOfEdges) {
            if (goLeft) {
                segStart = polygonEdgeFace->vertex(rightToLeftIndices.at(numberOfLoops))->point();
                segEnd = polygonEdgeFace->vertex(rightToLeftIndices.at(numberOfLoops + 1))->point();
            } else {
                segStart = polygonEdgeFace->vertex(rightToLeftIndices.at(numberOfEdges - numberOfLoops))->point();
                segEnd = polygonEdgeFace->vertex(rightToLeftIndices.at(numberOfEdges - (numberOfLoops + 1)))->point();
            }
            numberOfLoops++;

            boost::variant<bool, std::vector<SPV::EventIntersection*>> result =
                polygonEdgeFace->info().getIntersectionsForSegment(segStart, segEnd);
            if (result.type() == typeid(bool)) {
                continue;
            }
            std::vector<EventIntersection*> currentIntersections = boost::get<std::vector<EventIntersection*>>(result);
            bool traverseFromStart = shouldTraverseIntersectionsFromStart(segStart, currentIntersections.at(0));

            // If the start intersection has a change in direction, the start of the current segment needs to be checked
            // against the defining point
            if (startIntersection->getHasChangeInDirection()) {
                foundCurrentIntersection = getClosestDefiningPoint(startIntersection, fromStart, pivotPointIndex) == segStart;
            }

            if (traverseFromStart) {
                for (unsigned j = 0; j < currentIntersections.size(); j++) {
                    intersectionOnEdge = currentIntersections.at(j);
                    if (foundCurrentIntersection == true) {
                        // If the event was already handled, don't consider it again
                        spEvent = getSPEvent(pivotPointIndex, intersectionOnEdge->getIntersection(), fromStart);
                        if (spEvent->wasHandled(fromStart)) {
                            continue;
                        }
                        finished = true;
                        if (setStartTriangleAndHandled) {
                            startTriangle = currentTriangle;
                            spEvent->setHandled(fromStart);
                        }
                        return currentIntersections.at(j);
                    } else if (intersectionOnEdge->getIntersection() == startIntersection->getIntersection()) {
                        foundCurrentIntersection = true;
                    }
                }
            } else {
                for (int j = currentIntersections.size() - 1; j >= 0; j--) {
                    intersectionOnEdge = currentIntersections.at(j);
                    if (foundCurrentIntersection == true) {
                        // If the event was already handled, don't consider it again
                        spEvent = getSPEvent(pivotPointIndex, intersectionOnEdge->getIntersection(), fromStart);
                        if (spEvent->wasHandled(fromStart)) {
                            continue;
                        }
                        finished = true;
                        if (setStartTriangleAndHandled) {
                            startTriangle = currentTriangle;
                            spEvent->setHandled(fromStart);
                        }
                        return currentIntersections.at(j);
                    } else if (intersectionOnEdge->getIntersection() == startIntersection->getIntersection()) {
                        foundCurrentIntersection = true;
                    }
                }
            }
        }
        if (goLeft) {
            currentTriangle = currentTriangle->getLeftTriangle();
        } else {
            currentTriangle = currentTriangle->getRightTriangle();
        }
    } while (finished == false);

    std::cout << "No next intersection found, we got a Problem" << std::endl;
    return startIntersection;
}


bool SPV::BaseEvents::isPathToLoSOnPolygonEdge(Point startPoint, Point pivotPoint, Point endPoint, Point lastPointOnLoS) {
    Line l = Line(startPoint, pivotPoint);

    // If the end point is on the same side of the perpendicular line as the pivot point,
    // the perpendicular line is outside the polygon, so the shortest path to the LoS will follow the polygon edge.
    if (gU.isOnLeftSideOfPerpendicularLine(l, lastPointOnLoS, pivotPoint)) {
        return gU.isOnLeftSideOfPerpendicularLine(l, lastPointOnLoS, endPoint);
    } else {
        return gU.isOnRightSideOfPerpendicularLine(l, lastPointOnLoS, endPoint);
    }
}

Point SPV::BaseEvents::getPolygonEdgeStartPoint(EventIntersection *startIntersection, bool fromStart, unsigned pivotPointIndex) {
    EventOnShortestPath* spEvent;
    // Sanity check: only interested in path and boundary events
    if (startIntersection->getEventType() > 2) {
        return startIntersection->getIntersection();
    }

        // Handle path events
    if (startIntersection->getEventType() == 1) {
        if (startIntersection->getHasChangeInDirection() == false) {
            return startIntersection->getIntersection();
        }
        return getClosestDefiningPoint(startIntersection, fromStart, pivotPointIndex);
    }

    // Now boundary events
    // If the defining vertex is on the other side of the polygon, return the intersection
    if (startIntersection->belongsToStart() != fromStart) {
        return startIntersection->getIntersection();
    }
    // Otherwise the polygon edge starts on the polygon vertex
    spEvent = getSPEvent(pivotPointIndex, startIntersection->getIntersection(), fromStart);
    return spEvent->getFirstDefiningPoint();
}
