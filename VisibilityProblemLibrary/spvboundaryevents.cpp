#include "spvboundaryevents.h"

std::vector<SPV::EventIntersection *> SPV::BoundaryEvents::calculateBoundaryEvents() {
    std::vector<int> indices;

    for (int i = 0; i < shortestPath.size(); i++) {
        std::cout << shortestPath.at(i)->getPoint() <<std::endl;
    }
    if (shortestPath.size() < 3) {
        return eventIntersections;
    }

    PolygonTriangle *firstTriangleStart = eventMap.getStartTriangle();
    PolygonTriangle *firstTriangleEnd = eventMap.getStartTriangle();
    PolygonTriangle *nextTriangleStart = eventMap.getStartTriangle();
    PolygonTriangle *nextTriangleEnd = eventMap.getStartTriangle();
    bool previousGoLeft;

    for (int i = 0; i < shortestPath.size() - 2; i++) {
        Point firstOnShortestPath = shortestPath.at(i)->getPoint();
        Point secondOnShortestPath = shortestPath.at(i + 1)->getPoint();
        Point thirdOnShortestPath = shortestPath.at(i + 2)->getPoint();
        bool goLeft = gU.isOnRightSide(firstOnShortestPath, secondOnShortestPath, thirdOnShortestPath);

        CDT::Face_handle currentFace = shortestPath.at(i + 1)->getFaceHandle();
        EventOnShortestPath* spEvent = shortestPath.at(i + 1)->getFaceHandle()->info().getShortestPathEvent(firstOnShortestPath, secondOnShortestPath);
        Point firstIntersectionStart = spEvent->getFirstPointIntersection();
        Point firstIntersectionEnd = spEvent->getSecondPointIntersection();
        if (shortestPath.at(i + 2)->isEndPoint()) {
            spEvent = shortestPath.at(i + 1)->getFaceHandle()->info().getShortestPathEvent(secondOnShortestPath, thirdOnShortestPath);
        } else {
            spEvent = shortestPath.at(i + 2)->getFaceHandle()->info().getShortestPathEvent(secondOnShortestPath, thirdOnShortestPath);
        }
        Point nextIntersectionStart = spEvent->getFirstPointIntersection();
        Point nextIntersectionEnd = spEvent->getSecondPointIntersection();

        if (i == 0) {
            firstTriangleStart = findTriangleWithIntersectionEvent(firstTriangleStart, firstIntersectionStart, goLeft);
            firstTriangleEnd = findTriangleWithIntersectionEvent(firstTriangleEnd, firstIntersectionEnd, goLeft);

            nextTriangleStart = findTriangleWithIntersectionEvent(nextTriangleStart, nextIntersectionStart, goLeft);
            nextTriangleEnd = findTriangleWithIntersectionEvent(nextTriangleEnd, nextIntersectionEnd, goLeft);

        } else {
            if (goLeft != previousGoLeft) {
                firstTriangleStart = findTriangleWithFirstPoint(firstTriangleStart, firstOnShortestPath, goLeft);
                nextTriangleStart = findTriangleWithIntersectionEvent(firstTriangleStart, nextIntersectionStart, goLeft);
            } else {
                firstTriangleStart = nextTriangleStart;
                nextTriangleStart = findTriangleWithIntersectionEvent(nextTriangleStart, nextIntersectionStart, goLeft);
            }
            firstTriangleEnd = nextTriangleEnd;

            nextTriangleStart = findTriangleWithIntersectionEvent(nextTriangleStart, nextIntersectionStart, goLeft);
            nextTriangleEnd = findTriangleWithIntersectionEvent(nextTriangleEnd, nextIntersectionEnd, goLeft);
        }
        previousGoLeft = goLeft;

        calculateEventsBetween2PathEvents(
            firstTriangleStart,
            firstTriangleEnd,
            nextTriangleStart,
            nextTriangleEnd,
            firstIntersectionStart,
            firstIntersectionEnd,
            nextIntersectionStart,
            nextIntersectionEnd,
            firstOnShortestPath,
            secondOnShortestPath,
            thirdOnShortestPath,
            true,
            currentFace,
            goLeft
        );
        calculateEventsBetween2PathEvents(
            firstTriangleEnd,
            firstTriangleStart,
            nextTriangleEnd,
            nextTriangleStart,
            firstIntersectionEnd,
            firstIntersectionStart,
            nextIntersectionEnd,
            nextIntersectionStart,
            firstOnShortestPath,
            secondOnShortestPath,
            thirdOnShortestPath,
            false,
            currentFace,
            goLeft
        );
    }
    return eventIntersections;
}

