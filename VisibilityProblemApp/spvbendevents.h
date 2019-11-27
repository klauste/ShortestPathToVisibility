#ifndef SPVBENDEVENTS_H
#define SPVBENDEVENTS_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <vector>
#include <iostream>
#include "spvshortestpathtree.h"
#include "spvfaceinfo.h"
#include "spventryonshortestpath.h"
#include "spveventintersection.h"
#include "spveventmap.h"
#include "spvgeometryutil.h"
#include "spvboundaryevents.h"
#include "spvbaseevents.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel       K;
typedef CGAL::Triangulation_vertex_base_2<K>                      Vb;
typedef CGAL::Triangulation_face_base_with_info_2<SPV::FaceInfo,K>    Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K,Fbb>        Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_predicates_tag                                Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>  CDT;
typedef K::Segment_2 Segment;
typedef K::Point_2 Point;
typedef K::Triangle_2 Triangle;
typedef CGAL::Polygon_2<K> Polygon;
typedef K::Line_2 Line;
typedef CDT::Face_circulator Face_circulator;

namespace SPV {
    class BendEvents: public BaseEvents {
    public:
        BendEvents() {}
        BendEvents(std::vector<ShortestPathEntry *> sP, EventMap &eM) {
            shortestPath = sP;
            eventMap = eM;
        }
        void calculateBendEvents();

    private:
        void calculateEventsBetween2PathEvents (
                EventIntersection *currentIntersection,
                Point nextIntersectionStart,
                unsigned pivotPointIndex,
                bool vertexIsStart,
                bool goLeft
        );
        EventIntersection *calculateEventsBetween2Events (
                EventIntersection *firstIntersection,
                EventIntersection *secondIntersection,
                unsigned pivotPointIndex,
                bool goLeft,
                bool fromStart
        );

        bool doesNextLoSRotateInTheSameDirection(unsigned pivotPointIndex, bool fromStart, bool goLeft);
        /**
         * @brief getNextDegenerateBendEvent
         * This function checks if there is a degenerate bend event on the current edge defined by the
         * two intersection events. If there isn't, false is returned. If there are degenerate events, the
         * degenerate event closer to ei1 is returned.
         *
         * @param pivotPointIndex
         * @param ei1
         * @param ei2
         * @param polygonEdgeStart
         * @param fromStart
         * @return
         */
        boost::variant<Point, bool> getNextDegenerateBendEvent(
                unsigned pivotPointIndex,
                EventIntersection *ei1,
                EventIntersection *ei2,
                Point polygonEdgeStart,
                bool fromStart
        );
        void handlePathOrBoundaryEvents(
                unsigned pivotPointIndex,
                EventIntersection *ei1,
                EventIntersection *ei2,
                bool goLeft,
                bool fromStart,
                bool onPolygonEdge
        );
        EventIntersection* handleAddingPointBendEvents(
                unsigned pivotPointIndex,
                CDT::Face_handle pivotPointFace,
                EventIntersection *ei1,
                Point nextIntersection,
                bool goLeft,
                bool fromStart
        );
        EventIntersection* handleLosingPointBendEvents(
                unsigned pivotPointIndex,
                CDT::Face_handle pivotPointFace,
                EventIntersection *ei1,
                Point nextIntersection,
                bool goLeft,
                bool fromStart
        );
        EventIntersection* handleCircleIntersection(
                Point circleIntersection,
                unsigned pivotPointIndex,
                EventIntersection *ei1,
                bool goLeft,
                bool belongsToStart
        );

        // This function checks if the shortest path to the line of sight between start and end intersection starts on the polygon edge. If that's the case,
        // the flag is set in the start intersection
        void setStartOnPolygonEdge(EventIntersection *startIntersection, EventIntersection *endIntersection, unsigned pivotPointIndex, bool fromStart, bool goLeft);

        // This function creates an event intersection between for the given intersection point. As a side effect it moves startTriangle
        // to the triangle with a segment containing the intersectionPoint
        EventIntersection *createEventIntersection(Point intersectionPoint, Point pivotPoint, bool goLeft, bool fromStart);
    };
}


#endif // SPVBENDEVENTS_H
