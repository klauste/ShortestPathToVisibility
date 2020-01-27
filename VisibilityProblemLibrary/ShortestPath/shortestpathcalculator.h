#ifndef SHORTESTPATHCALCULATOR_H
#define SHORTESTPATHCALCULATOR_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/squared_distance_2.h>
#include <math.h>
#include <vector>
#include <iostream>
#include "Models/faceonshortestpath.h"
#include "Models/pointwithtriangulationinfo.h"
#include "Utils/geometryutil.h"
#include "ShortestPath/faceinfo.h"
#include "ShortestPath/triangulation.h"
#include "Models/pointonshortestpath.h"

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

namespace SPV {
    class ShortestPathCalculator
    {
    public:
        ShortestPathCalculator(const Polygon &p, Point s, Point e) {
            triangulationCalculator = Triangulation(p);
            polygon = p;
            triangulation = triangulationCalculator.getTriangulation();
            startPoint = s;
            endPoint = e;
        }

        const std::vector<std::shared_ptr<PointOnShortestPath>> getShortestPath()
        {
            calculateShortestPath();
            return shortestPath;
        }

        CDT::Face_handle getStartFace()
        {
            return facesFromStartToEnd.at(0)->faceHandle;
        }

        CDT::Face_handle getEndFace()
        {
            unsigned lastIndex = facesFromStartToEnd.size() - 1;

            return facesFromStartToEnd.at(lastIndex)->faceHandle;
        }
    protected:
        /**
         * Calculates the shortest path between startPoint and endPoint
         * in the given polygon. The function implements the algorithm
         * described by Wolgang Mulzer in
         * https://page.mi.fu-berlin.de/mulzer/notes/alggeo/polySP.pdf
         *
         * @brief calculateShortestPath
         * @return the shortest path
         */
        void calculateShortestPath();

        /**
         * Stores the triangulation faces through which the shortest
         * path has to go. The first face contains the start point,
         * the second face contains the end point.
         *
         * @brief facesFromStartToEnd
         */
        std::vector<std::shared_ptr<FaceOnShortestPath>> facesFromStartToEnd;

        /**
         * @brief shortestPath
         */
        std::vector<std::shared_ptr<PointOnShortestPath>> shortestPath;

        Point startPoint;
        Point endPoint;
        GeometryUtil gU;
    private:
        Polygon polygon;
        CDT triangulation;
        Triangulation triangulationCalculator;

        /**
         * This function sets facesFromStartToEnd
         *
         * @brief setFacesFromStartToEndPoint
         */
        void setFacesFromStartToEndPoint();

        /**
         * This function recursively goes through the triangulation
         * and searches for the endPoint. It adds the faces to
         * facesFromStartToEnd as it does so.
         *
         * @brief recursivelyfindEndPoint
         * @param currentFaceHandle
         * @return
         */
        bool recursivelyfindEndPoint(TDS::Face_handle &currentFaceHandle);

        /**
         * Contains the left part of the funnel
         * @brief funnelLeftPath
         */
        std::vector<std::shared_ptr<PointOnShortestPath>> funnelLeftPath;

        /**
         * Contains the right part of the funnel
         * @brief funnelRightPath
         */
        std::vector<std::shared_ptr<PointOnShortestPath>> funnelRightPath;

        /**
         * Handle the next point in a triangle on the path from the start to the end
         * point.
         *
         * @brief handleNextPoint
         * @param backwardPath
         * @param forwardPath
         * @param nextPoint
         * @param isBackwardPathOnTheRight
         */
        void handleNextPoint(
                std::vector<std::shared_ptr<PointOnShortestPath>> &backwardPath,
                std::vector<std::shared_ptr<PointOnShortestPath>> &forwardPath,
                std::shared_ptr<PointOnShortestPath> nextPoint,
                bool isBackwardPathOnTheRight
        );

        /**
         * Set the distance from the start and end point to this point on
         * the shortest path.
         * @brief setDistances
         */
        void setDistances();
    };
}
#endif // SHORTESTPATHCALCULATOR_H
