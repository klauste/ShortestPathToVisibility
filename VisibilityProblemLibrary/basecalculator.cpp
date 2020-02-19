#include "basecalculator.h"

SPV::BaseCalculator::BaseCalculator(const Polygon &p, const Point s, Point e) {
    gU = GeometryUtil();
    stepPrecision = 0.001;
    currentMinimum = -1;
    std::unique_ptr<ShortestPathTreeCalculator> spt = std::unique_ptr<ShortestPathTreeCalculator>(new ShortestPathTreeCalculator(p, s, e));
    shortestPath = spt->getShortestPath();
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
