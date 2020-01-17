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
        PointOnShortestPathTree(PointWithTriangulationInfo *p);
        PointOnShortestPathTree(PointWithTriangulationInfo *p, PointOnShortestPathTree* pt);
        ~PointOnShortestPathTree()
        {
            delete currentPoint;
        }
        Point getPoint();
        PointWithTriangulationInfo* getPointWithTriangulationInfo();
        PointOnShortestPathTree *getPreviousPoint();
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
        PointWithTriangulationInfo *currentPoint;
        PointOnShortestPathTree *previousPointOnTree;
        int indexOnShortestPath = -1;
    };
}

#endif // POINTONSHORTESTPATHTREE_H
