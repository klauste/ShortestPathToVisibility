#ifndef FACEONSHORTESTPATH_H
#define FACEONSHORTESTPATH_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include "spvfaceinfo.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel        K;
typedef CGAL::Triangulation_vertex_base_2<K>                       Vb;
typedef CGAL::Triangulation_face_base_with_info_2<SPV::FaceInfo,K> Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K,Fbb>         Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>                TDS;

namespace SPV {
    struct FaceOnShortestPath
    {
        FaceOnShortestPath(TDS::Face_handle f) : faceHandle(f){}
        int nextFaceIndex;
        TDS::Face_handle faceHandle;
    };
}

#endif // FACEONSHORTESTPATH_H
