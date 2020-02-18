#ifndef POINTONSHORTESTPATHTREE_H
#define POINTONSHORTESTPATHTREE_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

namespace SPV {
    /**
     * @brief The PointOnShortestPathTree class links a polygon vertex to its predecessor on the
     * shortest path from the vertex to the root point of the tree
     */
    class PointOnShortestPathTree {
    public:
        PointOnShortestPathTree(Point p) :
            currentPoint(p),
            indexOnShortestPath(-1)
        {}

        PointOnShortestPathTree(
            Point p,
            std::shared_ptr<PointOnShortestPathTree> pt
        ) : currentPoint(p),
            previousPointOnTree(pt),
            indexOnShortestPath(-1)
        {}

        /**
         * @brief getPoint return this instance's CGAL point
         * @return
         */
        Point getPoint();

        /**
         * @brief getPreviousPoint returns this instance's predecessor
         * @return
         */
        std::shared_ptr<PointOnShortestPathTree> getPreviousPoint();

        /**
         * @brief setIndexOnShortestPath sets this point's index on the shortest path
         * @param i
         */
        void setIndexOnShortestPath(int i);

        /**
         * @brief isPartOfShortestPath returns if a boolean indicating if this point is part of
         * the shortest path
         * @return
         */
        bool isPartOfShortestPath();

        /**
         * @brief getIndexOnShortestPath returns this point's index on the shortest path
         * @return
         */
        int getIndexOnShortestPath();
    private:
        /**
         * @brief currentPoint the instance's CGAL Point
         */
        Point currentPoint;

        /**
         * @brief previousPointOnTree this point's predecessor
         */
        std::shared_ptr<PointOnShortestPathTree> previousPointOnTree;

        /**
         * @brief indexOnShortestPath this point's index on the shortest path
         */
        int indexOnShortestPath;
    };
}

#endif // POINTONSHORTESTPATHTREE_H
