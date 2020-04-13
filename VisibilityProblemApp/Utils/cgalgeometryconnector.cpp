#include "cgalgeometryconnector.h"
CGALGeometryConnector::CGALGeometryConnector()
{
    polygon = Polygon();
    minSquaredDistanceToStartPoint = 400;
    interpolationRunning = false;
    currentInterpolationState = InterpolationResult();
    currentInterpolationState.lineOfSight = QLineF();
    currentInterpolationState.startSideToLoS = QLineF();
    currentInterpolationState.endSideToLoS = QLineF();
}

std::vector<std::shared_ptr<QLineF>> CGALGeometryConnector::getShortestPathGraph()
{
    return shortestPathGraph;
}

std::vector<std::shared_ptr<QLineF>> CGALGeometryConnector::getPathEvents()
{
    return pathEvents;
}

std::vector<std::shared_ptr<QLineF>> CGALGeometryConnector::getBoundaryEvents()
{
    return boundaryEvents;
}

std::vector<std::shared_ptr<QLineF>> CGALGeometryConnector::getBendEvents()
{
    return bendEvents;
}

std::vector<std::shared_ptr<CGALGeometryConnector::MinData>> CGALGeometryConnector::getMinMaxMinima()
{
    return minMaxMinima;
}

std::vector<std::shared_ptr<CGALGeometryConnector::MinData>> CGALGeometryConnector::getMinSumMinima()
{
    return minSumMinima;
}

bool CGALGeometryConnector::shouldClosePolyline(QPointF p)
{
    if (polygon.size() < 3) {
        return false;
    }
    Point firstPointInPolygon = polygon.vertex(0);
    Point currentCgalPoint = Point(p.x(), p.y());
    double distance = CGAL::squared_distance(currentCgalPoint, firstPointInPolygon);

    return (distance < minSquaredDistanceToStartPoint);
}

void CGALGeometryConnector::addPointToCGALPolygon(QPointF p)
{
    Point currentCgalPoint = Point(p.x(), p.y());
    if (polygon.size() > 0) {
        addedSegments.push_back(Segment(polygon.vertex(polygon.size() - 1), currentCgalPoint));
    }
    polygon.push_back(currentCgalPoint);
}

bool CGALGeometryConnector::isPointInPolygon(QPointF p)
{
    Point pointToCheck = Point(p.x(), p.y());
    return (polygon.bounded_side(pointToCheck) == CGAL::ON_BOUNDED_SIDE);
}

void CGALGeometryConnector::handleFinalPoint(QPointF p, bool isStart)
{
    if (isStart) {
        startPoint = Point(p.x(), p.y());
    } else {
        endPoint = Point(p.x(), p.y());
        calculateMinima();
    }
}

bool CGALGeometryConnector::doSegmentsIntersect(QPointF p)
{
    if (polygon.size() < 2) {
        return false;
    }
    Point lastPointInPolygon = polygon.vertex(polygon.size() - 1);
    Segment newSegment = Segment(lastPointInPolygon, Point(p.x(), p.y()));

    for (auto &currentSegment : addedSegments) {
        Point currentEndPoint = currentSegment.target();
        bool checkIntersect = currentEndPoint != lastPointInPolygon;

        if (checkIntersect && CGAL::do_intersect(currentSegment, newSegment)) {
            return true;
        }
    }
    return false;
}

void CGALGeometryConnector::reset()
{
    if (minMaxCalculator) {
        delete minMaxCalculator;
        minMaxCalculator = nullptr;
    }
    if (minSumCalculator) {
        delete minSumCalculator;
        minSumCalculator = nullptr;
    }
    polygon.clear();
    addedSegments.clear();
    pathEvents.clear();
    boundaryEvents.clear();
    bendEvents.clear();
    minMaxMinima.clear();
    minSumMinima.clear();
    shortestPathGraph.clear();
}

void CGALGeometryConnector::calculateMinima()
{
    unsigned i;
    minMaxCalculator = new SPV::MinMaxCalculator(polygon, startPoint, endPoint);
    minMaxCalculator->calculateMinima();
    firstSegment = minMaxCalculator->getFirstEventSegment();
    shortestPath = minMaxCalculator->getShortestPath();
    minSumCalculator = new SPV::MinSumCalculator(polygon, startPoint, endPoint);
    minSumCalculator->calculateMinima();

    for (i = 0; i < shortestPath.size() - 1; i++) {
        Point currentPoint = shortestPath.at(i)->getPoint();
        Point nextPoint = shortestPath.at(i + 1)->getPoint();
        auto newLine = std::make_shared<QLineF>(currentPoint.x(), currentPoint.y(), nextPoint.x(), nextPoint.y());
        shortestPathGraph.push_back(newLine);
    }

    if (!minMaxCalculator->hasDirectPath()) {
        setEvents();
        setMinima();
    }
}

