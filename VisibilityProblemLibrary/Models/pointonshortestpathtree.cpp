#include "Models/pointonshortestpathtree.h"
Point SPV::PointOnShortestPathTree::getPoint() {
    return currentPoint;
}

std::shared_ptr<SPV::PointOnShortestPathTree> SPV::PointOnShortestPathTree::getPreviousPoint() {
    return previousPointOnTree;
}

void SPV::PointOnShortestPathTree::setIndexOnShortestPath(int i)
{
    indexOnShortestPath = i;
}

bool SPV::PointOnShortestPathTree::isPartOfShortestPath()
{
    return indexOnShortestPath > -1;
}

int SPV::PointOnShortestPathTree::getIndexOnShortestPath()
{
    return indexOnShortestPath;
}
