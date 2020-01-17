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
#include "spvfaceinfo.h"

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
    class ShortestPathTreeCalculator
    {
    public:
        /**
         * Constructor for a shortest path tree calculator. If this constructs a tree starting at the end point
         * of the shortest path rootAtEnd should be set to true, otherwise to false
         *
         * @brief ShortestPathTreeCalculator
         * @param rP
         * @param rootAtEnd
         */
        ShortestPathTreeCalculator(Point rP, const std::vector<PointOnShortestPath* > &sP, bool rootAtEnd)  {
            shortestPath = sP;
            rootAtEndPoint = rootAtEnd;
            if (rootAtEndPoint) {
                rootPoint = new PointWithTriangulationInfo(rP);
                currentPointOnShortestPathIndex = shortestPath.size() - 1;
            } else {
                rootPoint = new PointWithTriangulationInfo(rP);
                currentPointOnShortestPathIndex = 0;
            }
        }

        ~ShortestPathTreeCalculator()
        {
            shortestPathTree.clear();
        }

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

    private:
        std::vector <PointOnShortestPath* > shortestPath;
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
                PointOnShortestPathTree* apex,
                std::vector<PointOnShortestPathTree*> &leftFunnel,
                std::vector<PointOnShortestPathTree*> &rightFunnel
        );

        void splitFunnelAtApex(
                CDT::Face_handle nextFace,
                SPV::PointOnShortestPathTree* apex,
                std::vector<PointOnShortestPathTree*> &leftFunnel,
                std::vector<PointOnShortestPathTree*> &rightFunnel,
                triangulationIndexInformation *indexInfo
        );
        void splitFunnelAtLastPoint(
                CDT::Face_handle nextFace,
                SPV::PointOnShortestPathTree* apex,
                std::vector<PointOnShortestPathTree*> &leftFunnel,
                std::vector<PointOnShortestPathTree*> &rightFunnel,
                bool nextPointOnLeftFunnel,
                triangulationIndexInformation *indexInfo
        );
        void splitFunnelAtMidPoint(
                CDT::Face_handle nextFace,
                SPV::PointOnShortestPathTree* apex,
                std::vector<PointOnShortestPathTree*> &leftFunnel,
                std::vector<PointOnShortestPathTree*> &rightFunnel,
                bool nextPointOnLeftFunnel,
                triangulationIndexInformation *indexInfo,
                unsigned newApexIndex
        );
        void handleTriangleBeyondLastEdge(
                CDT::Face_handle nextFace,
                PointOnShortestPathTree *apex,
                PointOnShortestPathTree *firstPointOnTree,
                bool lastPointOnLeftFunnel
        );
        predecessorInfo* findPredecessor(
                Point p,
                SPV::PointOnShortestPathTree* apex,
                std::vector<SPV::PointOnShortestPathTree*> &leftFunnel,
                std::vector<SPV::PointOnShortestPathTree*> &rightFunnel
        );


        PointWithTriangulationInfo* rootPoint;
        bool rootAtEndPoint;
        std::vector<PointOnShortestPathTree*> shortestPathTree;
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

        bool isPointOnShortestPath(PointOnShortestPathTree* pointToCheck)
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

        void addPointToShortestPathTree(PointOnShortestPathTree *p)
        {
            if (isPointOnShortestPath(p)) {
                p->setIndexOnShortestPath(currentPointOnShortestPathIndex);
            }
            shortestPathTree.push_back(p);
        }

        triangulationIndexInformation* getTriangulationIndexInformation(Point leftPoint, Point rightPoint, CDT::Face_handle faceHandle);
        GeometryUtil gU = GeometryUtil();

        void calculateSweptSegments(
           CDT::Face_handle currentFace,
           PointOnShortestPathTree* apex,
           std::vector<PointOnShortestPathTree*> &leftFunnel,
           std::vector<PointOnShortestPathTree*> &rightFunnel,
           triangulationIndexInformation *tI
        );

        void calculateAndAddSegment(
            PointOnShortestPathTree* apex,
            PointOnShortestPathTree* leftFunnelPoint,
            PointOnShortestPathTree* rightFunnelPoint,
            Point leftTriangleEdgePoint,
            Point rightTriangleEdgePoint
       );
    };
}
#endif // SHORTESTPATHTREECALCULATOR_H
