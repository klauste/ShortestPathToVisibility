#include "spvshortestpath.h"

SPV::ShortestPath::~ShortestPath()
{
    shortestPathTree.clear();
    shortestPathTreeFromEnd.clear();
    facesFromStartToEnd.clear();
    pathEvents.clear();
    eventsOnShortestPath.clear();
    boundaryEventIntersections.clear();
    bendEventIntersections.clear();
    boundaryEvents.getEventsOnShortestPath().clear();
    bendEvents.getEventsOnShortestPath().clear();
}

void SPV::ShortestPath::initialize(const Polygon &p)
{
    polygon = p;
    cdt.insert_constraint(polygon.vertices_begin(), polygon.vertices_end(), true);

    //Mark faces that are inside the domain bounded by the polygon
    markDomains(cdt);
    eventMap = EventMap(polygon, cdt);
}

const CDT& SPV::ShortestPath::getTriangulation() {
    return cdt;
}

const std::vector<SPV::ShortestPathEntry *>& SPV::ShortestPath::getSleevePath(int i) {
    if (i == 1) {
        return funnelLeftPath;
    }
    if (i == 2) {
    return funnelRightPath;
    }
    if (i == 3) {
        return funnelTail;
    }
}

void SPV::ShortestPath::markDomains(
        CDT& ct,
        CDT::Face_handle start,
        int index,
        std::list<CDT::Edge>& border
)
{
    if(start->info().getNestingLevel() != -1){
        return;
    }
    std::list<CDT::Face_handle> queue;
    queue.push_back(start);
    while(! queue.empty()){
        CDT::Face_handle fh = queue.front();
        queue.pop_front();
        if(fh->info().getNestingLevel() == -1){
            fh->info().setNestingLevel(index);
            for(int i = 0; i < 3; i++){
                CDT::Edge e(fh,i);
                CDT::Face_handle n = fh->neighbor(i);
                if(n->info().getNestingLevel() == -1){
                    if(ct.is_constrained(e)) border.push_back(e);
                    else queue.push_back(n);
                }
            }
        }
    }
}

void SPV::ShortestPath::markDomains(CDT& cdt) {
    for(CDT::All_faces_iterator it = cdt.all_faces_begin(); it != cdt.all_faces_end(); ++it){
        it->info().setNestingLevel(-1);
    }
    std::list<CDT::Edge> border;
    markDomains(cdt, cdt.infinite_face(), 0, border);
    while(! border.empty()){
        CDT::Edge e = border.front();
        border.pop_front();
        CDT::Face_handle n = e.first->neighbor(e.second);
        if(n->info().getNestingLevel() == -1){
            markDomains(cdt, n, e.first->info().getNestingLevel()+1, border);
        }
    }
}

bool SPV::ShortestPath::recursivelyfindEndPoint(TDS::Face_handle &currentFaceHandle) {
    bool endPointFoundOnPath = false;
    int previousIndex = facesFromStartToEnd.size() - 1;
    FaceOnPath *currentFaceOnPath = new FaceOnPath(currentFaceHandle);

    currentFaceOnPath->nextFaceIndex = -1;
    facesFromStartToEnd.push_back(currentFaceOnPath);

    Triangle t = cdt.triangle(currentFaceHandle);

    // If the end point is found, end the recursion by returning true
    if (t.has_on_bounded_side(endPoint->getPoint())) {
        return true;
    }

    // Recursively call the function for all the neighbors
    for (int i = 0; i < 3; i++) {
        TDS::Face_handle neighbor = currentFaceHandle->neighbor(i);
        if (neighbor->info().inDomain()) {
            // Only continue, if the neighbor is not the last face
            if (previousIndex < 0 || neighbor != facesFromStartToEnd[previousIndex]->currentFace) {
                endPointFoundOnPath = recursivelyfindEndPoint(neighbor);
                if (endPointFoundOnPath == true) {
                    currentFaceOnPath->nextFaceIndex = i;
                    break;
                }
            }
        }
    }

    // remove the current face handle
    if (endPointFoundOnPath == false) {
        facesFromStartToEnd.pop_back();
    }
    return endPointFoundOnPath;
}

bool SPV::ShortestPath::setFacesFromStartToEndPoint() {
    TDS::Face_handle currentFace;

    // Find the face containing the start point
    for (
         CDT::Finite_faces_iterator fit = cdt.finite_faces_begin();
         fit != cdt.finite_faces_end();
         fit++
         ) {
        if ( fit->info().inDomain() ) {
            currentFace = fit;
            Triangle t = cdt.triangle(fit);
            if (t.has_on_bounded_side(startPoint->getPoint())) {
                break;
            }
        }
    }
    return recursivelyfindEndPoint(currentFace);
}

