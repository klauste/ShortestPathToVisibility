#ifndef SPVMINIMUMCALCULATOR_H
#define SPVMINIMUMCALCULATOR_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <vector>
#include <iostream>
#include "spvshortestpathtree.h"
#include "spvfaceinfo.h"
#include "spventryonshortestpath.h"
#include "spveventintersection.h"
#include "spveventmap.h"
#include "spvgeometryutil.h"
#include "spvboundaryevents.h"
#include "spvbaseevents.h"
#include "spvminimum.h"
#include <CGAL/squared_distance_2.h>
#include <math.h>

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
    class MinimumCalculator: public BaseEvents {
    public:
        MinimumCalculator() {}
        MinimumCalculator(std::vector<ShortestPathEntry *> sP, EventMap &eM) {
            shortestPath = sP;
            eventMap = eM;
        }
        void calculateMinima();
        std::vector<Minimum*> getAllMinima() {
            return allMinima;
        }

    protected:
            void handleNewMinimum (
                double newMinimum,
                EventIntersection* startIntersection,
                EventIntersection* endIntersection,
                Point startIntersectionOnLoS,
                Point endIntersectionOnLoS,
                Point startIntersectionOnEdge,
                Point endIntersectionOnEdge,
                unsigned pivotPointIndex
            );
            std::vector<Minimum*> allMinima;
            void calculateMinimaBetween2PathEvents (
                EventIntersection *currentIntersection,
                Point nextIntersectionStart,
                unsigned pivotPointIndex,
                bool goLeft
            );
            void calculateMinimumBetween2Events (
                EventIntersection *firstIntersection,
                EventIntersection *secondIntersection,
                unsigned pivotPointIndex,
                bool goLeft
            );
            void handleMinimaWithBothPathsFree(
                EventIntersection *firstIntersection,
                EventIntersection *secondIntersection,
                EventIntersection *oppositeFirstIntersection,
                EventIntersection *oppositeSecondIntersection,
                unsigned pivotPointIndex
            );
            void handleMinimaWithBothPathsBlocked(
                EventIntersection *firstIntersection,
                EventIntersection *secondIntersection,
                EventIntersection *oppositeFirstIntersection,
                EventIntersection *oppositeSecondIntersection,
                unsigned pivotPointIndex
            );
            double getDistanceSoFar(EventIntersection *ei, bool fromStart) {
                std::vector<Point> pointsToLoS = ei->getPathToLineOfSight(fromStart);

                // If there is only one point, the distance is zero
                if (pointsToLoS.size() == 1) {
                    return 0;
                }
                double distance = 0;
                for (unsigned i = 0; i < pointsToLoS.size() - 1; i++) {
                    distance = distance + sqrt(CGAL::squared_distance(pointsToLoS.at(i), pointsToLoS.at(i + 1)));
                }
                return distance;
            }
            double currentMinimum = -1.0;
            bool handleMinimumAtPivotPoint(
                EventIntersection *firstIntersection,
                EventIntersection *secondIntersection,
                EventIntersection *oppositeFirstIntersection,
                EventIntersection *oppositeSecondIntersection,
                unsigned pivotPointIndex
            );
            void handleMinimaWithOnePathBlocked(
                EventIntersection *firstIntersection,
                EventIntersection *secondIntersection,
                EventIntersection *oppositeFirstIntersection,
                EventIntersection *oppositeSecondIntersection,
                unsigned pivotPointIndex
            );
            bool valuesAreEqual(double dist1, double dist2, double factor = 1.0);
            double getDistanceToIntersectionPoint(EventIntersection *ei, Point intersectionPoint, bool fromStart);
            Point getIntersectionPointOnLoS(EventIntersection *ei, Point intersectionPoint, unsigned pivotPointIndex, bool fromStart);
            double precision = 0.01;
            EventIntersection *lastIntersectionFromStart;
    };
}
#endif // MINIMUMCALCULATOR_H
