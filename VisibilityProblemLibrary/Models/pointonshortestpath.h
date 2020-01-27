#ifndef POINTONSHORTESTPATH_H
#define POINTONSHORTESTPATH_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>
#include "Models/sweptsegment.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

namespace SPV {
    /**
     * Contains the following information for a point on the shortest path:
     * - The point's coordinates
     * - the point's type: start point, mid point or end point
     * - two vectors containing the edges or part of the edges swept over by the two halfs of the line of sight.
     *   The edges are stored in order from left to right.
     *
     * @brief The ShortestPathEntry class
     */
    class PointOnShortestPath
    {
    public:
        PointOnShortestPath(Point p) : point(p) {}
        ~PointOnShortestPath()
        {
            segmentsFromStart.clear();
            segmentsFromEnd.clear();
        }

        Point getPoint()
        {
            return point;
        }

        std::vector<std::shared_ptr<SweptSegment>> getSegmentsFromStart()
        {
            return segmentsFromStart;
        }

        std::vector<std::shared_ptr<SweptSegment>> getSegmentsFromEnd()
        {
            return segmentsFromEnd;
        }

        void addSegmentFromStart(std::shared_ptr<SweptSegment> s)
        {
            segmentsFromStart.push_back(s);
        }

        void addSegmentFromEnd(std::shared_ptr<SweptSegment> s)
        {
            segmentsFromEnd.push_back(s);
        }

        unsigned getIndexOnShortestPath()
        {
            return indexOnShortestPath;
        }

        void setIndexOnShortestPath(unsigned i)
        {
            indexOnShortestPath = i;
        }

        double getDistanceFromStartPoint()
        {
            return distanceFromStartPoint;
        }

        double getDistanceFromEndPoint()
        {
            return distanceFromEndPoint;
        }

        void setDistanceFromStartPoint(double d)
        {
            distanceFromStartPoint = d;
        }

        void setDistanceFromEndPoint(double d)
        {
            distanceFromEndPoint = d;
        }
    private:
        /**
         * Contains the coordinates of this point.
         *
         * @brief point
         */
        Point point;

        /**
         * The segments swept by the line of sight through this point
         * found in the start point's shortest path map
         * @brief segmentsFromStart
         */
        std::vector<std::shared_ptr<SweptSegment>> segmentsFromStart;

        /**
         * The segments swept by the line of sight through this point
         * found in th end point's shortest path map
         * @brief segmentsFromEnd
         */
        std::vector<std::shared_ptr<SweptSegment>> segmentsFromEnd;

        unsigned indexOnShortestPath;

        double distanceFromStartPoint;
        double distanceFromEndPoint;
    };
}


#endif // POINTONSHORTESTPATH_H
