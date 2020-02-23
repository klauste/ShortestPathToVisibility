#ifndef BASECALCULATOR_H
#define BASECALCULATOR_H
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include "Models/eventsegment.h"
#include "Models/pointonshortestpath.h"
#include "Models/sweptsegment.h"
#include "Utils/geometryutil.h"
#include "Models/lineofsight.h"
#include "Models/minimum.h"
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

        virtual ~BaseCalculator() {}

        /**
         * @brief calculatePathAndBoundaryEvents calculates the path and boundary events
         */
        virtual void calculatePathAndBoundaryEvents() = 0;

        /**
         * @brief calculateBendEvents calculates the bend events
         */
        virtual void calculateBendEvents() = 0;

        /**
         * @brief calculateMinima calculates the minima (either min-max or min-sum)
         */
        virtual void calculateMinima() = 0;

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
        std::vector<std::shared_ptr<PointOnShortestPath>> getShortestPath();

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

        /**
         * @brief getAllMinima returns the vector with the minima
         * @return
         */
        std::vector<std::shared_ptr<Minimum>> getAllMinima();

        /**
         * @brief hasDirectPath returns the value of directPathExists
         * @return
         */
        bool hasDirectPath();

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

        /**
         * @brief stepPrecision the precision used to calculate minima if at least one line of sight is
         * obstructed by a polygon edge
         */
        double stepPrecision = 0.001;

        /**
         * @brief allMinima contains the minima
         */
        std::vector<std::shared_ptr<Minimum>> allMinima;

        /**
         * @brief currentMinimum the currently minimal distance to a line of sight
         */
        double currentMinimum;

        /**
         * @brief directPathExists indicates if a direct path exists between the start and end point
         */
        bool directPathExists;

        /**
         * @brief getDistanceToIntersectionPoint returns the distance to an intersection point on a line
         * of sight for the current event segment
         * @param intersectionPoint
         * @param onStartSide
         * @return
         */
        double getDistanceToIntersectionPoint(Point intersectionPoint, bool onStartSide);

        /**
         * @brief getIntersectionPointOnLoS returns the intersection point an a line of sight for the
         * current event segment
         * @param intersectionPointOnBoundary
         * @param onStartSide
         * @return
         */
        Point getIntersectionPointOnLoS(Point intersectionPointOnBoundary, bool onStartSide);

        /**
         * @brief handleNewGlobalMinimum checks if newMinimumValue is a new global value (compared to the
         * minima so far). If that's the case a new minimum is added to the minima vector. If the new
         * minimum value is the same as the minimal value so far, the minima so far are not removed
         * @param newMinimumValue
         * @param startSideIntersectionOnLoS
         * @param endSideIntersectionOnLoS
         * @param startSideIntersectionOnEdge
         * @param endSideIntersectionOnEdge
         * @param calculateMinimumSector
         */
        void handleNewGlobalMinimum (
            double newMinimumValue,
            Point startSideIntersectionOnLoS,
            Point endSideIntersectionOnLoS,
            Point startSideIntersectionOnEdge,
            Point endSideIntersectionOnEdge,
            bool calculateMinimumSector = false
        );

    private:
        /**
         * @brief setMinimumDetails sets the details of a minimum
         * @param min
         * @param newMinimumValue
         * @param startSideIntersectionOnLoS
         * @param endSideIntersectionOnLoS
         * @param startSideIntersectionOnEdge
         * @param endSideIntersectionOnEdge
         * @param isMinSectorStart
         * @param isMinSectorEnd
         */
        void setMinimumDetails(
            std::shared_ptr<Minimum> min,
            double newMinimumValue,
            Point startSideIntersectionOnLoS,
            Point endSideIntersectionOnLoS,
            Point startSideIntersectionOnEdge,
            Point endSideIntersectionOnEdge,
            bool isMinSectorStart,
            bool isMinSectorEnd
        );
    };
}
#endif // BASECALCULATOR_H
