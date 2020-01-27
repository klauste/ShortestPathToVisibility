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
#include "Models/pointwithtriangulationinfo.h"
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
        const std::vector<std::shared_ptr<PointOnShortestPath>> getShortestPath()
        {
            calculateShortestPath();
            return shortestPath;
        }

    protected:
        void calculateShortestPath();

    private:
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

        struct triangulationIndexInformation {
            Point nextPoint;
            unsigned leftPointIndex;
            unsigned rightPointIndex;
            unsigned nextPointIndex;
        };

        /**
         * Calculates the shortest path tree and map as described
         * in https://graphics.stanford.edu/courses/cs268-09-winter/notes/handout7.pdf.
         * During the calculation, it sets all the edges swept by lines of sight through
         * each of the points in the shortest path. The recursive build of the shortest
         * tree always goes left first. Therfore the swept edges will be added to each
         * point on the shortest path in order from left to right
         *
         * @brief setSweptSegmentsInShortestPath
         * @param firstFace
         * @return
         */
        void setSweptSegmentsInShortestPath(CDT::Face_handle firstFace);

        /**
         * Splits a funnel as described in https://graphics.stanford.edu/courses/cs268-09-winter/notes/handout7.pdf
         *
         * @brief splitFunnel
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

        void splitFunnelAtApex(
                CDT::Face_handle nextFace,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
                std::shared_ptr<triangulationIndexInformation> indexInfo
        );
        void splitFunnelAtLastPoint(
                CDT::Face_handle nextFace,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
                bool nextPointOnLeftFunnel,
                std::shared_ptr<triangulationIndexInformation> indexInfo
        );
        void splitFunnelAtMidPoint(
                CDT::Face_handle nextFace,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
                bool nextPointOnLeftFunnel,
                std::shared_ptr<triangulationIndexInformation> indexInfo,
                unsigned newApexIndex
        );
        void handleTriangleBeyondLastEdge(
                CDT::Face_handle nextFace,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::shared_ptr<PointOnShortestPathTree> firstPointOnTree,
                bool lastPointOnLeftFunnel
        );
        std::shared_ptr<predecessorInfo> findPredecessor(
                Point p,
                std::shared_ptr<PointOnShortestPathTree> apex,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
                std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel
        );


        std::shared_ptr<PointWithTriangulationInfo> rootPoint;
        bool rootAtEndPoint;
        std::vector<std::shared_ptr<PointOnShortestPathTree>> shortestPathTree;
        int currentPointOnShortestPathIndex;

        bool allPointsOnShortestPathHandled()
        {
            if (rootAtEndPoint) {
                return currentPointOnShortestPathIndex <= 1;
            }
            return currentPointOnShortestPathIndex >= shortestPath.size() - 1;
        }

        Point getNextPointOnShortestPath()
        {
            int index;
            if (rootAtEndPoint) {
                index = currentPointOnShortestPathIndex - 1;
            } else {
                index = currentPointOnShortestPathIndex + 1;
            }
            return shortestPath.at(index)->getPoint();
        }

        bool isPointOnShortestPath(std::shared_ptr<PointOnShortestPathTree> pointToCheck)
        {
            if (allPointsOnShortestPathHandled()) {
                return false;
            }
            if (getNextPointOnShortestPath() == pointToCheck->getPoint()) {
                // Set the shortest path to the
                if (rootAtEndPoint) {
                    currentPointOnShortestPathIndex = currentPointOnShortestPathIndex - 1;
                } else {
                    currentPointOnShortestPathIndex = currentPointOnShortestPathIndex + 1;
                }
                return true;
            }
            return false;
        }

        void addPointToShortestPathTree(std::shared_ptr<PointOnShortestPathTree> p)
        {
            if (isPointOnShortestPath(p)) {
                p->setIndexOnShortestPath(currentPointOnShortestPathIndex);
            }
            shortestPathTree.push_back(p);
        }

        std::shared_ptr<triangulationIndexInformation> getTriangulationIndexInformation(
                Point leftPoint,
                Point rightPoint,
                CDT::Face_handle faceHandle
        );
        GeometryUtil gU = GeometryUtil();

        void calculateSweptSegments(
           CDT::Face_handle currentFace,
           std::shared_ptr<PointOnShortestPathTree> apex,
           std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
           std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
           std::shared_ptr<triangulationIndexInformation> tI
        );

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
