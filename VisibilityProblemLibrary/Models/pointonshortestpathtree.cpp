#include "Models/pointonshortestpathtree.h"
SPV::PointOnShortestPathTree::PointOnShortestPathTree(std::shared_ptr<PointWithTriangulationInfo> p) {
    currentPoint = p;
}

SPV::PointOnShortestPathTree::PointOnShortestPathTree(std::shared_ptr<PointWithTriangulationInfo> p, std::shared_ptr<PointOnShortestPathTree> pt) {
    currentPoint = p;
    previousPointOnTree = pt;
}

Point SPV::PointOnShortestPathTree::getPoint() {
    return currentPoint->getPoint();
}

std::shared_ptr<SPV::PointOnShortestPathTree> SPV::PointOnShortestPathTree::getPreviousPoint() {
    return previousPointOnTree;
}

std::shared_ptr<SPV::PointWithTriangulationInfo> SPV::PointOnShortestPathTree::getPointWithTriangulationInfo() {
    return currentPoint;
}