void SPV::BoundaryEvents::calculateEventsBetween2PathEvents (
        PolygonTriangle *startTriangle,
        PolygonTriangle *endTriangle,
        PolygonTriangle *nextStartTriangle,
        PolygonTriangle *nextEndTriangle,
        Point firstIntersectionStart,
        Point firstIntersectionEnd,
        Point nextIntersectionStart,
        Point nextIntersectionEnd,
        Point startPointOnShortestPath,
        Point pivotPointOnShortestPath,
        Point nextPointOnShortestPath,
        bool vertexIsStart,
        CDT::Face_handle currentFace,
        bool goLeft
) {
    PolygonTriangle* currentTriangle = startTriangle;
    EventOnShortestPath *spEvent;
    Point currentVertex;
    bool finished;
    std::vector<int> indices;
    EventIntersection* ei;

    std::cout << "First intersection start" <<std::endl;
    std::cout << firstIntersectionStart <<std::endl;
    std::cout << "First intersection End" <<std::endl;
    std::cout << firstIntersectionEnd <<std::endl;
    std::cout << "Next intersection start" <<std::endl;
    std::cout << nextIntersectionStart <<std::endl;
    std::cout << "Next intersection end" <<std::endl;
    std::cout << nextIntersectionEnd <<std::endl;
    do {
        std::cout << "CURRENT" <<std::endl;
        for (int j = 0; j < 3; j++) {
            std::cout << currentTriangle->getFace()->vertex(j)->point() << std::endl;
        }
        std::cout << "Next" <<std::endl;
        for (int j = 0; j < 3; j++) {
            std::cout << nextStartTriangle->getFace()->vertex(j)->point() << std::endl;
        }
        std::cout << "End" <<std::endl;
        for (int j = 0; j < 3; j++) {
            std::cout << endTriangle->getFace()->vertex(j)->point() << std::endl;
        }
        finished = currentTriangle == nextStartTriangle;
        indices = currentTriangle->getRightToLeftIndices();
        if (goLeft) {
            for (int i = 0; i < indices.size(); i++) {
                // Avoid duplication
                if (i == 0 && currentVertex == currentTriangle->getFace()->vertex(indices.at(i))->point()) {
                    continue;
                }
                currentVertex = currentTriangle->getFace()->vertex(indices.at(i))->point();

                if (currentVertex == startPointOnShortestPath || currentVertex == pivotPointOnShortestPath || currentVertex == nextPointOnShortestPath) {
                    continue;
                }
                if (!isPointSPTParent(vertexIsStart, currentVertex, pivotPointOnShortestPath, currentTriangle->getFace()->vertex(indices.at(i)))) {
                    continue;
                }

                if (
                    gU.isOnLeftSide(firstIntersectionStart, firstIntersectionEnd, currentVertex) &&
                    gU.isOnRightSide(nextIntersectionStart, nextIntersectionEnd, currentVertex)
                ) {
                    if (vertexIsStart) {
                        spEvent = new EventOnShortestPath(currentVertex, pivotPointOnShortestPath);
                        // If the neighbouring points are on the same side, the vertex is not the end intersection
                        if (
                            gU.isOnLeftSide(pivotPointOnShortestPath, currentVertex, currentTriangle->getLeftPoint(currentVertex)) ==
                            gU.isOnLeftSide(pivotPointOnShortestPath, currentVertex, currentTriangle->getRightPoint(currentVertex))
                        ) {
                            handleIntersection(startTriangle, nextStartTriangle, spEvent, goLeft, false, vertexIsStart);
                        } else {
                            spEvent->setFirstPointIntersection(currentVertex);
                            ei = new EventIntersection(
                                2,
                                pivotPointOnShortestPath,
                                currentVertex,
                                currentVertex,
                                getSegmentEndPointForVertex(currentTriangle, i)
                            );
                            ei->setBelongsToStart(vertexIsStart);
                            currentTriangle->getFace()->info().addEventIntersection(ei);
                            eventIntersections.push_back(ei);
                        }
                    } else {
                        spEvent = new EventOnShortestPath(currentVertex, pivotPointOnShortestPath);

                        // If the neighbouring points are on the same side, the vertex is not the end intersection
                        if (
                            gU.isOnLeftSide(pivotPointOnShortestPath, currentVertex, currentTriangle->getLeftPoint(currentVertex)) ==
                            gU.isOnLeftSide(pivotPointOnShortestPath, currentVertex, currentTriangle->getRightPoint(currentVertex))
                        ) {
                            startTriangle = handleIntersection(startTriangle, nextStartTriangle, spEvent, goLeft, false, vertexIsStart);
                        } else {
                            spEvent->setFirstPointIntersection(currentVertex);
                            ei = new EventIntersection(
                                2,
                                pivotPointOnShortestPath,
                                currentVertex,
                                currentVertex,
                                getSegmentEndPointForVertex(currentTriangle, i)
                            );
                            ei->setBelongsToStart(vertexIsStart);
                            currentTriangle->getFace()->info().addEventIntersection(ei);
                            eventIntersections.push_back(ei);
                        }
                    }
                    endTriangle = handleIntersection(endTriangle, nextEndTriangle, spEvent, goLeft, true, vertexIsStart);
                    for (int j = 0; j < 3; j++) {
                        std::cout << endTriangle->getFace()->vertex(j)->point() << std::endl;
                    }
                    currentFace->info().addShortestPathEvent(spEvent);
                    eventsOnShortestPath.push_back(spEvent);
                }
            }
            currentTriangle = currentTriangle->getLeftTriangle();
        } else {
            for (int i = indices.size() - 1; i >= 0; i--) {
                // Avoid duplication
                if (i == indices.size() -1 && currentVertex == currentTriangle->getFace()->vertex(indices.at(i))->point()) {
                    continue;
                }
                currentVertex = currentTriangle->getFace()->vertex(indices.at(i))->point();

                if (currentVertex == startPointOnShortestPath || currentVertex == pivotPointOnShortestPath || currentVertex == nextPointOnShortestPath) {
                    continue;
                }
                if (!isPointSPTParent(vertexIsStart, currentVertex, pivotPointOnShortestPath, currentTriangle->getFace()->vertex(indices.at(i)))) {
                    continue;
                }
                if (
                    gU.isOnRightSide(firstIntersectionStart, firstIntersectionEnd, currentVertex) &&
                    gU.isOnLeftSide(nextIntersectionStart, nextIntersectionEnd, currentVertex)
                ) {
                    if (vertexIsStart) {
                        spEvent = new EventOnShortestPath(currentVertex, pivotPointOnShortestPath);

                        // If the neighbouring points are on the same side, the vertex is not the end intersection
                        if (
                            gU.isOnLeftSide(pivotPointOnShortestPath, currentVertex, currentTriangle->getLeftPoint(currentVertex)) ==
                            gU.isOnLeftSide(pivotPointOnShortestPath, currentVertex, currentTriangle->getRightPoint(currentVertex))
                        ) {
                            handleIntersection(startTriangle, nextStartTriangle, spEvent, goLeft, false, vertexIsStart);
                        } else {
                            spEvent->setFirstPointIntersection(currentVertex);
                            ei = new EventIntersection(
                                2,
                                pivotPointOnShortestPath,
                                currentVertex,
                                currentVertex,
                                getSegmentEndPointForVertex(currentTriangle, i)
                            );
                            ei->setBelongsToStart(vertexIsStart);
                            currentTriangle->getFace()->info().addEventIntersection(ei);
                            eventIntersections.push_back(ei);
                        }
                    } else {                        
                        spEvent = new EventOnShortestPath(currentVertex, pivotPointOnShortestPath);

                        // If the neighbouring points are on the same side, the vertex is not the end intersection
                        if (
                            gU.isOnLeftSide(pivotPointOnShortestPath, currentVertex, currentTriangle->getLeftPoint(currentVertex)) ==
                            gU.isOnLeftSide(pivotPointOnShortestPath, currentVertex, currentTriangle->getRightPoint(currentVertex))
                        ) {
                            startTriangle = handleIntersection(startTriangle, nextStartTriangle, spEvent, goLeft, false, vertexIsStart);
                        } else {
                            spEvent->setFirstPointIntersection(currentVertex);
                            ei = new EventIntersection(
                                2,
                                pivotPointOnShortestPath,
                                currentVertex,
                                currentVertex,
                                getSegmentEndPointForVertex(currentTriangle, i)
                            );
                            ei->setBelongsToStart(vertexIsStart);
                            currentTriangle->getFace()->info().addEventIntersection(ei);
                            eventIntersections.push_back(ei);
                        }
                    }
                    endTriangle = handleIntersection(endTriangle, nextEndTriangle, spEvent, goLeft, true, vertexIsStart);
                    currentFace->info().addShortestPathEvent(spEvent);
                    eventsOnShortestPath.push_back(spEvent);
                }
            }
            currentTriangle = currentTriangle->getRightTriangle();
        }
    } while (finished == false);
}

