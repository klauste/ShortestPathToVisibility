#ifndef MINIMUM_H
#define MINIMUM_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Point_2.h>
#include "Models/eventsegment.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

namespace SPV {
    class Minimum {
    public:
        Minimum () :
            isInDiscArea(false),
            minSectorStart(false),
            minSectorEnd(false)
        {}

        /**
         * @brief setStartSideIntersectionOnLoS sets the end point of the path from the start point
         * to this minimum
         * @param p
         */
        void setStartSideIntersectionOnLoS(Point p);

        /**
         * @brief setEndSideIntersectionOnLoS sets the end point of the path from the end point
         * to this minimum
         * @param p
         */
        void setEndSideIntersectionOnLoS(Point p);

        /**
         * @brief setStartSideIntersectionOnEdge sets the line of sight's point on the polygon edge on the start
         * side
         * @param p
         */
        void setStartSideIntersectionOnEdge(Point p);

        /**
         * @brief setEndSideIntersectionOnEdge sets the line of the sight's point on the polygonedge on the end
         * side
         * @param p
         */
        void setEndSideIntersectionOnEdge(Point p);

        /**
         * @brief getStartSideIntersectionOnLoS returns the end point of the path from the start point
         * @return
         */
        Point getStartSideIntersectionOnLoS();

        /**
         * @brief getStartSideIntersectionOnEdge returns the point of the line of sight on the polygon
         * boundary closer to the start point
         * @return
         */
        Point getStartSideIntersectionOnEdge();

        /**
         * @brief getEndSideIntersectionOnLoS returns the end point of the path from the end point
         * @return
         */
        Point getEndSideIntersectionOnLoS();

        /**
         * @brief getEndSideIntersectionOnEdge returns the point of the line of sight on the polygon
         * boundary closer to the end point
         * @return
         */
        Point getEndSideIntersectionOnEdge();

        /**
         * @brief setEventSegment stores a pointer to the event segment within which this line of sight lies
         * @param eS
         */
        void setEventSegment(EventSegment *eS);

        /**
         * @brief getEventSegment returns the event segment within which this line of sight lies
         * @return
         */
        EventSegment* getEventSegment();

        /**
         * @brief setIsInDiscArea indicates whether this is is a set of minima in a disc area
         * @param value
         */
        void setIsInDiscArea(bool value);

        /**
         * @brief getIsInDiscArea returns the flag
         * @return
         */
        bool getIsInDiscArea();

        /**
         * @brief setDiscRadius sets the radius of the disc area
         * @param r
         */
        void setDiscRadius(double r);

        /**
         * @brief getDiscRadius returns the disc area
         * @return
         */
        double getDiscRadius();

        /**
         * @brief setDistance sets the distances from the start/end point to this minimum. If this is
         * a min-max minimum, it should be minimal distance. If this is a min-sum minimum, it should
         * be the sum of the distances
         * @param d
         */
        void setDistance(double d);

        /**
         * @brief getDistance returns the distance
         * @return
         */
        double getDistance();

        /**
         * @brief setMinSectorStart sets the sector start flag
         * @param b
         */
        void setMinSectorStart(bool b);

        /**
         * @brief setMinSectorEnd sets the sector end flag
         * @param b
         */
        void setMinSectorEnd(bool b);

        /**
         * @brief isMinSectorStart returns the sector start flag
         * @return
         */
        bool isMinSectorStart();

        /**
         * @brief isMinSectorEnd returns the sector end flag
         * @return
         */
        bool isMinSectorEnd();

        /**
         * @brief setDiscOnStartSide sets the discOnStartSide flag
         * @param b
         */
        void setDiscOnStartSide(bool b);

        /**
         * @brief isDiscOnStartSide returns the flag indicating if the set of minima within a disc
         * is on the start side
         * @return
         */
        bool isDiscOnStartSide();
    private:
        /**
         * @brief startSideIntersectionOnLoS the intersection on the line of sight on the path
         * from the start point
         */
        Point startSideIntersectionOnLoS;

        /**
         * @brief startSideIntersectionOnEdge the intersection of the line of sight with the polygon
         * boundary closer to the start point
         */
        Point startSideIntersectionOnEdge;

        /**
         * @brief endSideIntersectionOnLoS the intersection on the line of sight on the path
         * from the end point
         */
        Point endSideIntersectionOnLoS;

        /**
         * @brief endSideIntersectionOnEdge the intersection of the line of sight with the polygon
         * boundary closer to the end point
         */
        Point endSideIntersectionOnEdge;

        /**
         * @brief isInDiscArea whether there is a set of minima within a disc
         */
        bool isInDiscArea = false;

        /**
         * @brief discRadius the radius of the disc (if the minima are a set within a disc)
         */
        double discRadius;

        /**
         * @brief distance the distance to this minimum. If this is a min-max minimum, it's the minimal distance.
         * Otherwise, it's the sum of minima.
         */
        double distance;

        /**
         * @brief eventSegment points to the event segment within which this line of sight lies
         */
        EventSegment *eventSegment;

        /**
         * @brief minSectorStart if a minimum is not unique, this flag indicates that a sector of minima
         * starts at this line of sight
         */
        bool minSectorStart = false;

        /**
         * @brief minSectorEnd if a minimum is not unique, this flag indicates that a sector of minima
         * ends
         */
        bool minSectorEnd = false;

        /**
         * @brief discOnStartSide indicates if the disc containing all minima is on the start side
         */
        bool discOnStartSide;
    };
}

#endif // MINIMUM_H