void SPV::ShortestPath::setPoint(int index, float x, float y) {
    if (index == 0) {
        sPoint = Point(x, y);
        startPoint = new SPV::ShortestPathEntry(sPoint, 0);
    }
    if (index == 1) {
        ePoint = Point(x, y);
        endPoint = new SPV::ShortestPathEntry(ePoint, 2);
    }
}

bool SPV::ShortestPath::calculateShortestPath() {
    if (setFacesFromStartToEndPoint() == true) {
        FaceOnPath *currentFaceOnPath = facesFromStartToEnd.at(0);
        int lastIndex = facesFromStartToEnd.size() - 1;
        CDT::Face_handle currentFace = currentFaceOnPath->currentFace;
        CDT::Face_handle lastFace = facesFromStartToEnd.at(lastIndex)->currentFace;

        int nextFaceIndex = currentFaceOnPath->nextFaceIndex;
        funnelTail.push_back(startPoint);

        int vertexIndex = currentFace->ccw(nextFaceIndex);
        ShortestPathEntry *leftEntry = new ShortestPathEntry(currentFace, vertexIndex);
        funnelLeftPath.push_back(startPoint);
        funnelLeftPath.push_back(leftEntry);

        vertexIndex = currentFace->cw(nextFaceIndex);
        ShortestPathEntry *rightEntry = new ShortestPathEntry(currentFace, vertexIndex);
        funnelRightPath.push_back(startPoint);
        funnelRightPath.push_back(rightEntry);

        // Loop over all the diagonals
        for (int i = 1; i < facesFromStartToEnd.size() - 1; i++) {
            bool startOnLeftPath = true;
            currentFaceOnPath = facesFromStartToEnd.at(i);
            currentFace = currentFaceOnPath->currentFace;
            nextFaceIndex = currentFaceOnPath->nextFaceIndex;
            vertexIndex = currentFace->ccw(nextFaceIndex);
            std::vector<ShortestPathEntry *> forwardVector;
            ShortestPathEntry *nextEntry = new ShortestPathEntry(currentFace, vertexIndex);

            // Set next point to the point which is not on the current diagonal
            if (nextEntry->getPoint() == leftEntry->getPoint()) {
                startOnLeftPath = false;
                vertexIndex = currentFace->cw(nextFaceIndex);
                delete nextEntry;
                nextEntry = new ShortestPathEntry(currentFace, vertexIndex);
                rightEntry = nextEntry;

            } else {
                leftEntry = nextEntry;
            }

            // Check if nextPoint is part of the right or left sleeve
            if (startOnLeftPath) {
                // Add the elements from end to front to forwardVector
                for (int j = funnelRightPath.size() - 1; j >= 0; j--) {
                    forwardVector.push_back(funnelRightPath.at(j));
                    funnelRightPath.pop_back();
                }
                handleNextPoint(funnelLeftPath, forwardVector, nextEntry, false);
                for (int j = forwardVector.size() - 1; j >= 0; j--) {
                    funnelRightPath.push_back(forwardVector.at(j));
                }
            } else {
                for (int j = funnelLeftPath.size() - 1; j >= 0; j--) {
                    forwardVector.push_back(funnelLeftPath.at(j));
                    funnelLeftPath.pop_back();
                }
                handleNextPoint(funnelRightPath, forwardVector, nextEntry, true);
                for (int j = forwardVector.size() - 1; j >= 0; j--) {
                    funnelLeftPath.push_back(forwardVector.at(j));
                }
            }
        }
    }

    // Handle the last point
    std::vector<ShortestPathEntry *> forwardVector;
    for (int i = funnelRightPath.size() - 1; i >= 0; i--) {
        forwardVector.push_back(funnelRightPath.at(i));
        funnelRightPath.pop_back();
    }

    handleNextPoint(funnelLeftPath, forwardVector, endPoint, false);

    // Add the last points to the funnelTail
    for (int i = 1; i < funnelLeftPath.size(); i++) {
        ShortestPathEntry* currentEntry = funnelLeftPath.at(i);
        funnelTail.push_back(currentEntry);
        if (currentEntry->isMidPoint()) {
            currentEntry->getFaceHandle()->info().addShortestPathIndex(funnelTail.size() - 1);
        }
    }

    calculateShortestPathTree(false);
    calculateShortestPathTree(true);

    boundaryEvents = BoundaryEvents(funnelTail, eventMap, shortestPathTree, shortestPathTreeFromEnd);
    boundaryEventIntersections = boundaryEvents.calculateBoundaryEvents();
    bendEvents = BendEvents(funnelTail, eventMap);
    bendEventIntersections = bendEvents.calculateBendEvents();
    minimumCalculator = MinimumCalculator(funnelTail, eventMap);
    minimumCalculator.calculateMinima();
    std::vector<Minimum*> allMinima = minimumCalculator.getAllMinima();
    return false;
}

