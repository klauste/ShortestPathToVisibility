#ifndef SHORTESTPATHTREECALCULATOR_H
#define SHORTESTPATHTREECALCULATOR_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <vector>
#include <iostream>
#include "Models/faceonshortestpath.h"
#include "Models/pointonshortestpath.h"
#include "Models/pointonshortestpathtree.h"
#include "Utils/geometryutil.h"
#include "ShortestPath/faceinfo.h"
#include "ShortestPath/shortestpathcalculator.h"

namespace SPV {
    class ShortestPathTreeCalculator : public ShortestPathCalculator
    {
    public:
        ShortestPathTreeCalculator (const Polygon &p, Point s, Point e) :
            ShortestPathCalculator (p, s, e) {}

        /**
         * @brief getShortestPath overwrites the parent's function. Calculates the
         * shortest path and sets the segments which are swept by lines of sight when rotating
         * around one point on the shortest path as pivot point.
         * @return
         */
        const std::vector<std::shared_ptr<PointOnShortestPath>> getShortestPath();

    protected:
        /**
         * @brief calculateShortestPath calculates the shortest path and sets the segments on the
         * polygon boundary which are swept by lines of sight when rotating around one point on the
         * shortest path as pivot point. Overwrites the parent function.
         */
        void calculateShortestPath();

    private:
        /**
         * @brief The predecessorInfo struct is a helper data structure containing information about the
         * predecessor of a point on the funnel
         */
        struct predecessorInfo {
            predecessorInfo() : isApex(false),
                                isLastPointOnFunnel(false),
                                onLeftFunnel(false),
                                onRightFunnel(false),
                                indexOnFunnel(-1) {}
            bool isApex;
            bool isLastPointOnFunnel;
            bool onLeftFunnel;
            bool onRightFunnel;
            int indexOnFunnel;
        };

        /**
         * @brief The triangulationIndexInformation struct is a helper data structure containing information
         * which point in a triangulation face is the next point to be considered during the calculation
         * of the shortest path tree
         */
        struct triangulationIndexInformation {
            Point nextPoint;
            unsigned leftPointIndex;
            unsigned rightPointIndex;
            unsigned nextPointIndex;
        };

        /**
         * @brief setSweptSegmentsInShortestPath calculates the shortest path tree and map as described
         * in https://graphics.stanford.edu/courses/cs268-09-winter/notes/handout7.pdf.
         * During the calculation, it sets all the edges swept by lines of sight through each of the
         * points in the shortest path. The recursive build of the shortest tree always goes left first.
         * Therfore the swept edges will be added to each point on the shortest path in order from left to
         * right (as seen from the pivot point).
         *
         * @param firstFace
         * @return
         */
        void setSweptSegmentsInShortestPath(CDT::Face_handle firstFace);

        /**
         * @brief splitFunnel splits a funnel as described in
         * https://graphics.stanford.edu/courses/cs268-09-winter/notes/handout7.pdf
         *
         * @param currentFace
         * @param neighborIndex
         * @param apex
         * @param leftFunnel
         * @param rightFunnel
         */
        void splitFunnel(
                CDT::Face_handle currentFace,
                int neighborIndex,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel
        );

        /**
         * @brief splitFunnelAtApex helper function to split a funnel at the apex
         * @param nextFace
         * @param apex
         * @param leftFunnel
         * @param rightFunnel
         * @param indexInfo
         */
        void splitFunnelAtApex(
                CDT::Face_handle nextFace,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
                std::shared_ptr<triangulationIndexInformation> indexInfo
        );

        /**
         * @brief splitFunnelAtLastPoint helper function to split a funnel at the last point
         * of a funnel
         * @param nextFace
         * @param apex
         * @param leftFunnel
         * @param rightFunnel
         * @param nextPointOnLeftFunnel
         * @param indexInfo
         */
        void splitFunnelAtLastPoint(
                CDT::Face_handle nextFace,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
                bool nextPointOnLeftFunnel,
                std::shared_ptr<triangulationIndexInformation> indexInfo
        );

