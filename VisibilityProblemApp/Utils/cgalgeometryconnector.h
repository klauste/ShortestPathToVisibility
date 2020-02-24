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
#include <boost/lexical_cast.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon;
typedef K::Segment_2 Segment;

/**
 * @brief The CGALGeometryConnector class connects the visualiation code and the minimum calculations library
 */
class CGALGeometryConnector
{
public:
    /**
     * @brief CGALGeometryConnector constructor
     */
    CGALGeometryConnector();

    /**
     * @brief The MinData struct contains data to draw the path to the minimal
     * lines of sight.
     */
    struct MinData {
        MinData(QLineF *l, double mV, Point pS, Point pE) :
            loS(l), minValue(mV), pointOnStartSide(pS), pointOnEndSide(pE)
        {}
        ~MinData() {
            delete loS;
            linesToMin.clear();
        }

        /**
         * @brief loS is the line of sight where the minimum is located
         */
        QLineF *loS;

        /**
         * @brief minValue contains either the minimized maximal distance (for the min-max version
         * of the problem) or the sum of distances (for the min-sum version of the problem).
         */
        double minValue;

        /**
         * @brief pointOnStartSide the last point on the path from the start point to
         * the minimal line of sight
         */
        Point pointOnStartSide;

        /**
         * @brief pointOnEndSide the last point on the path from the end point to
         * the minimal line of sight
         */
        Point pointOnEndSide;

        /**
         * @brief linesToMin contains all the lines which make up the path from the start/end point
         * to the last point on the polygon before the line of sight is reached.
         */
        std::vector<QLineF*> linesToMin;

        /**
         * @brief hasRadius flag to determine if this is a min-max minimum with a disc as solution
         */
        bool hasRadius = false;

        /**
         * @brief centerPoint the center point of the disc. Is only set if hasRadius is true.
         */
        QPointF centerPoint;

        /**
         * @brief radius the value of the disc's radius. Is only set if hasRadius is true.
         */
        double radius;
    };

    /**
     * @brief shouldClosePolyline given the current moust position at p, determines if the
     * polyline, which has been entered so far, should be closed to a polygon.
     * @param p
     * @return true if the point p is close enough to the start point of the polyline, false otherwise
     */
    bool shouldClosePolyline(QPointF p);

    /**
     * @brief addPointToCGALPolygon adds point p (the current mouse position) to the polygon
     * @param p
     */
    void addPointToCGALPolygon(QPointF p);

    /**
     * @brief handleFinalPoint handles one of the points (the start or the end point) for which the
     * path to pairwise visibility is to be calculated. If this function is called for the end point,
     * the functions to calculate the the minima are called.
     * @param p
     * @param isStart
     */
    void handleFinalPoint(QPointF p, bool isStart);

    /**
     * @brief doSegmentsIntersect checks if the segment from the last point of the polyline so far
     * to the current mouse position at p intersects the polyline
     * @param p
     * @return true if the polyline is intersected, false otherwise
     */
    bool doSegmentsIntersect(QPointF p);

    /**
     * @brief isPointInPolygon checks if point p is within the polygon
     * @param p
     * @return
     */
    bool isPointInPolygon(QPointF p);

    /**
     * @brief getShortestPathGraph returns the vector which contains the lines making up the shortest
     * path from the start point to the endpoint within the polygon
     * @return
     */
    std::vector<QLineF*> getShortestPathGraph();

    /**
     * @brief getPathEvents returns the vector containing the lines making up the path events
     * @return
     */
    std::vector<QLineF*> getPathEvents();

    /**
     * @brief getBoundaryEvents returns the vector containing the lines making up the boundary events
     * @return
     */
    std::vector<QLineF*> getBoundaryEvents();

    /**
     * @brief getBendEvents returns the vector containing the lines making up the bend events
     * @return
     */
    std::vector<QLineF*> getBendEvents();

    /**
     * @brief getMinMaxMinima returns the vector containing the min max minima
     * @return
     */
    std::vector<MinData*> getMinMaxMinima();

    /**
     * @brief getMinSumMinima returns the vector containint the min sum minima
     * @return
     */
    std::vector<MinData*> getMinSumMinima();

    /**
     * @brief reset resets all the vectors and destroys the calculators so that new
     * calculations can be done
     */
    void reset();

private:
    /**
     * @brief polygon the polygon entered by the user
     */
    Polygon polygon;

    /**
     * @brief startPoint first of the point pair
     */
    Point startPoint;

    /**
     * @brief endPoint second of the point pair
     */
    Point endPoint;

    /**
     * @brief addedSegments holds the segments which have so far been added to the polygon
     */
    std::vector<Segment> addedSegments;

    /**
     * @brief minSquaredDistanceToStartPoint how close the mouse needs to be to the start point
     * to close the polyline
     */
    double minSquaredDistanceToStartPoint;

    std::vector<QLineF*> shortestPathGraph;
    std::vector<QLineF*> pathEvents;
    std::vector<QLineF*> boundaryEvents;
    std::vector<QLineF*> bendEvents;
    std::vector<MinData*> minMaxMinima;
    std::vector<MinData*> minSumMinima;
    SPV::MinSumCalculator *minSumCalculator = nullptr;
    SPV::MinMaxCalculator *minMaxCalculator = nullptr;

    /**
     * @brief calculateMinima calculates the min-sum and min max solution of the problem
     * Expects that the polygon as well as the start and end point have been set
     */
    void calculateMinima();

    SPV::EventSegment *firstSegment;
    std::vector<std::shared_ptr<SPV::PointOnShortestPath>> shortestPath;

    /**
     * @brief setEvents populates the event vectors
     */
    void setEvents();

    /**
     * @brief setMinima populates the min vectors
     */
    void setMinima();

    /**
     * @brief setLinesToMin populates MinData.linesToMin with the linese
     * leading from the start and end point to the minimum
     * @param min
     * @param data
     */
    void setLinesToMin(std::shared_ptr<SPV::Minimum> min, MinData* data);
};

#endif // CGALGEOMETRYCONNECTOR_H