void SPV::ShortestPath::handleNextPoint(
    std::vector<ShortestPathEntry *> &backwardPath,
    std::vector<ShortestPathEntry *> &forwardPath,
    ShortestPathEntry *nextPoint,
    bool isBackwardPathOnTheRight
) {
    ShortestPathEntry* currentEntry;
    int backwardPathSize = backwardPath.size();

    // If the backward path consists only of the apex or of no point, just add the next point
    if (backwardPathSize <= 1) {
        backwardPath.push_back(nextPoint);
        return;
    }
    bool sideCheck;
    if (backwardPathSize > 1) {
        for (int i = backwardPathSize - 1; i > 0; i--) {
            if (isBackwardPathOnTheRight) {
                sideCheck = isOnRightSide(backwardPath.at(i - 1)->getPoint(), backwardPath.at(i)->getPoint(), nextPoint->getPoint());
            } else {
                sideCheck = isOnLeftSide(backwardPath.at(i - 1)->getPoint(), backwardPath.at(i)->getPoint(), nextPoint->getPoint());
            }
            if (sideCheck) {
                backwardPath.push_back(nextPoint);
                return;
            }
            // Remove the current point from the backward path
            backwardPath.pop_back();
        }
    }

    int forwardPathSize = forwardPath.size();

    // Check the apex
    if (forwardPathSize <= 1) {
        backwardPath.push_back(nextPoint);
        return;
    }
    if (forwardPathSize > 1) {
        if (isBackwardPathOnTheRight) {
            sideCheck = isOnRightSide(forwardPath.at(forwardPathSize - 1)->getPoint(), forwardPath.at(forwardPathSize - 2)->getPoint(), nextPoint->getPoint());
        } else {
            sideCheck = isOnLeftSide(forwardPath.at(forwardPathSize - 1)->getPoint(), forwardPath.at(forwardPathSize - 2)->getPoint(), nextPoint->getPoint());
        }
        if (sideCheck) {
            backwardPath.push_back(nextPoint);
            return;
        }
    }

    while (backwardPath.size() > 0) {
        backwardPath.pop_back();
    }

    // Check the forwardPath
    if (forwardPathSize > 1) {
        for (int i = forwardPathSize - 1; i > 0; i--) {
            if (isBackwardPathOnTheRight) {
                sideCheck = isOnRightSide(forwardPath.at(i)->getPoint(), forwardPath.at(i - 1)->getPoint(), nextPoint->getPoint());
            } else {
                sideCheck = isOnLeftSide(forwardPath.at(i)->getPoint(), forwardPath.at(i - 1)->getPoint(), nextPoint->getPoint());
            }
            if (sideCheck) {
                backwardPath.push_back(forwardPath.at(i));
                backwardPath.push_back(nextPoint);
                return;
            }
            currentEntry = forwardPath.at(i - 1);
            funnelTail.push_back(currentEntry);
            if (currentEntry->isMidPoint()) {
                currentEntry->getFaceHandle()->info().addShortestPathIndex(funnelTail.size() - 1);
            }
            forwardPath.pop_back();
        }
    }
    if (forwardPath.size() == 1) {
        backwardPath.push_back(forwardPath.at(0));
        backwardPath.push_back(nextPoint);
    }
}

// y grows towards bottom of screen so adjust checks
bool SPV::ShortestPath::isOnRightSide(Point p1, Point p2, Point p3) {
    Line l = Line(p1, p2);

    return l.has_on_positive_side(p3);
}

bool SPV::ShortestPath::isOnLeftSide(Point p1, Point p2, Point p3) {
    Line l = Line(p1, p2);

    return l.has_on_negative_side(p3);
}

void SPV::ShortestPath::calculateShortestPathTree(bool startFromEnd) {
    int oppositePointIndex, leftPointIndex, rightPointIndex;
    PointOnShortestPath* startPointOnTree;
    FaceOnPath *currentFaceOnPath;
    std::vector<SPV::PointOnShortestPath *> *currentShortestPathTree;


    if (startFromEnd) {
        int index = facesFromStartToEnd.size() - 1;
        currentFaceOnPath = facesFromStartToEnd.at(index);
        startPointOnTree = new PointOnShortestPath(endPoint);
        currentShortestPathTree = &shortestPathTreeFromEnd;
    } else {
        currentFaceOnPath = facesFromStartToEnd.at(0);
        startPointOnTree = new PointOnShortestPath(startPoint);
        currentShortestPathTree = &shortestPathTree;
    }
    currentShortestPathTree->push_back(startPointOnTree);
    if (startFromEnd) {
        currentFaceOnPath->currentFace->info().addSptFromEndIndex(currentShortestPathTree->size() - 1);
    } else {
        currentFaceOnPath->currentFace->info().addSptFromStartIndex(currentShortestPathTree->size() - 1);
    }


    CDT::Face_handle currentFace = currentFaceOnPath->currentFace;

    // add all points in the start triangle
    for (int i = 0; i < 3; i++) {
        currentShortestPathTree->push_back(
            new SPV::PointOnShortestPath(
                new ShortestPathEntry(currentFace, i),
                startPointOnTree
            )
        );
        if (startFromEnd) {
            currentFaceOnPath->currentFace->info().addSptFromEndIndex(currentShortestPathTree->size() - 1);
        } else {
            currentFaceOnPath->currentFace->info().addSptFromStartIndex(currentShortestPathTree->size() - 1);
        }
    }

    // recursively go through the funnels on all three sides
    for (oppositePointIndex = 0; oppositePointIndex < 3; oppositePointIndex++) {
        std::vector<SPV::PointOnShortestPath*> leftFunnel;
        std::vector<SPV::PointOnShortestPath*> rightFunnel;

        leftPointIndex = currentFace->ccw(oppositePointIndex);
        rightPointIndex = currentFace->cw(oppositePointIndex);

        leftFunnel.push_back(currentShortestPathTree->at(leftPointIndex + 1));
        rightFunnel.push_back(currentShortestPathTree->at(rightPointIndex + 1));

        splitFunnel(
            currentFace,
            oppositePointIndex,
            startPointOnTree,
            leftFunnel,
            rightFunnel,
            startFromEnd
        );
    }
}

