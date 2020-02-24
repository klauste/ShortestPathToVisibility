#include "Events/bendeventcalculator.h"
SPV::BendEventCalculator::BendEventCalculator (Polygon p, Point s, Point e) :
    PathAndBoundaryEventCalculator (p, s, e) {}

void SPV::BendEventCalculator::calculateBendEvents()
{
    if (directPathExists) {
        return;
    }

    calculatePathAndBoundaryEvents();
    currentEventSegment = firstEventSegment;
    calculateEventsOnStartSide = true;
    bool allEventsHandled = false;

    while (!allEventsHandled) {
        calculateEventsForCurrentEventSegment();
        setDistanceToLastVertex();
        if (currentEventSegment->hasSuccessor()) {
            currentEventSegment = currentEventSegment->getSuccessor();
        } else {
            allEventsHandled = true;
        }
    }

    // The last event segment is reached, now calculate the bend events on the end side
    calculateEventsOnStartSide = false;
    allEventsHandled = false;

    while (!allEventsHandled) {
        calculateEventsForCurrentEventSegment();
        setDistanceToLastVertex();
        if (currentEventSegment->hasPredecessor()) {
            currentEventSegment = currentEventSegment->getPredecessor();
        } else {
            allEventsHandled = true;
            firstEventSegment = currentEventSegment;
        }
    }
}

void SPV::BendEventCalculator::setDistanceToLastVertex()
{
    EventSegment *previousSegment;
    unsigned indexOfLastSPPoint, previousIndexOfSPPoint;
    std::vector<Point> extraPoints, previousExtraPoints;
    double totalDistance;
    if (calculateEventsOnStartSide) {
        if (!currentEventSegment->hasPredecessor()) {
            currentEventSegment->setDistanceToLastVertex(0.0, true);
            return;
        }
        previousSegment = currentEventSegment->getPredecessor();
        indexOfLastSPPoint = currentEventSegment->getIndexOfLastSPPointOnStartSide();
        previousIndexOfSPPoint = previousSegment->getIndexOfLastSPPointOnStartSide();
        extraPoints = currentEventSegment->getExtraPointsOnStartSide();
        previousExtraPoints = previousSegment->getExtraPointsOnStartSide();
        totalDistance = shortestPath.at(indexOfLastSPPoint)->getDistanceFromStartPoint();
    } else {
        if (!currentEventSegment->hasSuccessor()) {
            currentEventSegment->setDistanceToLastVertex(0.0, false);
            return;
        }
        previousSegment = currentEventSegment->getSuccessor();
        indexOfLastSPPoint = currentEventSegment->getIndexOfLastSPPointOnEndSide();
        previousIndexOfSPPoint = previousSegment->getIndexOfLastSPPointOnEndSide();
        extraPoints = currentEventSegment->getExtraPointsOnEndSide();
        previousExtraPoints = previousSegment->getExtraPointsOnEndSide();
        totalDistance = shortestPath.at(indexOfLastSPPoint)->getDistanceFromEndPoint();
    }
    if (indexOfLastSPPoint == previousIndexOfSPPoint && extraPoints.size() == previousExtraPoints.size()) {
        currentEventSegment->setDistanceToLastVertex(
            previousSegment->getDistanceToLastVertex(calculateEventsOnStartSide),
            calculateEventsOnStartSide
        );
        return;
    }

    Point lastSpPoint = shortestPath.at(indexOfLastSPPoint)->getPoint();
    for (unsigned i = 0; i < extraPoints.size(); i++) {
        if (i == 0) {
            totalDistance = totalDistance + sqrt(CGAL::squared_distance(lastSpPoint, extraPoints.at(i)));
        } else {
            totalDistance = totalDistance + sqrt(CGAL::squared_distance(extraPoints.at(i - 1), extraPoints.at(i)));
        }
    }
    currentEventSegment->setDistanceToLastVertex(
        totalDistance,
        calculateEventsOnStartSide
    );
}

