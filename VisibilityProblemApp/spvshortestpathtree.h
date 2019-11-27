#ifndef SPVSHORTESTPATHTREE_H
#define SPVSHORTESTPATHTREE_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include "spventryonshortestpath.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

namespace SPV {
    /**
     * A PointOnShortestPath object links a polygon vertex to its predecessor on the shortest
     * path from the vertex to either the start or the end point
     *
     * @brief The PointOnShortestPath class
     */
    class PointOnShortestPath {
    public:
        PointOnShortestPath(ShortestPathEntry *entry);
        PointOnShortestPath(ShortestPathEntry *entry, PointOnShortestPath* pp);
        Point getCurrentPoint();
        ShortestPathEntry* getCurrentEntry();
        PointOnShortestPath *getPreviousPoint();
        bool isFinalPoint();
    private:
        ShortestPathEntry *currentPoint;
        PointOnShortestPath *previousPoint;
    };
}

#endif // SPVSHORTESTPATHTREE_H