void SPV::ShortestPath::setShortestPathMapInfo(
   CDT::Face_handle currentFace,
   int neighborIndex,
   SPV::PointOnShortestPath* apex,
   std::vector<SPV::PointOnShortestPath*> &funnel,
   bool startFromEnd
) {
    unsigned funnelSize = funnel.size();
    unsigned i, pointIndex;
    unsigned lastHandledPointOnShortestPath = funnelTail.size() - 1;

    if (startFromEnd) {
        lastHandledPointOnShortestPath = 0;
    }
    Point seg1, seg2, intersection;
    SPV::PointOnShortestPath *startPoint, *endPoint;
    SPV::EventOnShortestPath *region;
    SPV::EventIntersection* eventIntersection;
    CDT::Face_handle fh;

    pointIndex = currentFace->cw(neighborIndex);
    seg1 = currentFace->vertex(pointIndex)->point();

    pointIndex = currentFace->ccw(neighborIndex);
    seg2 = currentFace->vertex(pointIndex)->point();
    bool setStartPointIntersection = false;
    if (startFromEnd) {
        for (unsigned i = 0; i < funnelSize; i++) {
            std::cout << "Funnel " << i << ": " << funnel.at(i)->getCurrentPoint() << std::endl;
        }
    }

    if (funnelSize > 1) {
        for (i = funnelSize - 2; i > 0; i--) {
            endPoint = funnel.at(i);
            startPoint = funnel.at(i - 1);
            if (shouldAddPathEventForEntries(endPoint->getCurrentEntry(), startPoint->getCurrentEntry(), startFromEnd) == false) {
                continue;
            }

            if (startFromEnd) {
                bool foundRegion = false;
                Face_circulator faceCirculator = endPoint->getCurrentEntry()->getVertexHandle()->incident_faces(),
                        done(faceCirculator);
                if (faceCirculator != 0) {
                    do {
                      if (faceCirculator->info().getHasShortestPathEvent(endPoint->getCurrentPoint(), startPoint->getCurrentPoint()) == true) {
                        region = faceCirculator->info().getShortestPathEvent(endPoint->getCurrentPoint(), startPoint->getCurrentPoint());
                        foundRegion = true;
                      }
                    } while (++faceCirculator != done && foundRegion == false);
                  }
                if (foundRegion == false) {
                    if (startPoint->getCurrentEntry()->isMidPoint()) {
                        Face_circulator faceCirculator = startPoint->getCurrentEntry()->getVertexHandle()->incident_faces(),
                            done(faceCirculator);
                        if (faceCirculator != 0) {
                            do {
                                if (faceCirculator->info().getHasShortestPathEvent(endPoint->getCurrentPoint(), startPoint->getCurrentPoint()) == true) {
                                    region = faceCirculator->info().getShortestPathEvent(endPoint->getCurrentPoint(), startPoint->getCurrentPoint());
                                    foundRegion = true;
                                }
                            } while (++faceCirculator != done && foundRegion == false);
                        }
                    }
                    if (foundRegion == false) {
                        continue;
                    }
                }
            } else {
                region = new SPV::EventOnShortestPath(
                    startPoint->getCurrentPoint(),
                    endPoint->getCurrentPoint()
                );

                endPoint->getCurrentEntry()->getFaceHandle()->info().addShortestPathEvent(region);
                eventsOnShortestPath.push_back(region);
            }

            region->calculateIntersection(
                seg1,
                seg2,
                !startFromEnd
            );

            if (startFromEnd) {
                intersection = region->getFirstPointIntersection();
            } else {
                intersection = region->getSecondPointIntersection();
            }
            eventIntersection = new EventIntersection(
                 1,
                 startPoint->getCurrentPoint(),
                 intersection,
                 seg1,
                 seg2
            );
            currentFace->info().addEventIntersection(eventIntersection);
            pathEvents.push_back(eventIntersection);
        }
        endPoint = funnel.at(0);
        std::cout << "End point" << endPoint->getCurrentPoint() << std::endl;
        std::cout << "Apex" << apex->getCurrentPoint() << std::endl;

        if (shouldAddPathEventForEntries(endPoint->getCurrentEntry(), apex->getCurrentEntry(), startFromEnd) == false) {
            return;
        }

        if (startFromEnd) {
            if (apex->getCurrentEntry()->isEndPoint()) {
                Point currentEndPoint = endPoint->getCurrentPoint();

                // Only add a new event if the current end point is the second to last on the shortest path
                if (currentEndPoint != funnelTail.at(funnelTail.size() - 2)->getPoint()) {
                    return;
                }

                region = new SPV::EventOnShortestPath(
                    currentEndPoint,
                    apex->getCurrentPoint()
                );
                region->calculateIntersection(
                    seg1,
                    seg2,
                    !startFromEnd
                );
                region->setSecondPointIntersection(apex->getCurrentPoint());
                int spSize = funnelTail.size();
                if (spSize > 1) {
                    funnelTail.at(spSize - 2)->getFaceHandle()->info().addShortestPathEvent(region);
                    intersection = region->getFirstPointIntersection();
                    handleIntersection(
                        eventMap.getStartTriangle(),
                        eventMap.getStartTriangle()->getRightTriangle(),
                        region,
                        true,
                        startFromEnd,
                        !startFromEnd,
                        1
                    );
                    eventIntersection = new EventIntersection(
                         1,
                         apex->getCurrentPoint(),
                         intersection,
                         seg1,
                         seg2
                    );
                    currentFace->info().addEventIntersection(eventIntersection);
                    pathEvents.push_back(eventIntersection);
                    eventsOnShortestPath.push_back(region);
                } else {
                    delete region;
                }
                return;
            }
            bool foundRegion = false;
            Face_circulator faceCirculator = endPoint->getCurrentEntry()->getVertexHandle()->incident_faces(),
                    done(faceCirculator);
            if (faceCirculator != 0) {
                do {
                  if (faceCirculator->info().getHasShortestPathEvent(endPoint->getCurrentPoint(), apex->getCurrentPoint()) == true) {
                    region = faceCirculator->info().getShortestPathEvent(endPoint->getCurrentPoint(), apex->getCurrentPoint());
                    foundRegion = true;
                  }
                } while (++faceCirculator != done && foundRegion == false);
              }
            if (foundRegion == false) {
                if (apex->getCurrentEntry()->isMidPoint()) {
                    Face_circulator faceCirculator = apex->getCurrentEntry()->getVertexHandle()->incident_faces(),
                            done(faceCirculator);
                    if (faceCirculator != 0) {
                        do {
                            if (faceCirculator->info().getHasShortestPathEvent(endPoint->getCurrentPoint(), apex->getCurrentPoint()) == true) {
                                region = faceCirculator->info().getShortestPathEvent(endPoint->getCurrentPoint(), apex->getCurrentPoint());
                                foundRegion = true;
                            }
                        } while (++faceCirculator != done && foundRegion == false);
                    }
                }
                if (foundRegion == false) {
                    return;
                }
            }
        } else {
            region = new SPV::EventOnShortestPath(
                apex->getCurrentPoint(),
                endPoint->getCurrentPoint()
            );
            if (apex->getCurrentEntry()->isStartPoint() && !startFromEnd) {
                setStartPointIntersection = true;
            }
            endPoint->getCurrentEntry()->getFaceHandle()->info().addShortestPathEvent(region);
            eventsOnShortestPath.push_back(region);
        }
        region->calculateIntersection(
            seg1,
            seg2,
            !startFromEnd
        );
        if (setStartPointIntersection == true) {
            handleIntersection(
                eventMap.getStartTriangle(),
                eventMap.getStartTriangle()->getRightTriangle(),
                region,
                true,
                startFromEnd,
                !startFromEnd,
                1
            );
        }
        if (startFromEnd) {
            intersection = region->getFirstPointIntersection();
        } else {
            intersection = region->getSecondPointIntersection();
        }
        eventIntersection = new EventIntersection(
             1,
             apex->getCurrentPoint(),
             intersection,
             seg1,
             seg2
        );
        currentFace->info().addEventIntersection(eventIntersection);
        pathEvents.push_back(eventIntersection);
    }
}