void SPV::BendEventCalculator::calculateEventsForCurrentEventSegment ()
{
    setCurrentSegmentOrderFromLeftToRight();
    handlePathOrBoundaryEvent();
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    Point lastPointToLoS = getLastPointBeforeLoS(currentEventSegment, calculateEventsOnStartSide);

    // If the last point to the line of sight is on the pivot point,
    // there is nothing to do
    if (pivotPoint == lastPointToLoS) {
        return;
    }

    if (
        currentEventSegment->isPathOnPolygonEdgeAtBeginning(calculateEventsOnStartSide) &&
        !currentEventSegment->isLoSVisible(calculateEventsOnStartSide)
    ) {
        boost::variant<bool, Point> result = getNextDegenerateBendEvent();
        // If the path runs on the polygon edge until the segment end point, there
        // is nothing to do
        if (result.type() == typeid(bool)) {
            return;
        }
        // Add a degenerate bend event and return
        Point eventPoint = boost::get<Point>(result);
        handleDegenerateBendEvent(eventPoint);
        return;
    }
    if (handleBendEventWithPointLoss(false)) {
        return;
    }
    if (handleBendEventWithPointAddition(false)) {
        return;
    }
    boost::variant<bool, Point> result = getNextDegenerateBendEvent();
    if (result.type() == typeid(bool)) {
        return;
    }
    // Add a degenerate bend event
    Point eventPoint = boost::get<Point>(result);
    handleDegenerateBendEvent(eventPoint);
}

bool SPV::BendEventCalculator::handleBendEventWithPointLoss(bool checkSegmentStartOnly)
{
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    std::vector<Point> extraPoints;
    Point segmentStart;
    Point segmentEnd;
    bool loSVisible;
    Point lastPointOnShortestPath;

    if (calculateEventsOnStartSide) {
        extraPoints = currentEventSegment->getExtraPointsOnStartSide();
        segmentStart = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
        segmentEnd = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide();
        loSVisible = currentEventSegment->getStartSideLoSVisible();
        lastPointOnShortestPath = shortestPath.at(currentEventSegment->getIndexOfLastSPPointOnStartSide())->getPoint();
    } else {
        extraPoints = currentEventSegment->getExtraPointsOnEndSide();
        segmentStart = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
        segmentEnd = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide();
        loSVisible = currentEventSegment->getEndSideLoSVisible();
        lastPointOnShortestPath = shortestPath.at(currentEventSegment->getIndexOfLastSPPointOnEndSide())->getPoint();
    }
    unsigned extraPointsSize = extraPoints.size();
    if (extraPointsSize == 0) {
        return false;
    }
    Point firstLinePoint = extraPoints.back();
    Point secondLinePoint;
    if (extraPointsSize > 1) {
        secondLinePoint = extraPoints.at(extraPointsSize - 2);
    } else {
        secondLinePoint = lastPointOnShortestPath;
    }
    Point segmentEndWithDegenerateEvent = segmentEnd;
    boost::variant<bool, Point> result = getNextDegenerateBendEvent();
    bool eventPointFound = false;
    Point eventPoint;

    if (result.type() != typeid(bool)) {
        segmentEndWithDegenerateEvent = boost::get<Point>(result);
    }
    Line lineToCheck = Line(firstLinePoint, secondLinePoint);

    // If the line of sight is visible, get the intersection of the current segment
    // with the perpendicular line
    if (loSVisible) {
        Line perpendicularLine = lineToCheck.perpendicular(pivotPoint);
        result = gU.getIntersectionBetweenLineAndSegment(perpendicularLine, segmentStart, segmentEndWithDegenerateEvent);
        if (result.type() == typeid(Point)) {
            eventPoint = boost::get<Point>(result);
            // Don't do anything if the segment end and the event point is equal. This will be
            // handled in the next segment when the start points are equal
            if (!gU.pointsAreEqual(eventPoint, segmentEnd)) {
                if (gU.pointsAreEqual(eventPoint, segmentStart)) {
                    eventPointFound = checkSegmentStartOnly;
                } else {
                    eventPointFound = !checkSegmentStartOnly;
                }
            }
        }
    } else {
        result = gU.getIntersectionBetweenLineAndSegment(lineToCheck, segmentStart, segmentEndWithDegenerateEvent);
        if (result.type() == typeid(Point)) {
            eventPoint = boost::get<Point>(result);
            // Don't do anything if the segment end and the event point is equal. This will be
            // handled in the next segment when the start points are equal
            if (!gU.pointsAreEqual(eventPoint, segmentEnd)) {
                if (gU.pointsAreEqual(eventPoint, segmentStart)) {
                    eventPointFound = checkSegmentStartOnly;
                } else {
                    eventPointFound = !checkSegmentStartOnly;
                }
            }
        }
    }

    if (eventPointFound) {
        // If the event point is the same as the segment start, remove the
        // point on the current segment
        if (checkSegmentStartOnly) {
            if (calculateEventsOnStartSide) {
                currentEventSegment->removeExtraPointOnStartSide();
            } else {
                currentEventSegment->removeExtraPointOnEndSide();
            }
        } else {
            // Otherwise add a new segment
            addNewEventSegment(eventPoint);
            EventSegment *newSegment;
            if (calculateEventsOnStartSide) {
                newSegment = currentEventSegment->getSuccessor();
                newSegment->removeExtraPointOnStartSide();
            } else {
                newSegment = currentEventSegment->getPredecessor();
                newSegment->removeExtraPointOnEndSide();
            }
        }
    }

    return eventPointFound;
}

