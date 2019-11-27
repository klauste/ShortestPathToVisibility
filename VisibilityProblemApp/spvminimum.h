#ifndef SPVMINIMUM_H
#define SPVMINIMUM_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Point_2.h>
#include <iostream>
#include "spventryonshortestpath.h"
#include "spveventintersection.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

namespace SPV {
    class Minimum {
    public:
        Minimum () {}
        void setStartIntersectionOnLoS(Point p) {
            startIntersectionOnLoS = p;
        }

        Point getStartIntersectionOnLoS() {
            return startIntersectionOnLoS;
        }

        void setEndIntersectionOnLoS(Point p) {
            endIntersectionOnLoS = p;
        }

        Point getEndIntersectionOnLoS() {
            return endIntersectionOnLoS;
        }

        void setStartIntersectionOnEdge(Point p) {
            startIntersectionOnEdge = p;
        }

        Point getStartIntersectionOnEdge() {
            return startIntersectionOnEdge;
        }

        void setEndIntersectionOnEdge(Point p) {
            endIntersectionOnEdge = p;
        }

        Point getEndIntersectionOnEdge() {
            return endIntersectionOnEdge;
        }

        void setLastIntersectionFromStart(EventIntersection *ei) {
            lastEventIntersectionFromStart = ei;
        }

        EventIntersection* getLastIntersectionFromStart() {
            return lastEventIntersectionFromStart;
        }

        void setLastIntersectionFromEnd(EventIntersection *ei) {
            lastEventIntersectionFromEnd = ei;
        }

        EventIntersection* getLastIntersectionFromEnd() {
            return lastEventIntersectionFromEnd;
        }

        void setPivotPointIndex (unsigned i) {
            pivotPointIndex = i;
        }

        unsigned getPivotPointIndex() {
            return pivotPointIndex;
        }

        void setIsInDiscArea(bool value) {
            isInDiscArea = value;
        }

        bool getIsInDiscArea() {
            return isInDiscArea;
        }

        void setDiscRadius(unsigned r) {
            discRadius = r;
        }

        double getDiscRadius() {
            if (isInDiscArea) {
                return discRadius;
            }
            return 0;
        }

        void setDistance(unsigned d) {
            distance = d;
        }

        double getDistance() {
            return distance;
        }
    private:
        Point startIntersectionOnLoS;
        Point endIntersectionOnLoS;
        Point startIntersectionOnEdge;
        Point endIntersectionOnEdge;
        EventIntersection *lastEventIntersectionFromStart;
        EventIntersection *lastEventIntersectionFromEnd;
        unsigned pivotPointIndex;
        bool isInDiscArea = false;
        double discRadius;
        double distance;
    };
}

#endif // SPVMINIMUM_H
