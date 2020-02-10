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
        Minimum () {}
        void setStartSideIntersectionOnLoS(Point p) {
            startSideIntersectionOnLoS = p;
        }

        void setEndSideIntersectionOnLoS(Point p) {
            endSideIntersectionOnLoS = p;
        }

        void setStartSideIntersectionOnEdge(Point p) {
            startSideIntersectionOnEdge = p;
        }

        void setEndSideIntersectionOnEdge(Point p) {
            endSideIntersectionOnEdge = p;
        }

        Point getStartSideIntersectionOnLoS()
        {
            return startSideIntersectionOnLoS;
        }

        Point getStartSideIntersectionOnEdge()
        {
            return startSideIntersectionOnEdge;
        }

        Point getEndSideIntersectionOnLoS() {
            return endSideIntersectionOnLoS;
        }

        Point getEndSideIntersectionOnEdge() {
            return endSideIntersectionOnEdge;
        }

        void setEventSegment(EventSegment *eS) {
            eventSegment = eS;
        }

        EventSegment* getEventSegment() {
            return eventSegment;
        }

        void setIsInDiscArea(bool value) {
            isInDiscArea = value;
        }

        bool getIsInDiscArea() {
            return isInDiscArea;
        }

        void setDiscRadius(double r) {
            discRadius = r;
        }

        double getDiscRadius() {
            if (isInDiscArea) {
                return discRadius;
            }
            return 0;
        }

        void setDistance(double d) {
            distance = d;
        }

        double getDistance() {
            return distance;
        }

        void setMinSectorStart(bool b)
        {
            minSectorStart = b;
        }

        void setMinSectorEnd(bool b)
        {
            minSectorEnd = b;
        }

        bool isMinSectorStart()
        {
            return minSectorStart;
        }

        bool isMinSectorEnd()
        {
            return minSectorEnd;
        }

        void setDiscOnStartSide(bool b)
        {
            discOnStartSide = b;
        }

        bool isDiscOnStartSide()
        {
            return discOnStartSide;
        }
    private:
        Point startSideIntersectionOnLoS;
        Point startSideIntersectionOnEdge;
        Point endSideIntersectionOnLoS;
        Point endSideIntersectionOnEdge;
        bool isInDiscArea = false;
        double discRadius;
        double distance;
        EventSegment *eventSegment;
        bool minSectorStart = false;
        bool minSectorEnd = false;
        bool discOnStartSide;
    };
}

#endif // MINIMUM_H