void SPV::ShortestPath::splitFunnel(
    CDT::Face_handle currentFace,
    int neighborIndex,
    SPV::PointOnShortestPath* apex,
    std::vector<SPV::PointOnShortestPath*> &leftFunnel,
    std::vector<SPV::PointOnShortestPath*> &rightFunnel,
    bool startFromEnd
) {
    CDT::Face_handle nextFace = currentFace->neighbor(neighborIndex);
    SPV::PointOnShortestPath* nextPointOnTree;
    std::vector<SPV::PointOnShortestPath*> leftFunnel1;
    std::vector<SPV::PointOnShortestPath*> leftFunnel2;
    std::vector<SPV::PointOnShortestPath*> rightFunnel1;
    std::vector<SPV::PointOnShortestPath*> rightFunnel2;
    std::vector<SPV::PointOnShortestPath*> *currentShortestPathTree;

    if (startFromEnd) {
        currentShortestPathTree = &shortestPathTreeFromEnd;
    } else {
        currentShortestPathTree = &shortestPathTree;

    }


    // End of recursion: nextFace is outside of the constrained triangulation
    if (!nextFace->info().inDomain()) {
        setShortestPathMapInfo(
            currentFace,
            neighborIndex,
            apex,
            leftFunnel,
            startFromEnd
        );
        setShortestPathMapInfo(
            currentFace,
            neighborIndex,
            apex,
            rightFunnel,
            startFromEnd
        );
        return;
    }

    Point nextPoint;
    int nextNeighborIndex, leftPointIndex, rightPointIndex;
    int leftFunnelSize = leftFunnel.size();
    int rightFunnelSize = rightFunnel.size();
    int pointIndex = 0;

    // We now know that nextFace is part of the triangulation. Find the point not on the current funnel.
    for (int i = 0; i < 3; i++) {
        Point p = nextFace->vertex(i)->point();

        if (p == leftFunnel.at(leftFunnelSize - 1)->getCurrentPoint()) {
            leftPointIndex = i;
        } else if (p == rightFunnel.at(rightFunnelSize - 1)->getCurrentPoint()) {
            rightPointIndex = i;
        } else {
            pointIndex = i;
            nextPoint = p;
        }
    }

    SPV::ShortestPath::predecessorInfo* info = findPredecessor(
        nextPoint,
        apex,
        leftFunnel,
        rightFunnel
    );

    // Special case if the predecessor is the last point on the funnel
    if (info->isLastPointOnFunnel) {
        SPV::PointOnShortestPath* apexOfSecondFunnel;

        if (info->onLeftFunnel) {
            apexOfSecondFunnel = leftFunnel.at(info->indexOnFunnel);
            nextPointOnTree = new SPV::PointOnShortestPath(
                new ShortestPathEntry(nextFace, pointIndex),
                apexOfSecondFunnel
            );
            currentShortestPathTree->push_back(nextPointOnTree);
            if (startFromEnd) {
                nextFace->info().addSptFromEndIndex(currentShortestPathTree->size() - 1);
            } else {
                nextFace->info().addSptFromStartIndex(currentShortestPathTree->size() - 1);
            }
            leftFunnel.push_back(nextPointOnTree);
            splitFunnel(
                nextFace,
                leftPointIndex,
                apex,
                leftFunnel,
                rightFunnel,
                startFromEnd
            );

            nextFace = nextFace->neighbor(rightPointIndex);

            // Check all the faces to the right of the current diagonal
            while (nextFace->info().inDomain()) {
                std::vector<SPV::PointOnShortestPath*> newLeftFunnel;
                std::vector<SPV::PointOnShortestPath*> newRightFunnel;

                newRightFunnel.push_back(nextPointOnTree);

                for (int i = 0; i < 3; i++) {
                    Point p = nextFace->vertex(i)->point();
                    if (p == apexOfSecondFunnel->getCurrentPoint()) {
                        nextNeighborIndex = i;
                    } else if (p == nextPointOnTree->getCurrentPoint()) {
                        rightPointIndex = i;
                    } else {
                        pointIndex = i;
                    }
                }

                nextPointOnTree = new SPV::PointOnShortestPath(
                    new ShortestPathEntry(nextFace, pointIndex),
                    apexOfSecondFunnel
                );
                currentShortestPathTree->push_back(nextPointOnTree);
                if (startFromEnd) {
                    nextFace->info().addSptFromEndIndex(currentShortestPathTree->size() - 1);
                } else {
                    nextFace->info().addSptFromStartIndex(currentShortestPathTree->size() - 1);
                }
                newLeftFunnel.push_back(nextPointOnTree);
                splitFunnel(
                    nextFace,
                    nextNeighborIndex,
                    apexOfSecondFunnel,
                    newLeftFunnel,
                    newRightFunnel,
                    startFromEnd
                );
                nextFace = nextFace->neighbor(rightPointIndex);
            }
        } else {
            apexOfSecondFunnel = rightFunnel.at(info->indexOnFunnel);
            nextPointOnTree = new SPV::PointOnShortestPath(
                new ShortestPathEntry(nextFace, pointIndex),
                apexOfSecondFunnel
            );
            currentShortestPathTree->push_back(nextPointOnTree);
            if (startFromEnd) {
                nextFace->info().addSptFromEndIndex(currentShortestPathTree->size() - 1);
            } else {
                nextFace->info().addSptFromStartIndex(currentShortestPathTree->size() - 1);
            }

            rightFunnel.push_back(nextPointOnTree);
            splitFunnel(
                nextFace,
                rightPointIndex,
                apex,
                leftFunnel,
                rightFunnel,
                startFromEnd
            );

            nextFace = nextFace->neighbor(leftPointIndex);

            // Check all the faces to the left of the current diagonal
            while (nextFace->info().inDomain()) {
                std::vector<SPV::PointOnShortestPath*> newLeftFunnel;
                std::vector<SPV::PointOnShortestPath*> newRightFunnel;

                newLeftFunnel.push_back(nextPointOnTree);

                for (int i = 0; i < 3; i++) {
                    Point p = nextFace->vertex(i)->point();
                    if (p == apexOfSecondFunnel->getCurrentPoint()) {
                        nextNeighborIndex = i;
                    } else if (p == nextPointOnTree->getCurrentPoint()) {
                        leftPointIndex = i;
                    } else {
                        pointIndex = i;
                    }
                }
                nextPointOnTree = new SPV::PointOnShortestPath(
                    new ShortestPathEntry(nextFace, pointIndex),
                    apexOfSecondFunnel
                );
                currentShortestPathTree->push_back(nextPointOnTree);
                if (startFromEnd) {
                    nextFace->info().addSptFromEndIndex(currentShortestPathTree->size() - 1);
                } else {
                    nextFace->info().addSptFromStartIndex(currentShortestPathTree->size() - 1);
                }
                newRightFunnel.push_back(nextPointOnTree);
                splitFunnel(
                    nextFace,
                    nextNeighborIndex,
                    apexOfSecondFunnel,
                    newLeftFunnel,
                    newRightFunnel,
                    startFromEnd
                );
                nextFace = nextFace->neighbor(leftPointIndex);
            }
        }
        delete info;
        return;
    }

    // Split the funnel at the apex
    if (info->isApex) {
        nextPointOnTree = nextPointOnTree = new SPV::PointOnShortestPath(
            new ShortestPathEntry(nextFace, pointIndex),
            apex
        );
        currentShortestPathTree->push_back(nextPointOnTree);
        if (startFromEnd) {
            nextFace->info().addSptFromEndIndex(currentShortestPathTree->size() - 1);
        } else {
            nextFace->info().addSptFromStartIndex(currentShortestPathTree->size() - 1);
        }
        rightFunnel1.push_back(nextPointOnTree);
        leftFunnel1.push_back(nextPointOnTree);
        splitFunnel(
            nextFace,
            rightPointIndex,
            apex,
            leftFunnel,
            rightFunnel1,
            startFromEnd
        );
        splitFunnel(
            nextFace,
            leftPointIndex,
            apex,
            leftFunnel1,
            rightFunnel,
            startFromEnd
        );
        delete info;
        return;
    }

    // Split at a point on the leftFunnel
    if (info->onLeftFunnel) {
        nextPointOnTree = new SPV::PointOnShortestPath(
            new ShortestPathEntry(nextFace, pointIndex),
            leftFunnel.at(info->indexOnFunnel)
        );
        rightFunnel1.push_back(nextPointOnTree);
        for (int i = info->indexOnFunnel + 1; i < leftFunnelSize; i++) {
            leftFunnel1.push_back(leftFunnel.at(i));
        }
        for (int i = 0; i <= info->indexOnFunnel; i++) {
            leftFunnel2.push_back(leftFunnel.at(i));
        }
        leftFunnel2.push_back(nextPointOnTree);

        splitFunnel(
            nextFace,
            rightPointIndex,
            leftFunnel.at(info->indexOnFunnel),
            leftFunnel1,
            rightFunnel1,
            startFromEnd
        );
        splitFunnel(
            nextFace,
            leftPointIndex,
            apex,
            leftFunnel2,
            rightFunnel,
            startFromEnd
        );
    } else {
        nextPointOnTree = new SPV::PointOnShortestPath(
            new ShortestPathEntry(nextFace, pointIndex),
            rightFunnel.at(info->indexOnFunnel)
        );
        leftFunnel1.push_back(nextPointOnTree);
        for (int i = info->indexOnFunnel + 1; i < rightFunnelSize; i++) {
            rightFunnel1.push_back(rightFunnel.at(i));
        }
        for (int i = 0; i <= info->indexOnFunnel; i++) {
            rightFunnel2.push_back(rightFunnel.at(i));
        }
        rightFunnel2.push_back(nextPointOnTree);

        splitFunnel(
            nextFace,
            leftPointIndex,
            rightFunnel.at(info->indexOnFunnel),
            leftFunnel1,
            rightFunnel1,
            startFromEnd
        );
        splitFunnel(
            nextFace,
            rightPointIndex,
            apex,
            leftFunnel,
            rightFunnel2,
            startFromEnd
        );
    }
    delete info;
    currentShortestPathTree->push_back(nextPointOnTree);
    if (startFromEnd) {
        nextFace->info().addSptFromEndIndex(currentShortestPathTree->size() - 1);
    } else {
        nextFace->info().addSptFromStartIndex(currentShortestPathTree->size() - 1);
    }
}

