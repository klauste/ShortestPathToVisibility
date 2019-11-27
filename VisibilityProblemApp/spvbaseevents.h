#ifndef SPVBASEEVENTS_H
#define SPVBASEEVENTS_H


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
    class BaseEvents {
    protected:
        std::vector<ShortestPathEntry *> shortestPath;
        SPV::EventMap eventMap;
        GeometryUtil gU;

        // Handles the intersection on the opposite side of the vertex causing the boundary event
        PolygonTriangle *handleIntersection(PolygonTriangle *startTriangle, PolygonTriangle *endTriangle, EventOnShortestPath *region, bool goLeft, bool isEndpoint, bool intersectionBelongsToStart, int eventType = 2);
        PolygonTriangle *findTriangleWithIntersectionEvent(PolygonTriangle *startTriangle, Point intersection, bool goLeft);
        std::pair<PolygonTriangle*, Segment> findTriangleWithIntersection(PolygonTriangle *startTriangle, Point intersection, bool goLeft);
        PolygonTriangle *findTriangleWithFirstPoint(PolygonTriangle *startTriangle, Point firstPoint, bool goLeft);

        PolygonTriangle *startTriangle;
        PolygonTriangle *endTriangle;
        PolygonTriangle *nextTriangleStart;
        PolygonTriangle *nextTriangleEnd;

        // Gets the intersection on the opposite side
        Point getIntersectionOnOppositeSide(EventIntersection* ei, unsigned pivotPointIndex);
        PolygonTriangle* findStartTriangleForCurrentEvent(PolygonTriangle* currentTriangle, EventIntersection* ei, unsigned pivotPointIndex, bool goLeft, bool fromStart);
        PolygonTriangle* findEndTriangleForCurrentEvent(PolygonTriangle* currentTriangle, EventIntersection* ei, unsigned pivotPointIndex, bool goLeft);

        // This function gets the first point of the currently swept polygon edge
        Point getPolygonEdgeStartPoint(EventIntersection *startIntersection, bool fromStart, unsigned pivotPointIndex);
        EventOnShortestPath* getSPEvent(unsigned pivotPointIndex, Point intersection, bool fromStart);
        Point getClosestDefiningPoint(EventIntersection *startIntersection, bool fromStart, unsigned pivotPointIndex);
        bool isPointOnShortestPathBeforePiovt(Point pointToCheck, unsigned pivotPointIndex, bool fromStart) {
            if (fromStart) {
                for (int i = pivotPointIndex - 1; i >= 0; i--) {
                    if (shortestPath.at(i)->getPoint() == pointToCheck) {
                        return true;
                    }
                }
            } else {
                for (unsigned i = pivotPointIndex + 1; i < shortestPath.size(); i++) {
                    if (shortestPath.at(i)->getPoint() == pointToCheck) {
                        return true;
                    }
                }
            }
            return false;
        }

        EventIntersection *getNextEvent(
            EventIntersection* currentIntersection,
            bool goLeft,
            unsigned pivotPointIndex,
            bool fromStart,
            bool setStartTriangleAndHandled = true
        );
        bool shouldTraverseIntersectionsFromStart(Point startEdge, EventIntersection *ei);

        /**
         * This function assumes that the current line of sight is defined by startPoint and pivotPoint and is rotated
         * towards endPoint. Then the result indicates if the path to the line of sight starts on the polygon edge at
         * startPoint or if it moves away from the edge
         *
         * @brief isPathToLoSOnPolygonEdge
         * @param startPoint
         * @param pivotPoint
         * @param endPoint
         * @param lastPointOnLoS
         * @return
         */
        bool isPathToLoSOnPolygonEdge(Point startPoint, Point pivotPoint, Point endPoint, Point lastPointOnLoS);
    };
}

#endif // SPVBASEEVENTS_H
