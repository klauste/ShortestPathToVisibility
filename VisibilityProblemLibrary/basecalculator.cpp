#include "basecalculator.h"

SPV::BaseCalculator::BaseCalculator(const Polygon &p, const Point s, Point e) {
    gU = GeometryUtil();
    std::unique_ptr<ShortestPathTreeCalculator> spt = std::unique_ptr<ShortestPathTreeCalculator>(new ShortestPathTreeCalculator(p, s, e));
    shortestPath = spt->getShortestPath();
}

SPV::EventSegment* SPV::BaseCalculator::getFirstEventSegment()
{
    return firstEventSegment;
}

const std::vector<std::shared_ptr<SPV::PointOnShortestPath>> SPV::BaseCalculator::getShortestPath()
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
