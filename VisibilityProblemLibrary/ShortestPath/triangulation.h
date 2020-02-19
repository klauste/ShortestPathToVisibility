#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <vector>
#include <iostream>
#include "ShortestPath/faceinfo.h"
#include <CGAL/intersections.h>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

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
    class Triangulation
    {
    public:
        Triangulation() {}
        Triangulation(const Polygon &p) : polygon(p) {}

        /**
         * @brief getTriangulation returns CGAL's triangulation of the polygon
         * @return
         */
        const CDT& getTriangulation();
    private:
        /**
         * @brief polygon the polygon to be triangulated
         */
        Polygon polygon;

        /**
         * @brief cdt CGAL's triangulation of the polygon
         */
        CDT cdt;

        /**
         * @brief markDomains helper function for CGAL to mark triangles which
         * are in the interior of the polygon
         * @param ct
         * @param start
         * @param index
         * @param border
         */
        void markDomains(CDT& ct,
                     CDT::Face_handle start,
                     int index,
                     std::list<CDT::Edge>& border );

        /**
         * @brief markDomains helper function for CGAL to mark triangles which
         * are in the interior of the polygon
         * @param cdt
         */
        void markDomains(CDT& cdt);
    };
}
#endif // TRIANGULATION_H