Point SPV::BoundaryEvents::getSegmentEndPointForVertex(PolygonTriangle* currentTriangle, unsigned currentIndex) {
    std::vector<int> indices = currentTriangle->getRightToLeftIndices();
    if (currentIndex > 0) {
        return currentTriangle->getFace()->vertex(indices.at(currentIndex - 1))->point();
    }
    return currentTriangle->getFace()->vertex(indices.at(1))->point();
}

bool SPV::BoundaryEvents::isPointSPTParent(bool fromStart, Point currentPoint, Point parentPoint, CDT::Vertex_handle currentVertex) {
    std::vector<PointOnShortestPath *> currentTree;
    PointOnShortestPath* currentPointOnSpt;
    std::vector<int> currentIndices;
    if (fromStart) {
        currentTree = shortestPathTreeFromEnd;
    } else {
        currentTree = shortestPathTree;
    }
    bool foundCurrentPointOnSPT = false;
    Face_circulator faceCirculator = currentVertex->incident_faces(),
            done(faceCirculator);
    if (faceCirculator != 0) {
        do {
            bool check = false;
            if (fromStart && faceCirculator->info().getHasSptFromEndIndices()) {
                check = true;
                currentIndices = faceCirculator->info().getSptFromEndIndices();
            } else if (!fromStart && faceCirculator->info().getHasSptFromStartIndices()) {
                check = true;
                currentIndices = faceCirculator->info().getSptFromStartIndices();
            }
            if (check == true) {
                for (int i = 0; i < currentIndices.size(); i ++) {
                    int index = currentIndices.at(i);
                    currentPointOnSpt = currentTree.at(index);
                    if (currentPointOnSpt->getCurrentPoint() == currentPoint) {
                        foundCurrentPointOnSPT = true;
                        if (!currentPointOnSpt->isFinalPoint()) {
                            currentPointOnSpt = currentPointOnSpt->getPreviousPoint();
                            Point p = currentPointOnSpt->getCurrentPoint();
                            if (currentPointOnSpt->getCurrentPoint() == parentPoint) {
                                return true;
                            }
                        }
                    }
                }
            }
        } while (++faceCirculator != done && foundCurrentPointOnSPT == false);
    }
    return false;
}

