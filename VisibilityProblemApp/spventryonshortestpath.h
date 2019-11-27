#ifndef SPVENTRYONSHORTESTPATH_H
#define SPVENTRYONSHORTESTPATH_H

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
     * Defines a point in the shortest path or shortest path tree. The point is either defined as
     * a normal CGAL point (if it is the start or end point), or as a vertex index on the triangulation
     * face to which this entry belongs.
     *
     * @brief The ShortestPathEntry class
     */
    class ShortestPathEntry
    {
    public:
        ShortestPathEntry(Point p, int t) : entryPoint(p), type(t) {}
        ShortestPathEntry(CDT::Face_handle fh, int i) : currentFace(fh), pointIndex(i), type(1) {}
        Point getPoint();
        CDT::Face_handle getFaceHandle();
        bool isStartPoint();
        bool isEndPoint();
        bool isMidPoint();
        CDT::Vertex_handle getVertexHandle();

    private:
        CDT::Face_handle currentFace;
        int pointIndex;
        Point entryPoint;
        int type;
    };
}

#endif // SPVENTRYONSHORTESTPATH_H