SPV::ShortestPath::predecessorInfo* SPV::ShortestPath::findPredecessor(
        Point p,
        SPV::PointOnShortestPath* apex,
        std::vector<SPV::PointOnShortestPath*> &leftFunnel,
        std::vector<SPV::PointOnShortestPath*> &rightFunnel
) {
    int leftFunnelSize = leftFunnel.size();
    Point first, second;
    SPV::ShortestPath::predecessorInfo* result = new SPV::ShortestPath::predecessorInfo();

    if (leftFunnel.size() > 1) {
        for (int i = leftFunnel.size() - 1; i > 0; i--) {
           first = leftFunnel.at(i - 1)->getCurrentPoint();
            second = leftFunnel.at(i)->getCurrentPoint();
            if (isOnLeftSide(first, second, p)) {
                result->onLeftFunnel = true;
                result->indexOnFunnel = i;
                if (i == leftFunnel.size() - 1) {
                    result->isLastPointOnFunnel = true;
                }
                return result;
            }
        }
    }

    first = apex->getCurrentPoint();
    second = leftFunnel.at(0)->getCurrentPoint();
    if (isOnLeftSide(first, second, p)) {
        result->onLeftFunnel = true;
        result->indexOnFunnel = 0;
        if (leftFunnel.size() == 1) {
            result->isLastPointOnFunnel = true;
        }
        return result;
    }

    second = rightFunnel.at(0)->getCurrentPoint();
    if (isOnLeftSide(first, second, p)) {
        result->isApex = true;
        return result;
    }

    // The predecessor must be on the right funnel
    result->onRightFunnel = true;

    if (rightFunnel.size() > 1) {
        for (int i = 0; i < rightFunnel.size() - 1; i++) {
            first = rightFunnel.at(i) ->getCurrentPoint();
            second = rightFunnel.at(i + 1)->getCurrentPoint();
            if (isOnLeftSide(first, second, p)) {
                result->indexOnFunnel = i;
                return result;
            }
        }
    }

    // return the last point on the right Funnel
    result->indexOnFunnel = rightFunnel.size() - 1;
    result->isLastPointOnFunnel = true;
    return result;
}

