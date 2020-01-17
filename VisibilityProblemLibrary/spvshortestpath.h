#ifndef SPVSHORTESTPATH_H
#define SPVSHORTESTPATH_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <vector>
#include <iostream>
#include "spvfaceinfo.h"
#include <CGAL/intersections.h>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include "Utils/geometryutil.h"
#include "ShortestPath/shortestpathcalculator.h"
#include "ShortestPath/shortestpathtreecalculator.h"
#include "Events/pathandboundaryeventcalculator.h"

typedef K::Ray_2 Ray;
typedef K::Intersect_2 Intersect_2;
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

struct FaceOnPath
{
    FaceOnPath(TDS::Face_handle currentFace) : currentFace(currentFace){}
    int nextFaceIndex;
    TDS::Face_handle currentFace;
};

namespace SPV {
    class ShortestPath
    {
    public:
        ShortestPath() {}
        void initialize(const Polygon &polygon);
        const CDT& getTriangulation();
        std::vector<PointOnShortestPath* > calculateShortestPath();
        void setPoint(int index, double x, double y);
        EventSegment *getFirstEvent()
        {
            return firstSegment;
        }
    private:
        EventSegment *firstSegment;
        Point sPoint;
        Point ePoint;
        CDT cdt;
        void calculateTriangulation();
        void markDomains(CDT& ct,
                     CDT::Face_handle start,
                     int index,
                     std::list<CDT::Edge>& border );
        void markDomains(CDT& cdt);
        bool setFacesFromStartToEndPoint();
        bool recursivelyfindEndPoint(TDS::Face_handle &currentFaceHandle);
        Polygon polygon;
    };
}
#endif // SPVSHORTESTPATH_H
