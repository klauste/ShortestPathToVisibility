#ifndef LINEOFSIGHT_H
#define LINEOFSIGHT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

/**
 * @brief The EventType enum indicates the type of event a line of sight represents
 */
enum EventType { PATH, BOUNDARY, BEND };

namespace SPV {
    /**
     * @brief The LineOfSight class stores information about lines of sight at path, boundary or bend events.
     */
    class LineOfSight {
    public:
        LineOfSight(Point pS, bool pSV, Point pE, bool pEV) :
            pointOnStartSide(pS),
            pointOnStartSideIsVertex(pSV),
            pointOnEndSide(pE),
            pointOnEndSideIsVertex(pEV) {}

        void setEventType(EventType t);

        EventType getEventType();

        Point getPointOnStartSide();

        Point getPointOnEndSide();

        bool isStartPointVertex();

        bool isEndPointVertex();
    private:
        /**
         * @brief type the event type of this line of sight
         */
        EventType type;

        /**
         * @brief pointOnStartSide the point on the polygon's boundary closest to the start point
         */
        Point pointOnStartSide;

        /**
         * @brief pointOnStartSideIsVertex indicates if the point on the start side is a polygon vertex
         */
        bool pointOnStartSideIsVertex;

        /**
         * @brief pointOnEndSide the point on the polygon's boundary closest to the end point
         */
        Point pointOnEndSide;

        /**
         * @brief pointOnEndSideIsVertex indicates if the point on the start side is a polygon vertex
         */
        bool pointOnEndSideIsVertex;
    };
}

#endif // LINEOFSIGHT_H