std::vector<SPV::PointOnShortestPath *> SPV::ShortestPath::getShorttestPathTree() {
    return shortestPathTreeFromEnd;
}

bool SPV::ShortestPath::shouldAddPathEventForEntries(ShortestPathEntry* endPoint, ShortestPathEntry* startPoint, bool startFromEnd) {
    CDT::Face_handle currentFace = endPoint->getFaceHandle();
    bool foundShortestPathIndex = false;
    std::vector<unsigned> indices;
    unsigned index;

    std::cout << endPoint->getPoint() << std::endl;

    if (currentFace->info().getHasShortestPathIndices() == true) {
        indices = currentFace->info().getShortestPathIndices();
        for (int i = 0; i < indices.size(); i++) {
            if (funnelTail.at(indices.at(i))->getPoint() == endPoint->getPoint()) {
                foundShortestPathIndex = true;
                index = indices.at(i);
                break;
            }
        }
    }

    // If no index has been found, check the adjacent faces just to be sure
    if (foundShortestPathIndex == false) {
        Face_circulator faceCirculator = endPoint->getVertexHandle()->incident_faces(),
            done(faceCirculator);
        if (faceCirculator != 0) {
            do {
                if (faceCirculator->info().inDomain() && faceCirculator->info().getHasShortestPathIndices() == true) {
                    indices = faceCirculator->info().getShortestPathIndices();
                    for (int i = 0; i < indices.size(); i++) {
                        if (funnelTail.at(indices.at(i))->getPoint() == endPoint->getPoint()) {
                            foundShortestPathIndex = true;
                            index = indices.at(i);
                            break;
                        }
                    }
                }
            } while (++faceCirculator != done && foundShortestPathIndex == false);
        }
    }

    if (foundShortestPathIndex) {
        if (startFromEnd) {
            return startPoint->getPoint() == funnelTail.at(index + 1)->getPoint();
        }
        return startPoint->getPoint() == funnelTail.at(index - 1)->getPoint();
    }
    return false;
}