void CGALGeometryConnector::setMinima()
{
    unsigned i;
    std::vector<std::shared_ptr<SPV::Minimum>> allMinima = minMaxCalculator->getAllMinima();
    for (i = 0; i < allMinima.size(); i++) {
        auto min = allMinima.at(i);
        double minValue = min->getDistance();
        Point p1 = min->getStartSideIntersectionOnEdge();
        Point p2 = min->getEndSideIntersectionOnEdge();
        auto loS = std::make_shared<QLineF>(p1.x(), p1.y(), p2.x(), p2.y());
        auto newMin = std::make_shared<MinData>(loS, minValue, min->getStartSideIntersectionOnLoS(), min->getEndSideIntersectionOnLoS());
        setLinesToMin(min, newMin);

        if (min->getIsInDiscArea()) {
            newMin->hasRadius = true;
            newMin->radius = min->getDiscRadius();
            Point cP;
            if (min->isDiscOnStartSide()) {
                cP = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), true);
            } else {
                cP = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), false);
            }
            newMin->centerPoint = QPointF(cP.x(), cP.y());
        }
        minMaxMinima.push_back(newMin);

    }

    allMinima.clear();
    allMinima = minSumCalculator->getAllMinima();
    for (i = 0; i < allMinima.size(); i++) {
        auto min = allMinima.at(i);
        double minValue = min->getDistance();
        Point p1 = min->getStartSideIntersectionOnEdge();
        Point p2 = min->getEndSideIntersectionOnEdge();
        auto loS = std::make_shared<QLineF>(p1.x(), p1.y(), p2.x(), p2.y());
        auto newMin = std::make_shared<MinData>(loS, minValue, min->getStartSideIntersectionOnLoS(), min->getEndSideIntersectionOnLoS());
        setLinesToMin(min, newMin);
        minSumMinima.push_back(newMin);
    }
}

void CGALGeometryConnector::setLinesToMin(std::shared_ptr<SPV::Minimum> min, std::shared_ptr<MinData> data)
{
    int i;
    Point p1 = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), true);
    Point p2 = min->getStartSideIntersectionOnLoS();
    auto newLine = std::make_shared<QLineF>(p1.x(), p1.y(), p2.x(), p2.y());
    data->linesToMin.push_back(newLine);

    p1 = minMaxCalculator->getLastPointBeforeLoS(min->getEventSegment(), false);
    p2 = min->getEndSideIntersectionOnLoS();
    newLine = std::make_shared<QLineF>(p1.x(), p1.y(), p2.x(), p2.y());
    data->linesToMin.push_back(newLine);

    for (i = 0; i < (int)min->getEventSegment()->getExtraPointsOnStartSide().size() - 1; i++) {
        p1 = min->getEventSegment()->getExtraPointsOnStartSide().at(i);
        p2 = min->getEventSegment()->getExtraPointsOnStartSide().at(i + 1);
        newLine = std::make_shared<QLineF>(p1.x(), p1.y(), p2.x(), p2.y());
        data->linesToMin.push_back(newLine);
    }
    for (i = 0; i < (int)min->getEventSegment()->getExtraPointsOnEndSide().size() - 1; i++) {
        p1 = min->getEventSegment()->getExtraPointsOnEndSide().at(i);
        p2 = min->getEventSegment()->getExtraPointsOnEndSide().at(i + 1);
        newLine = std::make_shared<QLineF>(p1.x(), p1.y(), p2.x(), p2.y());
        data->linesToMin.push_back(newLine);
    }

    unsigned index = min->getEventSegment()->getIndexOfLastSPPointOnStartSide();
    for (i = 0; i <= index; i++) {
        if (i == index) {
            if (min->getEventSegment()->getExtraPointsOnStartSide().size() > 0) {
                p1 = shortestPath.at(i)->getPoint();
                p2 = min->getEventSegment()->getExtraPointsOnStartSide().front();
            } else {
                break;
            }
        } else {
            p1 = shortestPath.at(i)->getPoint();
            p2 = shortestPath.at(i + 1)->getPoint();
        }
        newLine = std::make_shared<QLineF>(p1.x(), p1.y(), p2.x(), p2.y());
        data->linesToMin.push_back(newLine);
    }

    index = min->getEventSegment()->getIndexOfLastSPPointOnEndSide();
    for (i = shortestPath.size() - 1; i >= index; i--) {
        if (i == index) {
            if (min->getEventSegment()->getExtraPointsOnEndSide().size() > 0) {
                p1 = shortestPath.at(i)->getPoint();
                p2 = min->getEventSegment()->getExtraPointsOnEndSide().front();
            } else {
                break;
            }
        } else {
            p1 = shortestPath.at(i)->getPoint();
            p2 = shortestPath.at(i - 1)->getPoint();
        }
        newLine = std::make_shared<QLineF>(p1.x(), p1.y(), p2.x(), p2.y());
        data->linesToMin.push_back(newLine);
    }
}

