#ifndef SPVBOUNDARYEVENTS_H
#define SPVBOUNDARYEVENTS_H


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
    class BoundaryEvents: public BaseEvents {
    public:
        BoundaryEvents() {}
        BoundaryEvents(std::vector<ShortestPathEntry *> sP, EventMap &eM, std::vector<PointOnShortestPath *> spt, std::vector<PointOnShortestPath *> sptFromEnd) {
            shortestPath = sP;
            eventMap = eM;
            shortestPathTree = spt;
            shortestPathTreeFromEnd = sptFromEnd;
            gU = GeometryUtil();
        }
        void calculateBoundaryEvents();

    private:
        void calculateEventsBetween2PathEvents (
                PolygonTriangle *startTriangle,
                PolygonTriangle *endTriangle,
                PolygonTriangle *nextStartTriangle,
                PolygonTriangle *nextEndTriangle,
                Point firstIntersectionStart,
                Point firstIntersectionEnd,
                Point nextIntersectionStart,
                Point nextIntersectionEnd,
                Point startPointOnShortestPath,
                Point pivotPointOnShortestPath,
                Point nextPointOnShortestPath,
                bool vertexIsStart,
                CDT::Face_handle currentFace,
                bool goLeft
        );
        Point getSegmentEndPointForVertex(PolygonTriangle* currentTriangle, unsigned currentIndex);
        std::vector<PointOnShortestPath *> shortestPathTree;
        std::vector<PointOnShortestPath *> shortestPathTreeFromEnd;
        bool isPointSPTParent(bool fromStart, Point currentPoint, Point parentPoint, CDT::Vertex_handle currentVertex);
    };
}


#endif // SPVBOUNDARYEVENTS_H
