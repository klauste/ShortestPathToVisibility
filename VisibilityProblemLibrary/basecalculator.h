#ifndef BASECALCULATOR_H
#define BASECALCULATOR_H
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include "Models/eventsegment.h"
#include "Models/pointonshortestpath.h"
#include "Models/sweptsegment.h"
#include "Utils/geometryutil.h"
#include "Models/lineofsight.h"
#include "ShortestPath/shortestpathtreecalculator.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Line_2 Line;

namespace SPV {
    /**
     * @brief The BaseCalculator class contains data and functions needed by all calculators
     */
    class BaseCalculator
    {
    public:
        /**
         * @brief BaseCalculator constructor needs a polygon, a start point and an end point. The
         * start and end point are assumed to be inside the polygon.
         * @param p
         * @param s
         * @param e
         */
        BaseCalculator(const Polygon &p, const Point s, Point e);

        /**
         * @brief getFirstEventSegment returns the first event segment. After calculating the
         * events the event segments contain all relevant information about the location of
         * the events.
         * @return
         */
        EventSegment* getFirstEventSegment();

        /**
         * @brief getShortestPath return the shortest path from the start to the end point
         * @return
         */
        const std::vector<std::shared_ptr<PointOnShortestPath>> getShortestPath();

        /**
         * @brief getLastPointBeforeLoS given an event segment, this function returns the last
         * point before a line of sight in the event segment is reached. The last point can be
         * either the start or end point, a point on the shortest path or a polygon vertex add
         * because of a boundary event.
         * @param eS
         * @param onStartSide
         * @return
         */
        Point getLastPointBeforeLoS(EventSegment *eS, bool onStartSide);

    protected:
        /**
         * @brief shortestPath from start point to end point
         */
        std::vector<std::shared_ptr<PointOnShortestPath>> shortestPath;

        /**
         * @brief currentEventSegment pointer to an event segment
         */
        EventSegment *currentEventSegment;

        /**
         * @brief firstEventSegment pointer to the first event segment, i.e. the one which has the start
         * point on one of its edges
         */
        EventSegment *firstEventSegment;

        /**
         * @brief gU instance of the geometry util used for static calculations
         */
        GeometryUtil gU;
    };
}
#endif // BASECALCULATOR_H
