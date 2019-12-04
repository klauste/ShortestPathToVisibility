#ifndef SHORTESTPATHMAP_H
#define SHORTESTPATHMAP_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/intersections.h>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Triangle_2 Triangle;
typedef K::Segment_2 Segment;
typedef K::Ray_2 Ray;
typedef K::Intersect_2 Intersect_2;

namespace SPV {
    class EventOnShortestPath {
    public:
        EventOnShortestPath(Point fP, Point sP) : firstDefiningPoint(fP), secondDefiningPoint(sP) {}
        Point getFirstDefiningPoint();
        Point getSecondDefiningPoint();
        Point getFirstPointIntersection();
        Point getSecondPointIntersection();
        void setFirstPointIntersection(Point p);
        void setSecondPointIntersection(Point p);
        void calculateIntersection(Point segPoint1, Point segPoint2, bool startToEnd) {
            Ray r;
            Segment s = Segment(segPoint1, segPoint2);

            if (startToEnd) {
                r = Ray(firstDefiningPoint, secondDefiningPoint);
            } else {
                r = Ray(secondDefiningPoint, firstDefiningPoint);
            }
            CGAL::cpp11::result_of<Intersect_2(Ray, Segment)>::type
                result = intersection(r, s);
            if (result) {
                if (const Point* p = boost::get<Point>(&*result)) {
                    if (startToEnd) {
                        firstPointIntersection = Point(firstDefiningPoint.x(), firstDefiningPoint.y());
                        secondPointIntersection = Point(p->x(), p->y());
                    } else {
                        firstPointIntersection = Point(p->x(), p->y());
                    }
                }
            }
        }

        void setHandled(bool fromStart) {
            if (fromStart == true) {
                handledFromStart = true;
            } else {
                handledFromEnd = true;
            }
        }

        void unsetHandled() {
            handledFromStart = false;
            handledFromEnd = false;
        }

        bool wasHandled(bool fromStart) {
            if (fromStart == true) {
                return handledFromStart;
            } else {
                return handledFromEnd;
            }
        }
        void resetHandledFlag() {
            handledFromStart = false;
            handledFromEnd = false;
        }

    private:
        /**
         * The first point defining this event. For Path events it is the shortest path point
         * closer to the start point. For Boundary events it is the polygon vertex. For bend events
         * it is one of the intersections on the polygon boundary
         * @brief firstDefiningPoint
         */
        Point firstDefiningPoint;

        /**
         * The first point defining this event. For Path events it is the shortest path point
         * closer to the end point. For Boundary and bend events it is the vertex around which
         * the line of sight is rotated
         * @brief secondDefiningPoint
         */
        Point secondDefiningPoint;

        /**
         * The intersection on the polygon boundary closer to the first defining point
         * @brief firstPointIntersection
         */
        Point firstPointIntersection;

        /**
         * The intersection on the polygon boundary closer to the second defining point
         * @brief secondPointIntersection
         */
        Point secondPointIntersection;

        /**
          Indicates if the event was handled when traversing the polygon from start to end
         * @brief handledFromStart
         */
        bool handledFromStart = false;

        /**
          Indicates if the event was handled when traversing the polygon from end to start
         * @brief handledFromEnd
         */
        bool handledFromEnd = false;
    };
}

#endif // SHORTESTPATHMAP_H