bool SPV::BendEventCalculator::handleBendEventWithPointAddition(bool checkSegmentStartOnly)
{
    Point currentSPPoint;
    Point nextSPPoint;
    Point segmentStart;
    Point segmentEnd;
    bool loSVisible;
    unsigned currentSPIndex;
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();

    if (calculateEventsOnStartSide) {
        currentSPIndex = currentEventSegment->getIndexOfLastSPPointOnStartSide();
        if (currentSPIndex == shortestPath.size() - 1 || currentEventSegment->getExtraPointsOnStartSide().size() > 0) {
            return false;
        }
        currentSPPoint = shortestPath.at(currentSPIndex)->getPoint();
        nextSPPoint = shortestPath.at(currentSPIndex + 1)->getPoint();
        segmentStart = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
        segmentEnd = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide();
        loSVisible = currentEventSegment->getStartSideLoSVisible();
    } else {
        currentSPIndex = currentEventSegment->getIndexOfLastSPPointOnEndSide();
        if (currentSPIndex == 0 || currentEventSegment->getExtraPointsOnEndSide().size() > 0) {
            return false;
        }
        currentSPPoint = shortestPath.at(currentSPIndex)->getPoint();
        nextSPPoint = shortestPath.at(currentSPIndex - 1)->getPoint();
        segmentStart = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
        segmentEnd = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide();
        loSVisible = currentEventSegment->getEndSideLoSVisible();
    }

    Point segmentEndWithDegenerateEvent = segmentEnd;
    boost::variant<bool, Point> result = getNextDegenerateBendEvent();
    bool eventPointFound = false;
    Point eventPoint;

    if (result.type() != typeid(bool)) {
        segmentEndWithDegenerateEvent = boost::get<Point>(result);
    }
    Line lineToCheck = Line(currentSPPoint, nextSPPoint);

    // If the line of sight is visible, get the intersection of the current segment
    // with the line which is perpendicular at the pivot point
    if (loSVisible) {
        Line perpendicularLine = lineToCheck.perpendicular(pivotPoint);
        if (checkSegmentStartOnly) {
            result = gU.getIntersectionBetweenLineAndLine(perpendicularLine, segmentStart, segmentEndWithDegenerateEvent);
        } else {
            result = gU.getIntersectionBetweenLineAndSegment(perpendicularLine, segmentStart, segmentEndWithDegenerateEvent);
        }
        if (result.type() == typeid(Point)) {
            eventPoint = boost::get<Point>(result);

            // Don't do anything if the segment end and the event point is equal. This will be
            // handled in the next segment when the start points are equal
            if (!gU.pointsAreEqual(eventPoint, segmentEnd)) {
                if (gU.pointsAreEqual(eventPoint, segmentStart)) {
                    eventPointFound = checkSegmentStartOnly;
                } else {
                    eventPointFound = !checkSegmentStartOnly;
                }
            }
        }
    } else {
        if (checkSegmentStartOnly) {
            result = gU.getIntersectionBetweenLineAndLine(lineToCheck, segmentStart, segmentEndWithDegenerateEvent);
        } else {
            result = gU.getIntersectionBetweenLineAndSegment(lineToCheck, segmentStart, segmentEndWithDegenerateEvent);
        }
        if (result.type() == typeid(Point)) {
            eventPoint = boost::get<Point>(result);

            // Don't do anything if the segment end and the event point is equal. This will be
            // handled in the next segment when the start points are equal
            if (!gU.pointsAreEqual(eventPoint, segmentEnd)) {
                eventPointFound = true;
                if (gU.pointsAreEqual(eventPoint, segmentStart)) {
                    eventPointFound = checkSegmentStartOnly;
                } else {
                    eventPointFound = !checkSegmentStartOnly;
                }
            }
        }
    }

    if (eventPointFound) {
        // If the event point is the same as the segment start and a path or boundary event is handled,
        // set the new index on the current event segment
        if (checkSegmentStartOnly) {
            if (calculateEventsOnStartSide) {
                currentEventSegment->setIndexOfLastSPPointOnStartSide(currentSPIndex + 1);
            } else {
                currentEventSegment->setIndexOfLastSPPointOnEndSide(currentSPIndex - 1);
            }
        } else {
            // Otherwise add a new segment and set the index there
            addNewEventSegment(eventPoint);
            EventSegment *newSegment;
            if (calculateEventsOnStartSide) {
                newSegment = currentEventSegment->getSuccessor();
                newSegment->setIndexOfLastSPPointOnStartSide(currentSPIndex + 1);
            } else {
                newSegment = currentEventSegment->getPredecessor();
                newSegment->setIndexOfLastSPPointOnEndSide(currentSPIndex - 1);
            }
        }
    }

    return eventPointFound;
}