void CGALGeometryConnector::setEvents()
{
    SPV::EventSegment *currentSegment = firstSegment;
    Point furthestPointStartSide, furthestPointEndSide;
    SPV::EventSegment *previousSegment;
    Point pivotPoint;
    bool allEventsHandled = false;

    while (!allEventsHandled) {
        pivotPoint = currentSegment->getPivotPoint()->getPoint();
        auto currentLos = currentSegment->getFirstLineOfSightFromStart();
        furthestPointStartSide = currentLos->getPointOnStartSide();
        furthestPointEndSide = currentLos->getPointOnEndSide();
        if (currentSegment->hasPredecessor()) {
            previousSegment =  currentSegment->getPredecessor();
            auto previousLos = previousSegment->getSecondLineOfSightFromStart();
            if (CGAL::squared_distance(previousLos->getPointOnStartSide(), pivotPoint) >
                    CGAL::squared_distance(furthestPointStartSide, pivotPoint)) {
                furthestPointStartSide = previousLos->getPointOnStartSide();
            }
            if (CGAL::squared_distance(previousLos->getPointOnEndSide(), pivotPoint) >
                    CGAL::squared_distance(furthestPointEndSide, pivotPoint)) {
                furthestPointEndSide = previousLos->getPointOnEndSide();
            }
        }
        switch (currentLos->getEventType()) {
            case PATH: pathEvents.push_back(std::make_shared<QLineF>(
                furthestPointStartSide.x(),
                furthestPointStartSide.y(),
                furthestPointEndSide.x(),
                furthestPointEndSide.y()
            ));
            break;
        case BOUNDARY: boundaryEvents.push_back(std::make_shared<QLineF>(
                furthestPointStartSide.x(),
                furthestPointStartSide.y(),
                furthestPointEndSide.x(),
                furthestPointEndSide.y()
            ));
            break;
        case BEND: bendEvents.push_back(std::make_shared<QLineF>(
                furthestPointStartSide.x(),
                furthestPointStartSide.y(),
                furthestPointEndSide.x(),
                furthestPointEndSide.y()
            ));
        }
        if (currentSegment->hasSuccessor()) {
            currentSegment = currentSegment->getSuccessor();
        } else {
            allEventsHandled = true;
        }
    }
    // The last event is a path event
    auto lastLos = currentSegment->getSecondLineOfSightFromStart();
    pathEvents.push_back(std::make_shared<QLineF>(
        lastLos->getPointOnStartSide().x(),
        lastLos->getPointOnStartSide().y(),
        lastLos->getPointOnEndSide().x(),
        lastLos->getPointOnEndSide().y()
    ));
}

CGALGeometryConnector::InterpolationResult CGALGeometryConnector::getStartOfInterpolation()
{
    if (!minMaxCalculator || interpolationRunning == true) {
        currentInterpolationState.canStartInterpolation = false;
        currentInterpolationState.hasReachedEndPoint = false;
        return currentInterpolationState;
    }
    currentSegmentInInterpolation = minMaxCalculator->getFirstEventSegment();

    auto fL = currentSegmentInInterpolation->getFirstLineOfSightFromStart();
    QPointF p = QPointF(fL->getPointOnStartSide().x(), fL->getPointOnStartSide().y());
    currentInterpolationState.lineOfSight.setP1(p);
    p = QPointF(fL->getPointOnEndSide().x(), fL->getPointOnEndSide().y());
    currentInterpolationState.lineOfSight.setP2(p);
    currentInterpolationState.canStartInterpolation = true;
    currentInterpolationState.hasReachedEndPoint = false;
    currentInterpolationValue = 0.0;
    interpolationRunning = true;
    setCurrentStepPrecision();
    setPathSoFar();
    Line startToPivot = Line(fL->getPointOnStartSide(), currentSegmentInInterpolation->getPivotPoint()->getPoint());
    if (!setLineToLos(true, startToPivot, fL->getPointOnStartSide())) {
        // If this happens, something went wrong. Simply stop the interpolation.
        currentInterpolationState.hasReachedEndPoint = true;
        interpolationRunning = false;
        return currentInterpolationState;
    }
    if (!setLineToLos(false, startToPivot, fL->getPointOnEndSide())) {
        // If this happens, something went wrong. Simply stop the interpolation.
        currentInterpolationState.hasReachedEndPoint = true;
        interpolationRunning = false;
        return currentInterpolationState;
    }
    return currentInterpolationState;
}

