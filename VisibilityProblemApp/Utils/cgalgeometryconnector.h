#ifndef CGALGEOMETRYCONNECTOR_H
#define CGALGEOMETRYCONNECTOR_H

#include <QPointF>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include "Minima/minsumcalculator.h"
#include "Minima/minmaxcalculator.h"
#include <QLineF>
#include <QRectF>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon;
typedef K::Segment_2 Segment;

class CGALGeometryConnector
{
public:
    struct minData {
        minData(QLineF *l, QLineF *lS, QLineF *lE, double mV) :
            loS(l), lastPointToMinStartSide(lS), lastPointToMinEndSide(lE), minValue(mV)
        {}
        ~minData() {
            delete loS;
            delete lastPointToMinStartSide;
            delete lastPointToMinEndSide;
        }
        QLineF *loS;
        QLineF *lastPointToMinStartSide;
        QLineF *lastPointToMinEndSide;
        double minValue;
        bool hasRadius = false;
        QPointF centerPoint;
        double radius;
    };
    bool shouldClosePolyline(QPointF p);
    void addPointToCGALPolygon(QPointF p);
    void handleFinalPoint(QPointF p, bool isStart);
    bool doSegmentsIntersect(QPointF p);
    bool isPointInPolygon(QPointF p);
    const std::vector<QLineF*> &getShortestPathGraph()
    {
        return shortestPathGraph;
    }
    const std::vector<QLineF*> &getPathEvents()
    {
        return pathEvents;
    }
    const std::vector<QLineF*> &getBoundaryEvents()
    {
        return boundaryEvents;
    }
    const std::vector<QLineF*> &getBendEvents()
    {
        return bendEvents;
    }
    const std::vector<minData*> &getMinMaxMinima()
    {
        return minMaxMinima;
    }
    const std::vector<minData*> &getMinSumMinima()
    {
        return minSumMinima;
    }
    void reset();

private:
    Polygon polygon = Polygon();
    Point startPoint;
    Point endPoint;
    std::vector<Segment> addedSegments;
    const double minSquaredDistanceToStartPoint = 400;
    std::vector<QLineF*> shortestPathGraph;
    std::vector<QLineF*> pathEvents;
    std::vector<QLineF*> boundaryEvents;
    std::vector<QLineF*> bendEvents;
    std::vector<minData*> minMaxMinima;
    std::vector<minData*> minSumMinima;
    std::vector<QRectF*> sweptSegments;
    SPV::MinSumCalculator *minSumCalculator = nullptr;
    SPV::MinMaxCalculator *minMaxCalculator = nullptr;
    void calculateMinima();
    SPV::EventSegment *firstSegment;
    std::vector<std::shared_ptr<SPV::PointOnShortestPath>> shortestPath;
    void setEvents();
    void setMinima();
};

#endif // CGALGEOMETRYCONNECTOR_H
