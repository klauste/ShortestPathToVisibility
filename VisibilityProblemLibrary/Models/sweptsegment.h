#ifndef SWEPTSEGMENT_H
#define SWEPTSEGMENT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

namespace SPV {
    /**
     * @brief The SweptSegment class stores information about a segment on the polygon's border which
     * is swept by a line of sight. It's a helper data structure used by instances of PointOnShortestPath
     */
    class SweptSegment {
    public:
        SweptSegment(Point l, bool lP, Point r, bool rP) :
            leftPoint(l),
            leftPointPolygonVertex(lP),
            rightPoint(r),
            rightPointPolygonVertex(rP) {}

        /**
         * @brief getClone returns a clone of the instance
         * @return
         */
        std::shared_ptr<SPV::SweptSegment> getClone();

        /**
         * @brief getLeftPoint returns the left point of the segment (as seen from the pivot point)
         * @return
         */
        Point getLeftPoint();

        /**
         * @brief leftPointIsPolygonVertex returns the value of the flag indicating if the
         * left point is a vertex
         * @return
         */
        bool leftPointIsPolygonVertex();

        /**
         * @brief getRightPoint returns the right point of the segment (as seen from the pivot point)
         * @return
         */
        Point getRightPoint();

        /**
         * @brief rightPointIsPolygonVertex returns the value of the flag indicating if the right point
         * is a vertex
         * @return
         */
        bool rightPointIsPolygonVertex();

    private:
        /**
         * @brief leftPoint the left point of the segment
         */
        Point leftPoint;

        /**
         * @brief leftPointPolygonVertex indicates if the left point is a vertex
         */
        bool leftPointPolygonVertex;

        /**
         * @brief rightPoint the right point of the segment
         */
        Point rightPoint;

        /**
         * @brief rightPointPolygonVertex indicates if the right point is a vertex
         */
        bool rightPointPolygonVertex;
    };
}

#endif // SWEPTSEGMENT_H
