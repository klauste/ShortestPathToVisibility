#ifndef SPVGRAPHICSSCENECGALMODEL_H
#define SPVGRAPHICSSCENECGALMODEL_H
#include <QPointF>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Qt/PolygonGraphicsItem.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <vector>
#include "spvshortestpath.h"
#include "spventryonshortestpath.h"
#include "spvminimum.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Segment_2 Segment;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon;
typedef CGAL::Qt::PolygonGraphicsItem<Polygon> PolygonGraphic;

namespace SPV {
    class SPVGraphicsSceneCGALModel {
    public:
        /**
         * Addes the segment defined by start and end to the segment vector
         *
         * @brief addSegment
         * @param start
         * @param end
         */
        void addSegment(const QPointF &start, const QPointF &end);

        const std::vector<ShortestPathEntry*>& getSleevePath(int i) {
            return shortestPath.getSleevePath(i);
        }

        std::vector<SPV::PointOnShortestPath *> getShorttestPathTree() {
            return shortestPath.getShorttestPathTree();
        }

        std::vector<SPV::Minimum*> getMinima() {
            return shortestPath.getMinima();
        }

        Polygon getPolygon() {
            return polygon;
        }
        /**
         * This function checks if the setmgent defined by start and end intersects any of
         * the segments already added to the scene mode. If the end point of an added sement
         * is the same as the start point of the new segment, intersection is not tested
         *
         * @brief SPV::SPVGraphicsSceneCGALModel::doSegmentsIntersect
         * @param start
         * @param end
         * @return
         */
        bool doSegmentsIntersect(const QPointF &start, const QPointF &end);

        /**
         * Sets the start point of the current polyline to qPoint
         *
         * @brief setPolylineStartPoint
         * @param $qPoint
         */
        void setPolylineStartPoint(const QPointF &qPoint);

        /**
         * Checks if currentPoint is close enough to the polyline start point
         * to close the polygon
         *
         * @brief shouldClosePolyline
         * @param currentPoint
         * @return
         */
        bool shouldClosePolyline(const QPointF &currentPoint);

        /**
         * Checks if currentPoint is inside the polygon
         *
         * @brief isPointInPolygon
         * @param currentPoint
         * @return
         */
        bool isPointInPolygon(const QPointF &currentPoint);

        /**
         * Creates a polygon out of the current polyline and removes all segments from
         * segmentsAddedSoFar
         *
         * @brief closePolyline
         */
        void closePolyline(const QPointF &start);

        /**
         * Adds the currentPoint into visibilityPair at index
         *
         * @brief addPairPoint
         * @param currentPoint
         * @param index
         */
        void addPairPoint(const QPointF &currentPoint, int index);

        PolygonGraphic *getQtPolygon();
        std::vector<Segment>* getLinesAddedSoFar();
        const CDT& getCdt() {
            return shortestPath.getTriangulation();
        }
        void calculateShortestPath();

    private:
        std::vector<Segment> segmentsAddedSoFar;
        Point polylineStartPoint;
        const double minSquaredDistanceToStartPoint = 400;
        Polygon polygon;
        PolygonGraphic *polygonGraphicItem;
        ShortestPath shortestPath;
    };
}

#endif // SPVGRAPHICSSCENECGALMODEL_H
