#include "Models/pointonshortestpathtree.h"
SPV::PointOnShortestPathTree::PointOnShortestPathTree(PointWithTriangulationInfo *p) {
    currentPoint = p;
}

SPV::PointOnShortestPathTree::PointOnShortestPathTree(PointWithTriangulationInfo *p, PointOnShortestPathTree* pt) {
    currentPoint = p;
    previousPointOnTree = pt;
}

Point SPV::PointOnShortestPathTree::getPoint() {
    return currentPoint->getPoint();
}

SPV::PointOnShortestPathTree* SPV::PointOnShortestPathTree::getPreviousPoint() {
    return previousPointOnTree;
}

SPV::PointWithTriangulationInfo* SPV::PointOnShortestPathTree::getPointWithTriangulationInfo() {
    return currentPoint;
}