CGALGeometryConnector::InterpolationResult CGALGeometryConnector::getNextInterpolationResult()
{
    currentInterpolationValue += currentStepPrecision;
    if (currentInterpolationValue > 1) {
        if (currentSegmentInInterpolation->hasSuccessor()) {
            currentSegmentInInterpolation = currentSegmentInInterpolation->getSuccessor();
            setCurrentStepPrecision();
            setPathSoFar();
            currentInterpolationValue = currentInterpolationValue - 1;
        } else {
            currentInterpolationState.hasReachedEndPoint = true;
            interpolationRunning = false;
            return currentInterpolationState;
        }
    } else {
        currentInterpolationState.pathSoFarHasChanged = false;
    }
    auto fL = currentSegmentInInterpolation->getFirstLineOfSightFromStart();
    auto sL = currentSegmentInInterpolation->getSecondLineOfSightFromStart();

    Point pointOnStartSide = Point(
        (1 - currentInterpolationValue) * fL->getPointOnStartSide().x() + currentInterpolationValue * sL->getPointOnStartSide().x(),
        (1 - currentInterpolationValue) * fL->getPointOnStartSide().y() + currentInterpolationValue * sL->getPointOnStartSide().y()
    );
    Line startToPivot =  Line(pointOnStartSide, currentSegmentInInterpolation->getPivotPoint()->getPoint());
    Point pointOnEndSide;

    auto result = minMaxCalculator->getGeometryUtil().getIntersectionBetweenLineAndLine(startToPivot, fL->getPointOnEndSide(), sL->getPointOnEndSide());
    if (result.type() == typeid(bool)) {
        // If this happens, something went wrong. Simply stop the interpolation.
        currentInterpolationState.hasReachedEndPoint = true;
        interpolationRunning = false;
        return currentInterpolationState;
    } else {
        pointOnEndSide = boost::get<Point>(result);
    }

    QPointF p = QPointF(pointOnStartSide.x(), pointOnStartSide.y());
    currentInterpolationState.lineOfSight.setP1(p);
    p = QPointF(pointOnEndSide.x(), pointOnEndSide.y());
    currentInterpolationState.lineOfSight.setP2(p);

    if (!setLineToLos(true, startToPivot, pointOnStartSide)) {
        // If this happens, something went wrong. Simply stop the interpolation.
        currentInterpolationState.hasReachedEndPoint = true;
        interpolationRunning = false;
        return currentInterpolationState;
    }
    if (!setLineToLos(false, startToPivot, pointOnEndSide)) {
        // If this happens, something went wrong. Simply stop the interpolation.
        currentInterpolationState.hasReachedEndPoint = true;
        interpolationRunning = false;
        return currentInterpolationState;
    }
    return currentInterpolationState;
}

void CGALGeometryConnector::setPathSoFar()
{
    unsigned index = currentSegmentInInterpolation->getIndexOfLastSPPointOnStartSide();
    unsigned i;
    Point p1;
    Point p2;
    QLineF line;
    std::vector<Point> extraPoints;
    currentInterpolationState.pathSoFar.clear();
    if (index > 0) {
        for (i = 0; i < index; i++) {
            p1 = shortestPath.at(i)->getPoint();
            p2 = shortestPath.at(i + 1)->getPoint();
            line = QLineF();
            line.setP1(QPointF(p1.x(), p1.y()));
            line.setP2(QPointF(p2.x(), p2.y()));
            currentInterpolationState.pathSoFar.push_back(line);
        }
    }
    extraPoints = currentSegmentInInterpolation->getExtraPointsOnStartSide();
    if (extraPoints.size() > 0) {
        for (i = 0; i < extraPoints.size(); i++) {
            if (i == 0) {
                p1 = shortestPath.at(index)->getPoint();
                p2 = extraPoints.at(i);
                line = QLineF();
                line.setP1(QPointF(p1.x(), p1.y()));
                line.setP2(QPointF(p2.x(), p2.y()));
                currentInterpolationState.pathSoFar.push_back(line);
            } else {
                p1 = extraPoints.at(i - 1);
            }
            p2 = extraPoints.at(i);
            line = QLineF();
            line.setP1(QPointF(p1.x(), p1.y()));
            line.setP2(QPointF(p2.x(), p2.y()));
            currentInterpolationState.pathSoFar.push_back(line);
        }
    }
    index = currentSegmentInInterpolation->getIndexOfLastSPPointOnEndSide();
    if (index != shortestPath.size() - 1) {
        for (i = index; i < shortestPath.size() - 1; i++) {
            p1 = shortestPath.at(i)->getPoint();
            p2 = shortestPath.at(i + 1)->getPoint();
            line = QLineF();
            line.setP1(QPointF(p1.x(), p1.y()));
            line.setP2(QPointF(p2.x(), p2.y()));
            currentInterpolationState.pathSoFar.push_back(line);
        }
    }
    extraPoints = currentSegmentInInterpolation->getExtraPointsOnEndSide();
    if (extraPoints.size() > 0) {
        for (i = 0; i < extraPoints.size(); i++) {
            if (i == 0) {
                p1 = shortestPath.at(index)->getPoint();
                p2 = extraPoints.at(i);
                line = QLineF();
                line.setP1(QPointF(p1.x(), p1.y()));
                line.setP2(QPointF(p2.x(), p2.y()));
                currentInterpolationState.pathSoFar.push_back(line);
            } else {
                p1 = extraPoints.at(i - 1);
            }
            p2 = extraPoints.at(i);
            line = QLineF();
            line.setP1(QPointF(p1.x(), p1.y()));
            line.setP2(QPointF(p2.x(), p2.y()));
            currentInterpolationState.pathSoFar.push_back(line);
        }
    }
    currentInterpolationState.pathSoFarHasChanged = true;
}

