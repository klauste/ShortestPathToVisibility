#ifndef POINTONSHORTESTPATHTREE_H
#define POINTONSHORTESTPATHTREE_H

#include "Models/pointwithtriangulationinfo.h"

namespace SPV {
    /**
     * A PointOnShortestPathTree object links a polygon vertex (defined by a PointWithTriangulationInfo)
     * to its predecessor on the shortest path from the vertex to the root point of the tree
     *
     * @brief The PointOnShortestPathTree class
     */
    class PointOnShortestPathTree {
    public:
        PointOnShortestPathTree(std::shared_ptr<PointWithTriangulationInfo> p);
        PointOnShortestPathTree(std::shared_ptr<PointWithTriangulationInfo> p, std::shared_ptr<PointOnShortestPathTree> pt);

        Point getPoint();
        std::shared_ptr<PointWithTriangulationInfo> getPointWithTriangulationInfo();
        std::shared_ptr<PointOnShortestPathTree> getPreviousPoint();
        bool isFinalPoint();

        void setIndexOnShortestPath(int i)
        {
            indexOnShortestPath = i;
        }

        bool isPartOfShortestPath()
        {
            return indexOnShortestPath > -1;
        }

        int getIndexOnShortestPath()
        {
            return indexOnShortestPath;
        }
    private:
        std::shared_ptr<PointWithTriangulationInfo> currentPoint;
        std::shared_ptr<PointOnShortestPathTree> previousPointOnTree;
        int indexOnShortestPath = -1;
    };
}

#endif // POINTONSHORTESTPATHTREE_H