void SPV::BendEventCalculator::addNewEventSegment(Point eventPoint)
{
    std::shared_ptr<LineOfSight> splitLine;
    EventSegment *newEventSegment;
    Line lOS = Line(eventPoint, currentEventSegment->getPivotPoint()->getPoint());

    // Get the segment on the opposite side
    Point segmentStartPoint;
    Point segmentEndPoint;
    if (calculateEventsOnStartSide) {
        segmentStartPoint = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide();
        segmentEndPoint = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
    } else {
        segmentStartPoint = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
        segmentEndPoint = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide();
    }
    boost::variant<bool, Point> result = gU.getIntersectionBetweenLineAndLine(lOS, segmentStartPoint, segmentEndPoint);
    if (result.type() == typeid(bool)) {
        // TODO: handle this as an exception
    }
    Point secondEventPoint = boost::get<Point>(result);
    if (calculateEventsOnStartSide) {
        splitLine = std::make_shared<LineOfSight>(eventPoint, false, secondEventPoint, false);
        splitLine->setEventType(BEND);
        newEventSegment = currentEventSegment->createNewSuccessor(splitLine);
        newEventSegment->setEventsOnStartSideHandled();
    } else {
        splitLine = std::make_shared<LineOfSight>(secondEventPoint, false, eventPoint, false);
        splitLine->setEventType(BEND);
        newEventSegment = currentEventSegment->createNewPredecessor(splitLine);
        newEventSegment->setEventsOnEndSideHandled();
    }
}

void SPV::BendEventCalculator::handleDegenerateBendEvent(Point eventPoint)
{
    bool newVisibilityFlag;
    if (calculateEventsOnStartSide) {
        newVisibilityFlag = !currentEventSegment->getStartSideLoSVisible();
    } else {
        newVisibilityFlag = !currentEventSegment->getEndSideLoSVisible();
    }
    addNewEventSegment(eventPoint);
    EventSegment *newSegment;
    if (calculateEventsOnStartSide) {
        newSegment = currentEventSegment->getSuccessor();
        newSegment->setStartSideLoSVisible(newVisibilityFlag);
        newSegment->setStartSideOnPolygonEdge(false);
    } else {
        newSegment = currentEventSegment->getPredecessor();
        newSegment->setEndSideLoSVisible(newVisibilityFlag);
        newSegment->setEndSideOnPolygonEdge(false);
    }
}

void SPV::BendEventCalculator::handleDegenerateBendEventForSegmentStart()
{
    // If this is a degenerate bend event added on the start side, there is nothing to do
    if (calculateEventsOnStartSide && currentEventSegment->bendEventsOnStartSideAreHandled()) {
        return;
    }
    // If this is a degenerate bend event added on the end side, there is nothing to do
    if (!calculateEventsOnStartSide && currentEventSegment->bendEventsOnEndSideAreHandled()) {
        return;
    }
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    Point segmentStartPoint = currentEventSegment->getSegmentStartPoint(calculateEventsOnStartSide);
    Point segmentEndPoint = currentEventSegment->getSegmentEndPoint(calculateEventsOnStartSide);
    Point lastVertexToLs = getLastPointBeforeLoS(currentEventSegment, calculateEventsOnStartSide);
    Point centerPoint = Point((lastVertexToLs.x() + pivotPoint.x()) / 2, (lastVertexToLs.y() + pivotPoint.y()) / 2);
    boost::variant<std::vector<Point>, bool> intersectionResult =
        gU.getCircleLineIntersection(centerPoint, lastVertexToLs, segmentStartPoint, segmentEndPoint);

    // No intersection found, return false
    if (intersectionResult.type() == typeid(bool)) {
        return;
    }

    std::vector<Point> circleIntersections = boost::get<std::vector<Point>>(intersectionResult);
    bool foundIntersectionPoint = false;

    for (unsigned i = 0; i < circleIntersections.size(); i++) {
        // If the intersections are equal, don't handle them
        if (gU.pointsAreEqual(segmentStartPoint, circleIntersections.at(i))) {
            foundIntersectionPoint = true;
            break;
        }
    }

    if (foundIntersectionPoint) {
        if (calculateEventsOnStartSide) {
            currentEventSegment->setStartSideLoSVisible(!currentEventSegment->getStartSideLoSVisible());
        } else {
            currentEventSegment->setEndSideLoSVisible(!currentEventSegment->getEndSideLoSVisible());
        }
    }
}