        /**
         * @brief splitFunnelAtMidPoint helper function to split a funnel at a mid point
         * @param nextFace
         * @param apex
         * @param leftFunnel
         * @param rightFunnel
         * @param nextPointOnLeftFunnel
         * @param indexInfo
         * @param newApexIndex
         */
        void splitFunnelAtMidPoint(
                CDT::Face_handle nextFace,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
                bool nextPointOnLeftFunnel,
                std::shared_ptr<triangulationIndexInformation> indexInfo,
                unsigned newApexIndex
        );

        /**
         * @brief handleTriangleBeyondLastEdge is a function to handle an edge case which is not described in
         * https://graphics.stanford.edu/courses/cs268-09-winter/notes/handout7.pdf. The edge case occurs if
         * the next point to be handled does not split the funnel, but is located such, that it has to be
         * added to either the left or the right funnel
         *
         * @param nextFace
         * @param apex
         * @param firstPointOnTree
         * @param lastPointOnLeftFunnel
         */
        void handleTriangleBeyondLastEdge(
                CDT::Face_handle nextFace,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::shared_ptr<PointOnShortestPathTree> firstPointOnTree,
                bool lastPointOnLeftFunnel
        );

        /**
         * @brief findPredecessor finds the predecessor of point p in the funnel defined by the
         * apex and the left and right funnel
         * @param p
         * @param apex
         * @param leftFunnel
         * @param rightFunnel
         * @return
         */
        std::shared_ptr<predecessorInfo> findPredecessor(
                Point p,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel
        );

        /**
         * @brief rootPoint the point for which to calculate the shortest paht tree
         */
        Point rootPoint;

        /**
         * @brief rootAtEndPoint whether the root is the end point or the start point
         */
        bool rootAtEndPoint;

        /**
         * @brief shortestPathTree the shortest path tree from the root point
         */
        std::vector<std::shared_ptr<PointOnShortestPathTree>> shortestPathTree;

        /**
         * @brief currentPointOnShortestPathIndex the index of the current point on the shortest
         * path tree for which swept segments are set
         */
        int currentPointOnShortestPathIndex;

        /**
         * @brief allPointsOnShortestPathHandled checks if all points on the shortest path have been handled
         * @return
         */
        bool allPointsOnShortestPathHandled();

        /**
         * @brief getNextPointOnShortestPath returns the next point on the shortest path for which
         * swept segments need to be calculated
         * @return
         */
        Point getNextPointOnShortestPath();

        /**
         * @brief isPointOnShortestPath checks if pointToCheck is a point on the shortest paht
         * @param pointToCheck
         * @return
         */
        bool isPointOnShortestPath(std::shared_ptr<PointOnShortestPathTree> pointToCheck);

        /**
         * @brief addPointToShortestPathTree adds p to the shortest path tree
         * @param p
         */
        void addPointToShortestPathTree(std::shared_ptr<PointOnShortestPathTree> p);

        /**
         * @brief getTriangulationIndexInformation returns information which point on a triangulation
         * face is the next point to be handled in the shortest path tree calculations
         * @param leftPoint
         * @param rightPoint
         * @param faceHandle
         * @return
         */
        std::shared_ptr<triangulationIndexInformation> getTriangulationIndexInformation(
                Point leftPoint,
                Point rightPoint,
                CDT::Face_handle faceHandle
        );

        /**
         * @brief calculateSweptSegments calculates the swept segments for a given face and tunnel
         * @param currentFace
         * @param apex
         * @param leftFunnel
         * @param rightFunnel
         * @param tI
         */
        void calculateSweptSegments(
           CDT::Face_handle currentFace,
           std::shared_ptr<PointOnShortestPathTree> apex,
           std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
           std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
           std::shared_ptr<triangulationIndexInformation> tI
        );

        /**
         * @brief calculateAndAddSegment helper function to calculate and add one swept segment
         * @param apex
         * @param leftFunnelPoint
         * @param rightFunnelPoint
         * @param leftTriangleEdgePoint
         * @param rightTriangleEdgePoint
         */
        void calculateAndAddSegment(
            std::shared_ptr<PointOnShortestPathTree> apex,
            std::shared_ptr<PointOnShortestPathTree> leftFunnelPoint,
            std::shared_ptr<PointOnShortestPathTree> rightFunnelPoint,
            Point leftTriangleEdgePoint,
            Point rightTriangleEdgePoint
       );
    };
}
#endif // SHORTESTPATHTREECALCULATOR_H
