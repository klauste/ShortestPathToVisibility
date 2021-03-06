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
    /**
     * @brief The ShortestPathCalculator class calculates the shortest path for a given polygon
     * and a start and end point
     */
    class ShortestPathCalculator
    {
    public:
        /**
         * @brief ShortestPathCalculator constructor sets the triangulation for the given
         * polygon
         * @param p
         * @param s
         * @param e
         */
        ShortestPathCalculator(const Polygon &p, Point s, Point e);

        /**
         * @brief getShortestPath calculates and returns the shortest path
         * @return
         */
        const std::vector<std::shared_ptr<PointOnShortestPath>> getShortestPath();

        /**
         * @brief directPathBetweenFinalPointsExists returns the directPathBetweenFinalPoints flag
         * @return
         */
        bool directPathBetweenFinalPointsExists();

    protected:
        /**
         * @brief calculateShortestPath Cclculates the shortest path between startPoint and endPoint
         * in the given polygon. The function implements the algorithm
         * described by Wolgang Mulzer in
         * https://page.mi.fu-berlin.de/mulzer/notes/alggeo/polySP.pdf
         *
         * @return the shortest path
         */
        void calculateShortestPath();

        /**
         * @brief facesFromStartToEnd stores the triangulation faces through which the shortest
         * path has to go. The first face contains the start point,
         * the last face contains the end point.
         */
        std::vector<std::shared_ptr<FaceOnShortestPath>> facesFromStartToEnd;

        /**
         * @brief shortestPath stores the shortest path as a vector of PointOnShortestPath instances
         */
        std::vector<std::shared_ptr<PointOnShortestPath>> shortestPath;

        /**
         * @brief startPoint the start point for the shortest path
         */
        Point startPoint;

        /**
         * @brief endPoint the end point for the shortest path
         */
        Point endPoint;

        /**
         * @brief gU instance of the utility class
         */
        GeometryUtil gU;

        /**
         * @brief triangulation the triangulation of the polygon
         */
        CDT triangulation;

    private:
        /**
         * @brief polygon stores the polygon for the calculations
         */
        Polygon polygon;

        /**
         * @brief triangulationCalculator instance of the Triangulation helper class
         */
        Triangulation triangulationCalculator;

        /**
         * @brief directPathBetweenFinalPoints indicates if the start and end point are visible
         * to each other.
         */
        bool directPathBetweenFinalPoints;

        /**
         * @brief checkDirectPath checks if there is a direct path between start and end point
         * and sets the flag accordingly
         */
        void checkDirectPath();

        /**
         * @brief setFacesFromStartToEndPoint sets the triangulation faces from the start point to the
         * end point
         */
        void setFacesFromStartToEndPoint();

        /**
         * @brief recursivelyfindEndPoint recursively goes through the triangulation
         * and searches for the endPoint. It adds the faces to facesFromStartToEnd as
         * it does so.
         * @param currentFaceHandle
         * @return
         */
        bool recursivelyfindEndPoint(TDS::Face_handle &currentFaceHandle);

        /**
         * @brief funnelLeftPath contains the left part of the funnel
         */
        std::vector<std::shared_ptr<PointOnShortestPath>> funnelLeftPath;

        /**
         * @brief funnelRightPath containt the right part of the funnel
         */
        std::vector<std::shared_ptr<PointOnShortestPath>> funnelRightPath;

        /**
         * @brief handleNextPoint handles the next point in a triangle on the path from the start to the end
         * point.
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
         * @brief setDistances set the distance from the start and end point to all points on
         * the shortest path.
         */
        void setDistances();
    };
}
#endif // SHORTESTPATHCALCULATOR_H
