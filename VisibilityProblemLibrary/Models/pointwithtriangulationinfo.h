#ifndef POINTWITHTRIANGULATIONINFO_H
#define POINTWITHTRIANGULATIONINFO_H
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include "spvfaceinfo.h"
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel       K;
typedef CGAL::Triangulation_vertex_base_2<K>                      Vb;
typedef CGAL::Triangulation_face_base_with_info_2<SPV::FaceInfo,K>    Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K,Fbb>        Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_predicates_tag                                Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>  CDT;
typedef K::Point_2 Point;

namespace SPV {
    /**
     * Contains the details of a point and - if the point is not the start or
     * end point of the shortest path - the triangulation face it belongs to.
     *
     * @brief The ShortestPathEntry class
     */
    class PointWithTriangulationInfo
    {
    public:
        /**
         * Constructor for the start or end point. A start or end point lies inside a
         * triangulated face, but is not one of its vertices. Therefore such a point
         * does not contain information about a triangulation face
         *
         * @brief PointWithTriangulationInfo
         * @param p
         * @param t
         */
        PointWithTriangulationInfo(Point p) : point(p) {}

        /**
         * Constructor for any points between the start or end point. A mid point is
         * the vertex of a triangulation face and thus contains the handle to that
         * face.
         *
         * @brief PointWithTriangulationInfo
         * @param fh
         * @param i
         */
        PointWithTriangulationInfo(CDT::Face_handle fh, int i) : currentFace(fh), pointIndex(i), onTriangle(true) {}

        Point getPoint();
        CDT::Face_handle getFaceHandle();
        CDT::Vertex_handle getVertexHandle();

    private:
        CDT::Face_handle currentFace;
        int pointIndex;
        Point point;
        bool onTriangle = false;
    };
}

#endif // POINTWITHTRIANGULATIONINFO_H
