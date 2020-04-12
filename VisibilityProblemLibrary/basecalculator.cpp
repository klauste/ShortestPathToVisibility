#include "basecalculator.h"

SPV::BaseCalculator::BaseCalculator(Polygon p, const Point s, Point e)
{
    gU = GeometryUtil();
    currentMinimum = -1;
    std::unique_ptr<ShortestPathTreeCalculator> spt = std::unique_ptr<ShortestPathTreeCalculator>(new ShortestPathTreeCalculator(p, s, e));
    shortestPath = spt->getShortestPath();
    directPathExists = spt->directPathBetweenFinalPointsExists();
    stepPrecision = 0.001;
}

SPV::BaseCalculator::~BaseCalculator()
{
    if (!directPathExists) {
        if (firstEventSegment->hasSuccessor()) {
            EventSegment *currentSegment = firstEventSegment->getSuccessor();
            bool allDeleted = false;
            while(!allDeleted) {
                if (currentSegment->hasSuccessor()) {
                    EventSegment *toBeDeleted = currentSegment;
                    currentSegment = currentSegment->getSuccessor();
                    delete toBeDeleted;
                } else {
                    delete currentSegment;
                    allDeleted = true;
                }
            }
        }
        delete firstEventSegment;
    }
}

SPV::GeometryUtil SPV::BaseCalculator::getGeometryUtil()
{
    return gU;
}

bool SPV::BaseCalculator::hasDirectPath()
{
    return directPathExists;
}

SPV::EventSegment* SPV::BaseCalculator::getFirstEventSegment()
{
    return firstEventSegment;
}

std::vector<std::shared_ptr<SPV::PointOnShortestPath>> SPV::BaseCalculator::getShortestPath()
{
    return shortestPath;
}

Point SPV::BaseCalculator::getLastPointBeforeLoS(EventSegment *eS, bool onStartSide) {
    std::vector<Point> extraPoints;
    if (onStartSide) {
        extraPoints = eS->getExtraPointsOnStartSide();
        if (extraPoints.size() > 0) {
            return extraPoints.at(extraPoints.size() - 1);
        }
        return shortestPath.at(eS->getIndexOfLastSPPointOnStartSide())->getPoint();
    }
    extraPoints = eS->getExtraPointsOnEndSide();
    if (extraPoints.size() > 0) {
        return extraPoints.at(extraPoints.size() - 1);
    }
    return shortestPath.at(eS->getIndexOfLastSPPointOnEndSide())->getPoint();
}

void SPV::BaseCalculator::setMinimumDetails(
    std::shared_ptr<Minimum> min,
    double newMinimumValue,
    Point startSideIntersectionOnLoS,
    Point endSideIntersectionOnLoS,
    Point startSideIntersectionOnEdge,
    Point endSideIntersectionOnEdge,
    bool isMinSectorStart,
    bool isMinSectorEnd
)
{
    min->setEventSegment(currentEventSegment);
    min->setDistance(newMinimumValue);
    min->setStartSideIntersectionOnLoS(startSideIntersectionOnLoS);
    min->setEndSideIntersectionOnLoS(endSideIntersectionOnLoS);
    min->setStartSideIntersectionOnEdge(startSideIntersectionOnEdge);
    min->setEndSideIntersectionOnEdge(endSideIntersectionOnEdge);
    min->setDistance(currentMinimum);
    min->setMinSectorStart(isMinSectorStart);
    min->setMinSectorEnd(isMinSectorEnd);
}

double SPV::BaseCalculator::getDistanceToIntersectionPoint(Point intersectionPoint, bool onStartSide)
{
    Point lastPointOnPath = getLastPointBeforeLoS(currentEventSegment, onStartSide);

    return sqrt(CGAL::squared_distance(lastPointOnPath, intersectionPoint));
}

Point SPV::BaseCalculator::getIntersectionPointOnLoS(Point intersectionPointOnBoundary, bool onStartSide)
{
    Point lastPointOnPath = getLastPointBeforeLoS(currentEventSegment, onStartSide);
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();

    // If the last point on the path is the pivotPoint, return that as intersection
    if (gU.pointsAreEqual(lastPointOnPath, pivotPoint)) {
        return pivotPoint;
    }

    // If the last point on the path is on the LoS return the last point on the path
    if (gU.isPointOnSegment(Segment(intersectionPointOnBoundary, pivotPoint), lastPointOnPath)) {
        return lastPointOnPath;
    }

    if (!currentEventSegment->isLoSVisible(onStartSide)) {
        return intersectionPointOnBoundary;
    }

    return gU.getPerpendicularIntersectionPoint(Line(intersectionPointOnBoundary, pivotPoint), lastPointOnPath);
}

