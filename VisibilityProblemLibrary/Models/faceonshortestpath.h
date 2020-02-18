#ifndef FACEONSHORTESTPATH_H
#define FACEONSHORTESTPATH_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include "ShortestPath/faceinfo.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel        K;
typedef CGAL::Triangulation_vertex_base_2<K>                       Vb;
typedef CGAL::Triangulation_face_base_with_info_2<SPV::FaceInfo,K> Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K,Fbb>         Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>                TDS;

namespace SPV {
    /**
     * @brief The FaceOnShortestPath struct is used for the calculation of the shortest path
     * from the start to the end point. It stores the current faceHandel, representing
     * a triangle from the polygon's triangulation and information where the
     * next triangle on the path from start to end point lies.
     */
    struct FaceOnShortestPath
    {
        FaceOnShortestPath(TDS::Face_handle f) : faceHandle(f){}

        /**
         * @brief nextFaceIndex stores the index indicating which edge of the current triangle is adjacent
         * to the next triangle on the path from start to end point
         */
        int nextFaceIndex;

        /**
         * @brief faceHandle represents the current triangle on the path from start to end point. For
         * more information, read the CGAL documentation on triangulation.
         */
        TDS::Face_handle faceHandle;
    };
}

#endif // FACEONSHORTESTPATH_H
