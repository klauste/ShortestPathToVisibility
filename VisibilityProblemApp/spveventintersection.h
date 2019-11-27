#ifndef SPVEVENTINTERSECTION_H
#define SPVEVENTINTERSECTION_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

namespace SPV {
    class EventIntersection {
    public:
        EventIntersection (int et, Point pOnSp, Point pInter, Point segStart, Point segEnd) :
            eventType(et),
            pointOnShortestPath(pOnSp),
            intersection(pInter),
            segmentStart(segStart),
            segmentEnd(segEnd) {}

        Point getIntersection() {
            return intersection;
        }

        Point getPointOnShortestPath() {
            return pointOnShortestPath;
        }

        Point getSegmentStart() {
            return segmentStart;
        }

        Point getSegmentEnd() {
            return segmentEnd;
        }

        void swapSegmentPoints() {
            Point temp = segmentStart;
            segmentStart = segmentEnd;
            segmentEnd = temp;
        }

        int getEventType() {
            return eventType;
        }

        void addToPathToLos(Point p, bool fromStart) {
            if (fromStart) {
                sptToLineOfSightFromStart.push_back(p);
            } else {
                sptToLineOfSightFromEnd.push_back(p);
            }
        }

        void clearPathToLoS(bool fromStart) {
            if (fromStart) {
                sptToLineOfSightFromStart.clear();
            } else {
                sptToLineOfSightFromEnd.clear();
            }
        }

        void removeLastElementOnPathToLos(bool fromStart) {
            if (fromStart) {
                sptToLineOfSightFromStart.pop_back();
            } else {
                sptToLineOfSightFromEnd.pop_back();
            }
        }
        std::vector<Point> getPathToLineOfSight(bool fromStart) {
            if (fromStart) {
                return sptToLineOfSightFromStart;
            }
            return sptToLineOfSightFromEnd;
        }

        bool getSptToLineOfSightOnPolygonEdge(bool fromStart) {
            if (fromStart) {
                return sptToLoSOnPolygonEdgeFromStart;
            }
            return sptToLoSOnPolygonEdgeFromEnd;
        }

        void setSptToLineOfSightOnPolygonEdge(bool value, bool fromStart) {
            if (fromStart) {
                sptToLoSOnPolygonEdgeFromStart = value;
            } else {
                sptToLoSOnPolygonEdgeFromEnd = value;
            }
        }

        bool getPathToSemiCirclesIsFree(bool fromStart) {
            if (fromStart) {
                return pathToSemiCirclesIsFreeFromStart;
            }
            return pathToSemiCirclesIsFreeFromEnd;
        }

        void setPathToSemiCirclesIsFree(bool value, bool fromStart) {
            if (fromStart) {
                pathToSemiCirclesIsFreeFromStart = value;
            } else {
                pathToSemiCirclesIsFreeFromEnd = value;
            }
        }

        bool getHasChangeInDirection() {
            return hasChangeInDirection;
        }

        void setHasChangeInDirection() {
            hasChangeInDirection = true;
        }

        bool belongsToStart() {
            return isStartEvent;
        }

        void setBelongsToStart(bool value) {
            isStartEvent = value;
        }
    private:
        int eventType;
        Point pointOnShortestPath;
        Point intersection;
        Point segmentStart;
        Point segmentEnd;
        std::vector<Point> sptToLineOfSightFromStart;
        std::vector<Point> sptToLineOfSightFromEnd;
        bool sptToLoSOnPolygonEdgeFromStart = false;
        bool sptToLoSOnPolygonEdgeFromEnd = false;
        bool pathToSemiCirclesIsFreeFromStart = true;
        bool pathToSemiCirclesIsFreeFromEnd = true;
        bool isStartEvent = false;
        bool hasChangeInDirection = false;
    };
}

#endif // SPVEVENTINTERSECTION_H