void SPV::BaseCalculator::handleNewGlobalMinimum (
    double newMinimumValue,
    Point startSideIntersectionOnLoS,
    Point endSideIntersectionOnLoS,
    Point startSideIntersectionOnEdge,
    Point endSideIntersectionOnEdge,
    bool calculateMinimumSector
)
{
    if (currentMinimum >= 0 && gU.isLarger(newMinimumValue, currentMinimum)) {
        return;
    }

    if (currentMinimum < 0) {
        currentMinimum = newMinimumValue;
    }

    if (gU.isLarger(currentMinimum, newMinimumValue)) {
        currentMinimum = newMinimumValue;

        if (allMinima.size() > 0) {
            allMinima.clear();
        }
    }

    bool isMinSectorStart = calculateMinimumSector;
    bool isMinSectorEnd = false;
    if (allMinima.size() > 0) {
        auto lastMin = allMinima.back();

        // If this is a duplicate, then there is nothing to do
        if (gU.pointsAreEqual(lastMin->getStartSideIntersectionOnLoS(), startSideIntersectionOnLoS)) {
            return;
        }
        if (calculateMinimumSector) {
            // If the last minimum was the sector start, this minimum should be the sector end
            if (lastMin->isMinSectorStart()) {
                isMinSectorStart = false;
                isMinSectorEnd = true;
            // If the last minium was the sector end, reset it
            } else if (lastMin->isMinSectorEnd()) {
                setMinimumDetails(
                    lastMin,
                    newMinimumValue,
                    startSideIntersectionOnLoS,
                    endSideIntersectionOnLoS,
                    startSideIntersectionOnEdge,
                    endSideIntersectionOnEdge,
                    false,
                    true
                );
                return;
            }
        }
    }
    std::shared_ptr<Minimum> newMinimum = std::make_shared<Minimum>();
    setMinimumDetails(
        newMinimum,
        newMinimumValue,
        startSideIntersectionOnLoS,
        endSideIntersectionOnLoS,
        startSideIntersectionOnEdge,
        endSideIntersectionOnEdge,
        isMinSectorStart,
        isMinSectorEnd
    );
    allMinima.push_back(newMinimum);
}

std::vector<std::shared_ptr<SPV::Minimum>> SPV::BaseCalculator::getAllMinima() {
    return allMinima;
}

Point SPV::BaseCalculator::getFurthestPointOnBoundary(bool onStartSide, bool firstLoS)
{
    bool hasNeighbor = false;
    Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();
    Point currentPoint, otherPotentialPoint;
    std::shared_ptr<LineOfSight> loS, neighborLoS;

    if (firstLoS) {
        loS = currentEventSegment->getFirstLineOfSightFromStart();
        if (currentEventSegment->hasPredecessor()) {
            hasNeighbor = true;
            neighborLoS = currentEventSegment->getPredecessor()->getSecondLineOfSightFromStart();
        }
    } else {
        loS = currentEventSegment->getSecondLineOfSightFromStart();
        if (currentEventSegment->hasSuccessor()) {
            hasNeighbor = true;
            neighborLoS = currentEventSegment->getSuccessor()->getFirstLineOfSightFromStart();
        }
    }
    if (onStartSide) {
        currentPoint = loS->getPointOnStartSide();
        // If this is not a vertex, it is already furthest on the boundary
        if (!loS->isStartPointVertex() || !hasNeighbor) {
            return currentPoint;
        }
        otherPotentialPoint = neighborLoS->getPointOnStartSide();
    } else {
        currentPoint = loS->getPointOnEndSide();
        // If this is not a vertex, it is already furthest on the boundary
        if (!loS->isEndPointVertex() || !hasNeighbor) {
            return currentPoint;
        }
        otherPotentialPoint = neighborLoS->getPointOnEndSide();
    }
    if (CGAL::squared_distance(pivotPoint, otherPotentialPoint) > CGAL::squared_distance(pivotPoint, currentPoint)) {
        return otherPotentialPoint;
    }
    return currentPoint;
}