/**
 * @brief getNextDegenerateBendEvent
 * This function checks if there is a degenerate bend event on the current edge defined by the
 * two intersection events. If there isn't, false is returned. If there are degenerate events, the
 * degenerate event closer to ei1 is returned.
 * @param onStartSide
 * @return
 */
boost::variant<Point, bool> SPV::BendEventCalculator::getNextDegenerateBendEvent()
{
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    Point segmentStartPoint = currentEventSegment->getSegmentStartPoint(calculateEventsOnStartSide);
    Point segmentEndPoint = currentEventSegment->getSegmentEndPoint(calculateEventsOnStartSide);
    Point lastVertexToLs = getLastPointBeforeLoS(currentEventSegment, calculateEventsOnStartSide);
    Point centerPoint = Point((lastVertexToLs.x() + pivotPoint.x()) / 2, (lastVertexToLs.y() + pivotPoint.y()) / 2);
    boost::variant<std::vector<Point>, bool> intersectionResult =
        gU.getCircleSegmentIntersection(centerPoint, lastVertexToLs, segmentStartPoint, segmentEndPoint);

    // No intersection found, return false
    if (intersectionResult.type() == typeid(bool)) {
        return false;
    }

    std::vector<Point> circleIntersections = boost::get<std::vector<Point>>(intersectionResult);
    Point intersectionPoint;
    bool foundIntersectionPoint = false;
    K::FT distanceFromEdgeStartToIntersection = 0;

    for (unsigned i = 0; i < circleIntersections.size(); i++) {
        // If the intersections are equal, don't handle them
        if (gU.pointsAreEqual(segmentStartPoint, circleIntersections.at(i)) || gU.pointsAreEqual(segmentEndPoint, circleIntersections.at(i))) {
            continue;
        }
        if (!foundIntersectionPoint) {
            intersectionPoint = circleIntersections.at(i);
            foundIntersectionPoint = true;
            distanceFromEdgeStartToIntersection = CGAL::squared_distance(intersectionPoint, segmentStartPoint);
        } else {
            Point currentPoint = circleIntersections.at(i);
            // If a point has already been found, only set to the new point, if the distance is smaller
            if (distanceFromEdgeStartToIntersection > CGAL::squared_distance(currentPoint, segmentStartPoint)) {
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

void SPV::BendEventCalculator::handlePathOrBoundaryEvent()
{
    EventSegment *previousEventSegment;
    bool firstPointIsPolygonVertex = false;

    if (calculateEventsOnStartSide) {
        if (currentEventSegment->hasPredecessor()) {
            previousEventSegment = currentEventSegment->getPredecessor();
            firstPointIsPolygonVertex = currentEventSegment->getFirstLineOfSightFromStart()->isStartPointVertex();
        } else {
            currentEventSegment->setStartSideLoSVisible(true);
            currentEventSegment->setStartSideOnPolygonEdge(false);
            currentEventSegment->setIndexOfLastSPPointOnStartSide(0);
            return;
        }
    } else {
        if (currentEventSegment->hasSuccessor()) {
            previousEventSegment = currentEventSegment->getSuccessor();
            firstPointIsPolygonVertex = currentEventSegment->getSecondLineOfSightFromStart()->isEndPointVertex();
        } else {
            currentEventSegment->setEndSideLoSVisible(true);
            currentEventSegment->setEndSideOnPolygonEdge(false);
            currentEventSegment->setIndexOfLastSPPointOnEndSide(shortestPath.size() - 1);
            return;
        }
    }
    bool pivotPointHasChanged = currentEventSegment->getPivotPoint() != previousEventSegment->getPivotPoint();

    // A boundary event occurs if the pivot points are the same and the first point on the
    // segment is a is a polygon vertex
    if (!pivotPointHasChanged && firstPointIsPolygonVertex) {
        handleBoundaryEvent(previousEventSegment);
    } else if (pivotPointHasChanged) {
        handlePathEvent(previousEventSegment);
    } else {
        // If this is neither a boundary nor path event, just add the previous settings to
        // the current event segment if the event hasn't been handled yetf
        if (calculateEventsOnStartSide && !currentEventSegment->bendEventsOnStartSideAreHandled()) {
            addPreviousSettingsToCurrentES(previousEventSegment, false);
        }
        if (!calculateEventsOnStartSide && !currentEventSegment->bendEventsOnEndSideAreHandled()) {
            addPreviousSettingsToCurrentES(previousEventSegment, false);
        }
        // Check if the current segment start co-incides with a bend event where points are lost
        // and/or points are added
        handleBendEventWithPointLoss(true);
        handleBendEventWithPointAddition(true);
        handleDegenerateBendEventForSegmentStart();
    }
}

void SPV::BendEventCalculator::handleBoundaryEvent(EventSegment *previousEventSegment)
{
    std::shared_ptr<LineOfSight> firstLos;
    std::shared_ptr<LineOfSight> secondLos;
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    Point edgeStart;
    Point edgeEnd;
    Point previousLastPointOnPath = getLastPointBeforeLoS(previousEventSegment, calculateEventsOnStartSide);
    bool eventHandled = false;
    addPreviousSettingsToCurrentES(previousEventSegment, true);

    if (calculateEventsOnStartSide) {
        firstLos = currentEventSegment->getFirstLineOfSightFromStart();
        secondLos = currentEventSegment->getSecondLineOfSightFromStart();
        if (firstLos->isStartPointVertex()) {
            eventHandled = true;
            // If the end point on the previous segment was not a vertex, this vertex is
            // protruding into the polygon and we need to check the segment between
            // the previous end point and the protruding vertex
            if (!previousEventSegment->getSecondLineOfSightFromStart()->isStartPointVertex()) {
                handleSegmentToProtrudingVertex(previousEventSegment);
            } else {
                // Check if the current segment start co-incides with a bend event where points are lost
                // and/or points are added
                handleBendEventWithPointLoss(true);
                handleBendEventWithPointAddition(true);
            }
            edgeStart = firstLos->getPointOnStartSide();
            edgeEnd = secondLos->getPointOnStartSide();
            if (gU.isPerpendicularFootOnVertex(previousLastPointOnPath, edgeStart, pivotPoint)) {
                currentEventSegment->setStartSideLoSVisible(
                    gU.isEdgeWithStartPointOnCircleObstructingShortestPath(previousLastPointOnPath, edgeStart, edgeEnd, pivotPoint)
                );
            } else {
                bool pathIsObstructed = gU.isPerpendicularFootObstructedAtBoundaryVertex(previousLastPointOnPath, edgeStart, pivotPoint);
                if (pathIsObstructed) {
                    if (gU.isEdgeVisibleFromLastPoint(previousLastPointOnPath, edgeStart, edgeEnd, pivotPoint)) {
                        currentEventSegment->setStartSideLoSVisible(false);
                    } else {
                        currentEventSegment->addExtraPointsOnStartSide(edgeStart);
                        bool isEdgeObstructing = gU.isPerpendicularFootObstructedByEdge(edgeStart, edgeEnd, pivotPoint);
                        currentEventSegment->setStartSideLoSVisible(!isEdgeObstructing);
                        currentEventSegment->setStartSideOnPolygonEdge(isEdgeObstructing);
                    }
                }
            }
        }
    } else {
        firstLos = currentEventSegment->getSecondLineOfSightFromStart();
        secondLos = currentEventSegment->getFirstLineOfSightFromStart();
        if (firstLos->isEndPointVertex()) {
            eventHandled = true;
            // If the end point on the previous segment was not vertex, this vertex is
            // protruding into the polygon and we need to check the segment between
            // the previous end point and the protruding vertex
            if (!previousEventSegment->getFirstLineOfSightFromStart()->isEndPointVertex()) {
                handleSegmentToProtrudingVertex(previousEventSegment);
            } else {
                // Check if the current segment start co-incides with a bend event where points are lost
                // and/or points are added
                handleBendEventWithPointLoss(true);
                handleBendEventWithPointAddition(true);
            }
            edgeStart = firstLos->getPointOnEndSide();
            edgeEnd = secondLos->getPointOnEndSide();
            if (gU.isPerpendicularFootOnVertex(previousLastPointOnPath, edgeStart, pivotPoint)) {
                currentEventSegment->setEndSideLoSVisible(
                    gU.isEdgeWithStartPointOnCircleObstructingShortestPath(previousLastPointOnPath, edgeStart, edgeEnd, pivotPoint)
                );
            } else {
                bool pathIsObstructed = gU.isPerpendicularFootObstructedAtBoundaryVertex(previousLastPointOnPath, edgeStart, pivotPoint);
                if (pathIsObstructed) {
                    if (gU.isEdgeVisibleFromLastPoint(previousLastPointOnPath, edgeStart, edgeEnd, pivotPoint)) {
                        currentEventSegment->setEndSideLoSVisible(false);
                    } else {
                        currentEventSegment->addExtraPointsOnEndSide(edgeStart);
                        bool isEdgeObstructing = gU.isPerpendicularFootObstructedByEdge(edgeStart, edgeEnd, pivotPoint);
                        currentEventSegment->setEndSideLoSVisible(!isEdgeObstructing);
                        currentEventSegment->setEndSideOnPolygonEdge(isEdgeObstructing);
                    }
                }
            }
        }
    }
    if (!eventHandled) {
        // Check if the current segment start co-incides with a bend event where points are lost
        // and/or points are added or with a degenerate bend event
        handleBendEventWithPointLoss(true);
        handleBendEventWithPointAddition(true);
        handleDegenerateBendEventForSegmentStart();
    }
}

void SPV::BendEventCalculator::handleSegmentToProtrudingVertex(EventSegment *previousEventSegment)
{
    Point edgeStart;
    Point edgeEnd;
    std::vector<Point> extraPoints;
    unsigned indexOfLastSPPoint;
    boost::variant<Point, bool> result;

    if (calculateEventsOnStartSide) {
        edgeStart = previousEventSegment->getSecondLineOfSightFromStart()->getPointOnStartSide();
        edgeEnd = currentEventSegment->getFirstLineOfSightFromStart()->getPointOnStartSide();
        extraPoints = previousEventSegment->getExtraPointsOnStartSide();
        indexOfLastSPPoint = previousEventSegment->getIndexOfLastSPPointOnStartSide();
    } else {
        edgeStart = previousEventSegment->getFirstLineOfSightFromStart()->getPointOnEndSide();
        edgeEnd = currentEventSegment->getSecondLineOfSightFromStart()->getPointOnEndSide();
        extraPoints = previousEventSegment->getExtraPointsOnEndSide();
        indexOfLastSPPoint = previousEventSegment->getIndexOfLastSPPointOnEndSide();
    }

    Point lastShortestPathPoint = shortestPath.at(indexOfLastSPPoint)->getPoint();

    // Check if any points are lost in the segment
    for (int i = extraPoints.size() - 1; i >= 0; i--) {
        Line lineToCheck;
        if (i == 0) {
            lineToCheck = Line(extraPoints.at(i), lastShortestPathPoint);
        } else {
            lineToCheck = Line(extraPoints.at(i), extraPoints.at(i - 1));
        }
        result = gU.getIntersectionBetweenLineAndSegment(lineToCheck, edgeStart, edgeEnd);
        if (result.type() == typeid(bool)) {
            break;
        } else {
            edgeStart = boost::get<Point>(result);
            if (calculateEventsOnStartSide) {
                currentEventSegment->removeExtraPointOnStartSide();
            } else {
                currentEventSegment->removeExtraPointOnEndSide();
            }
        }
    }

    if (calculateEventsOnStartSide) {
        extraPoints = currentEventSegment->getExtraPointsOnStartSide();
    } else {
        extraPoints = currentEventSegment->getExtraPointsOnEndSide();
    }
    if (extraPoints.size() > 0) {
        return;
    }

    // Now check for points on the shortest path which might need adding
    int nextSPIndex;
    while (true) {
        Line lineToCheck;
        if (calculateEventsOnStartSide) {
            nextSPIndex = indexOfLastSPPoint + 1;
            if (nextSPIndex == shortestPath.size()) {
                break;
            }
        } else {
            nextSPIndex = indexOfLastSPPoint - 1;
            if (nextSPIndex < 0) {
                break;
            }
        }
        lineToCheck = Line(lastShortestPathPoint, shortestPath.at(nextSPIndex)->getPoint());
        result = gU.getIntersectionBetweenLineAndSegment(lineToCheck, edgeStart, edgeEnd);
        if (result.type() == typeid(bool)) {
            break;
        } else {
            edgeStart = boost::get<Point>(result);
            indexOfLastSPPoint = nextSPIndex;
            lastShortestPathPoint = shortestPath.at(indexOfLastSPPoint)->getPoint();
            if (calculateEventsOnStartSide) {
                currentEventSegment->setIndexOfLastSPPointOnStartSide(nextSPIndex);
            } else {
                currentEventSegment->setIndexOfLastSPPointOnEndSide(nextSPIndex);
            }
        }

    }
}


void SPV::BendEventCalculator::addPreviousSettingsToCurrentES(EventSegment *previousEventSegment, bool pointsOnly)
{
    std::vector<Point> extraPoints;
    if (calculateEventsOnStartSide) {
        if (!pointsOnly) {
            currentEventSegment->setStartSideLoSVisible(previousEventSegment->getStartSideLoSVisible());
            currentEventSegment->setStartSideOnPolygonEdge(previousEventSegment->getStartSideOnPolygonEdge());
        }
        currentEventSegment->setIndexOfLastSPPointOnStartSide(previousEventSegment->getIndexOfLastSPPointOnStartSide());
        extraPoints = previousEventSegment->getExtraPointsOnStartSide();
        for(unsigned i = 0; i < extraPoints.size(); i++) {
            currentEventSegment->addExtraPointsOnStartSide(extraPoints.at(i));
        }
    } else {
        if (!pointsOnly) {
            currentEventSegment->setEndSideLoSVisible(previousEventSegment->getEndSideLoSVisible());
            currentEventSegment->setEndSideOnPolygonEdge(previousEventSegment->getEndSideOnPolygonEdge());
        }
        currentEventSegment->setIndexOfLastSPPointOnEndSide(previousEventSegment->getIndexOfLastSPPointOnEndSide());
        extraPoints = previousEventSegment->getExtraPointsOnEndSide();
        for(unsigned i = 0; i < extraPoints.size(); i++) {
            currentEventSegment->addExtraPointsOnEndSide(extraPoints.at(i));
        }
    }
}

void SPV::BendEventCalculator::setCurrentSegmentOrderFromLeftToRight()
{
    unsigned currentIndex = currentEventSegment->getPivotPoint()->getIndexOnShortestPath();

    if (calculateEventsOnStartSide) {
        // First segment
        if (!currentEventSegment->hasPredecessor()) {
            currentSegmentOrderFromLeftToRight = isSegmentOrderFromLeftToRight(1);
            return;
        }
        unsigned previousIndex = currentEventSegment->getPredecessor()->getPivotPoint()->getIndexOnShortestPath();

        if (currentIndex != previousIndex) {
            currentSegmentOrderFromLeftToRight = isSegmentOrderFromLeftToRight(currentIndex);
        }
    } else {
        // Last segment
        if (!currentEventSegment->hasSuccessor()) {
            currentSegmentOrderFromLeftToRight = isSegmentOrderFromLeftToRight(currentIndex);
            return;
        }
        unsigned nextIndex = currentEventSegment->getSuccessor()->getPivotPoint()->getIndexOnShortestPath();
        if (currentIndex != nextIndex) {
            currentSegmentOrderFromLeftToRight = isSegmentOrderFromLeftToRight(currentIndex);
        }
    }
}

void SPV::BendEventCalculator::handlePathEvent(EventSegment *previousEventSegment)
{
    // Check if there is a change in the direction of rotation
    unsigned previousIndex = previousEventSegment->getPivotPoint()->getIndexOnShortestPath();
    if (currentSegmentOrderFromLeftToRight != isSegmentOrderFromLeftToRight(previousIndex)) {
        Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
        std::shared_ptr<LineOfSight> firstLoS = currentEventSegment->getFirstLineOfSightFromStart();
        std::shared_ptr<LineOfSight> secondLoS = currentEventSegment->getSecondLineOfSightFromStart();
        bool shortestPathObstructed;

        // The previous index is the last point on the shortest path at the start of this event segment
        if (calculateEventsOnStartSide) {
            currentEventSegment->setIndexOfLastSPPointOnStartSide(previousIndex);
            shortestPathObstructed = gU.isPerpendicularFootObstructedByEdge(
                firstLoS->getPointOnStartSide(),
                secondLoS->getPointOnStartSide(),
                pivotPoint
            );
            currentEventSegment->setStartSideLoSVisible(!shortestPathObstructed);
            currentEventSegment->setStartSideOnPolygonEdge(shortestPathObstructed);
        } else {
            currentEventSegment->setIndexOfLastSPPointOnEndSide(previousIndex);
            shortestPathObstructed = gU.isPerpendicularFootObstructedByEdge(
                secondLoS->getPointOnEndSide(),
                firstLoS->getPointOnEndSide(),
                pivotPoint
            );
            currentEventSegment->setEndSideLoSVisible(!shortestPathObstructed);
            currentEventSegment->setEndSideOnPolygonEdge(shortestPathObstructed);
        }
    } else {
        // The vertices to the line of sight remain the same
        addPreviousSettingsToCurrentES(previousEventSegment, false);

        // Check if the current segment start co-incides with a bend event where points are lost
        // and/or points are added
        handleBendEventWithPointLoss(true);
        handleBendEventWithPointAddition(true);
        handleDegenerateBendEventForSegmentStart();
    }
}
