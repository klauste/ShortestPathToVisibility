#ifndef SPVEVENTMAP_H
#define SPVEVENTMAP_H

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
    class PolygonTriangle {
    public:
        PolygonTriangle(CDT::Face_handle fh, bool isStart) : currentFace(fh), isStartTriangle(isStart) {}
        void setLeftTriangle(PolygonTriangle *pt);
        void setRightTriangle(PolygonTriangle *pt);
        PolygonTriangle *getLeftTriangle();
        PolygonTriangle *getRightTriangle();
        void addRightToLeftVertexIndex(int i);
        bool getIsStartTriangle();
        std::vector<int> getRightToLeftIndices();
        CDT::Face_handle getFace();
        void addIndexAtStart(int index);
        Point getLeftPoint(Point p);
        Point getRightPoint(Point p);
    private:
        CDT::Face_handle currentFace;
        PolygonTriangle *leftTriangle;
        PolygonTriangle *rightTriangle;
        std::vector<int> rightToLeftVertexIndex;
        bool isStartTriangle;
    };

    class EventMap {
    public:
        EventMap() {};
        EventMap(Polygon &p, CDT &cdt);
        PolygonTriangle *getStartTriangle() {
            return startPointTriangle;
        }
        PolygonTriangle *getEndPointTriangle() {
            return endPointTriangle;
        }
    private:
        void setPolygonTriangles(Polygon &p, CDT &cdt);
        PolygonTriangle *startPointTriangle;
        PolygonTriangle *endPointTriangle;
        CDT::Face_handle findNextFace(CDT::Face_handle fh, int lastPointIndex, Point nextPoint);
        void handleLastPoint(Point p);
        int addPointsToTriangle(Polygon &p, unsigned index, PolygonTriangle *currentTriangle);
    };
}
#endif // SPVEVENTMAP_H
