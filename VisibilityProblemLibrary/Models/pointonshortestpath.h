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
     * @brief The PointOnShortestPath class contains information about a point on the shortest path from
     * the start point to the end point
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

        /**
         * @brief getPoint returns the instance's CGAL point
         * @return
         */
        Point getPoint();

        /**
         * @brief getSegmentsFromStart returns the segments on the polygon edge which a line of sight
         * closer to the end point sweeps if rotated around this point as pivot point
         * @return
         */
        std::vector<std::shared_ptr<SweptSegment>> getSegmentsFromStart();

        /**
         * @brief getSegmentsFromEnd returns the segments on the polygon edge which a line of sight
         * closer to the start point sweeps if rotated around this point as pivot point
         * @return
         */
        std::vector<std::shared_ptr<SweptSegment>> getSegmentsFromEnd();

        /**
         * @brief addSegmentFromStart adds a swept segment
         * @param s
         */
        void addSegmentFromStart(std::shared_ptr<SweptSegment> s);

        /**
         * @brief addSegmentFromEnd adds a swept segment
         * @param s
         */
        void addSegmentFromEnd(std::shared_ptr<SweptSegment> s);

        /**
         * @brief getIndexOnShortestPath return the index of this point on the shortest path
         */
        unsigned getIndexOnShortestPath();

        /**
         * @brief setIndexOnShortestPath sets the index of this point on the shortest path
         * @param i
         */
        void setIndexOnShortestPath(unsigned i);

        /**
         * @brief getDistanceFromStartPoint returns the distance from the start point to this point
         * @return
         */
        double getDistanceFromStartPoint();

        /**
         * @brief getDistanceFromEndPoint returns the distance from the end point to this point
         * @return
         */
        double getDistanceFromEndPoint();

        /**
         * @brief setDistanceFromStartPoint sets the distance from the start point to this point
         * @param d
         */
        void setDistanceFromStartPoint(double d);

        /**
         * @brief setDistanceFromEndPoint sets the distance form the end point to this point
         * @param d
         */
        void setDistanceFromEndPoint(double d);

    private:
        /**
         * @brief point contains the coordinates of this point
         */
        Point point;

        /**
         * @brief segmentsFromStart the segments swept by the line of sight through this point
         * found in the start point's shortest path map
         */
        std::vector<std::shared_ptr<SweptSegment>> segmentsFromStart;

        /**
         * @brief segmentsFromEnd the segments swept by the line of sight through this point
         * found in the end point's shortest path map
         */
        std::vector<std::shared_ptr<SweptSegment>> segmentsFromEnd;

        /**
         * @brief indexOnShortestPath this point'ss index on the shortest path
         */
        unsigned indexOnShortestPath;

        /**
         * @brief distanceFromStartPoint the distance from the start point to this point
         */
        double distanceFromStartPoint;

        /**
         * @brief distanceFromEndPoint the distance from the end point to this point
         */
        double distanceFromEndPoint;
    };
}

#endif // POINTONSHORTESTPATH_H