bool CGALGeometryConnector::setLineToLos(bool onStart, Line currentLoS, Point pointOnEdge)
{
    QPointF p;
    Point pointOnLos;
    boost::variant<Point, bool> result;
    Point lastPointBeforeLos = minMaxCalculator->getLastPointBeforeLoS(currentSegmentInInterpolation, onStart);

    if (onStart) {
        if (currentSegmentInInterpolation->getStartSideLoSVisible()) {
            result = minMaxCalculator->getGeometryUtil().getPerpendicularIntersectionPoint(currentLoS, lastPointBeforeLos);
            if (result.type() == typeid(bool)) {
                return false;
            } else {
                pointOnLos = boost::get<Point>(result);
            }
        } else {
            pointOnLos = pointOnEdge;
        }
        p = QPointF(lastPointBeforeLos.x(), lastPointBeforeLos.y());
        currentInterpolationState.startSideToLoS.setP1(p);
        p = QPointF(pointOnLos.x(), pointOnLos.y());
        currentInterpolationState.startSideToLoS.setP2(p);
    } else {
        if (currentSegmentInInterpolation->getEndSideLoSVisible()) {
            result = minMaxCalculator->getGeometryUtil().getPerpendicularIntersectionPoint(currentLoS, lastPointBeforeLos);
            if (result.type() == typeid(bool)) {
                return false;
            } else {
                pointOnLos = boost::get<Point>(result);
            }
        } else {
            pointOnLos = pointOnEdge;
        }
        p = QPointF(lastPointBeforeLos.x(), lastPointBeforeLos.y());
        currentInterpolationState.endSideToLoS.setP1(p);
        p = QPointF(pointOnLos.x(), pointOnLos.y());
        currentInterpolationState.endSideToLoS.setP2(p);
    }
    return true;
}

void CGALGeometryConnector::setCurrentStepPrecision()
{
    auto fL = currentSegmentInInterpolation->getFirstLineOfSightFromStart();
    auto sL = currentSegmentInInterpolation->getSecondLineOfSightFromStart();
    double currentAngle = getDegreeAngleBetweenLoS(
        currentSegmentInInterpolation->getPivotPoint()->getPoint(),
        fL->getPointOnStartSide(),
        sL->getPointOnStartSide()
    );
    currentStepPrecision = 1 / (2 * currentAngle);
}

double CGALGeometryConnector::getDegreeAngleBetweenLoS(Point pivotPoint, Point pOnFirstLoS, Point pOnSecondLoS)
{
    Line firstToPivot = Line(pOnFirstLoS, pivotPoint);
    boost::variant<Point, bool> result = minMaxCalculator->getGeometryUtil().
            getPerpendicularIntersectionPoint(firstToPivot, pOnSecondLoS);
    if (result.type() == typeid(bool)) {
        return 0;
    }
    double d1 = sqrt(CGAL::squared_distance(pivotPoint, boost::get<Point>(result)));
    double d2 = sqrt(CGAL::squared_distance(pivotPoint, pOnSecondLoS));
    double cosValue = d1 / d2;
    return acos(cosValue) * 180 / M_PI;
}
