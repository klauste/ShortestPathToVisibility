#include "spvshortestpathtree.h"
SPV::PointOnShortestPath::~PointOnShortestPath()
{
    delete currentPoint;
}

SPV::PointOnShortestPath::PointOnShortestPath(ShortestPathEntry *entry) {
    currentPoint = entry;
}

SPV::PointOnShortestPath::PointOnShortestPath(ShortestPathEntry *entry, PointOnShortestPath* pp) {
    currentPoint = entry;
    previousPoint = pp;
}

Point SPV::PointOnShortestPath::getCurrentPoint() {
    return currentPoint->getPoint();
}

SPV::PointOnShortestPath* SPV::PointOnShortestPath::getPreviousPoint() {
    return previousPoint;
}

bool SPV::PointOnShortestPath::isFinalPoint() {
    return currentPoint->isStartPoint() || currentPoint->isEndPoint();
}

SPV::ShortestPathEntry* SPV::PointOnShortestPath::getCurrentEntry() {
    return currentPoint;
}
