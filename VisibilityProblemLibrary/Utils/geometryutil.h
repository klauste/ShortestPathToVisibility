#ifndef SPVGEOMETRYUTIL_H
#define SPVGEOMETRYUTIL_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/intersections.h>
#include <CGAL/result_of.h>
#include <CGAL/iterator.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/Polygon_2.h>
#include <boost/bind.hpp>
#include <iterator>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Line_2 Line;
typedef CGAL::Polygon_2<K> Polygon;
typedef K::Segment_2 Segment;
typedef CGAL::Exact_circular_kernel_2        CircK;
typedef CGAL::Point_2<CircK>                 Pt2;
typedef CGAL::Circle_2<CircK>                Circ2;
typedef CGAL::Line_arc_2<CircK>              LineArc2;
typedef CGAL::Line_2<CircK>                  CircLine;
typedef std::pair<CGAL::Circular_arc_point_2<CircK>, unsigned> ResType;
typedef boost::variant<ResType> InterRes;
typedef K::Intersect_2 Intersect;

namespace SPV {
    /**
     * @brief The GeometryUtil class contains static functions which are needed in
     * the calculation of the minima
     */
    class GeometryUtil {
    public:
        GeometryUtil();

        /**
         * @brief isOnRightSide determines if p3 is on the right side of the line through p1 and p2
         * @param p1
         * @param p2
         * @param p3
         * @return
         */
        bool isOnRightSide(Point p1, Point p2, Point p3);

        /**
         * @brief isOnLeftSide determines if p3 is on the left side of the line through p1 and p2
         * @param p1
         * @param p2
         * @param p3
         * @return
         */
        bool isOnLeftSide(Point p1, Point p2, Point p3);

        /**
         * @brief pointsAreEqual determines if p1 and p2 are close enough to be considered equal
         * @param p1
         * @param p2
         * @return
         */
        bool pointsAreEqual(Point p1, Point p2);

        /**
         * @brief valuesAreEqual determines if two double values are close enough to be considered equal
         * @param d1
         * @param d2
         * @return
         */
        bool valuesAreEqual(double d1, double d2);

        /**
         * @brief valuesAreEqualHighPrecision determins with high precision if two double values are close
         * enough to be considered equal
         * @param d1
         * @param d2
         * @return
         */
        bool valuesAreEqualHighPrecision(double d1, double d2) ;

        /**
         * @brief isLarger determines if d1 can be considered larger than d2
         * @param d1
         * @param d2
         * @return
         */
        bool isLarger(double d1, double d2);

        /**
         * @brief isLargerOrEqual determines if d1 can be considered larger or equal compared to d2
         * @param d1
         * @param d2
         * @return
         */
        bool isLargerOrEqual(double d1, double d2);

        /**
         * @brief getPerpendicularIntersectionPoint calculates the intersection point on l of the line
         * perpendicular to l through p1 with l
         * @param l
         * @param p1
         * @return
         */
        Point getPerpendicularIntersectionPoint(Line l, Point p1) ;

        /**
         * @brief getIntersectionBetweenLineAndSegment calculates the intersection between l and the segment
         * between p1 and p2
         * @param l
         * @param p1
         * @param p2
         * @return
         */
        boost::variant<Point, bool> getIntersectionBetweenLineAndSegment(Line l, Point p1, Point p2);

        /**
         * @brief getIntersectionBetweenLineAndLine calculates the intersection between l and the line
         * through p1 and p2
         * @param l
         * @param p1
         * @param p2
         * @return
         */
        boost::variant<Point, bool> getIntersectionBetweenLineAndLine(Line l, Point p1, Point p2);

        /**
         * @brief getCircleSegmentIntersection calculates the intersections between
         * the segement between segStart and segEnd and the circle centered in Point center and
         * the pOnCircle on the circle edge
         * @param center
         * @param pOnCircle
         * @param segStart
         * @param segEnd
         * @return the intersection points if there are any; false otherwise
         */
        boost::variant<std::vector<Point>, bool> getCircleSegmentIntersection(
                Point center,
                Point pOnCircle,
                Point segStart,
                Point segEnd
        );

        /**
         * @brief getCircleLineIntersection calculates the intersections between the line through
         * lineFirstPoint and lineSecondPoint and the circle centered in Point center and
         * the pOnCircle on the circle edge
         * @param center
         * @param pOnCircle
         * @param lineFirstPoint
         * @param lineSecondPoint
         * @return the intersection points if there are any; false otherwise
         */
        boost::variant<std::vector<Point>, bool> getCircleLineIntersection(
                Point center,
                Point pOnCircle,
                Point lineFirstPoint,
                Point lineSecondPoint
        );

        /**
         * @brief isPointOnSegment determines if p can be considered to part of s. It creates a polygon
         * around Segment s given the precision and checks if Point p is contained in that polygon
         * @param s
         * @param p
         * @return
         */
        bool isPointOnSegment(Segment s, Point p);

        /**
         * @brief isPerpendicularFootObstructedByEdge determines if the path from the last point
         * on the polygon to the Line of Sight between the pivot point and the segment start
         * ends on the segment or on the perpendicular foot on the line of sight in the interior of
         * the polygon.
         * @param segmentStart
         * @param segmentEnd
         * @param pivotPoint
         * @return
         */
        bool isPerpendicularFootObstructedByEdge(Point segmentStart, Point segmentEnd, Point pivotPoint);

        /**
         * @brief isEdgeVisibleFromLastPoint determines if the edge between edgeStart and edgeEnd is visible from
         * the last point on the path to a line of sight through the pivot point
         * @param lastPointOnPath
         * @param edgeStart
         * @param edgeEnd
         * @param pivotPoint
         * @return
         */
        bool isEdgeVisibleFromLastPoint(Point lastPointOnPath, Point edgeStart, Point edgeEnd, Point pivotPoint);

        /**
         * @brief isPerpendicularFootObstructedAtBoundaryVertex determines if a point on the polygon boundary
         * is located in such a way as to obstruct the direct path to a line of sight. If this is the case
         * the boundary point would have to be included in the shortest path to the minimum.
         * @param lastPointOnPath
         * @param boundaryVertex
         * @param pivotPoint
         * @return
         */
        bool isPerpendicularFootObstructedAtBoundaryVertex(
                Point lastPointOnPath,
                Point boundaryVertex,
                Point pivotPoint
        );

        /**
         * @brief isPerpendicularFootOnVertex checks if the intersection between the line through
         * pivotPoint and boundaryVertex and line perpendicular to that through lastPointOnPath
         * is the same as boundaryVertex
         * @param lastPointOnPath
         * @param boundaryVertex
         * @param pivotPoint
         * @return
         */
        bool isPerpendicularFootOnVertex(Point lastPointOnPath, Point boundaryVertex, Point pivotPoint);

        /**
         * @brief isEdgeWithStartPointOnCircleObstructingShortestPath if the circle with center beween lastPointOnPath
         * and pivotPoint intersects the edge in point edgeStart, this function determines, if the edge is obstructing
         * the direct path from lastPointOnPath to the line of sight
         * @param lastPointOnPath
         * @param edgeStart
         * @param edgeEnd
         * @param pivotPoint
         * @return
         */
        bool isEdgeWithStartPointOnCircleObstructingShortestPath(
                Point lastPointOnPath,
                Point edgeStart,
                Point edgeEnd,
                Point pivotPoint
        );
    private:
        /**
         * @brief precision determines the precision with which to perform calculations and comparisons
         */
        double precision;

        /**
         * @brief getPerpendicularCircleIntersections is a helper function for isPointOnSegment. It creates
         * a circle around centerPoint with a radius dependent on the precision. I then calculates the intersections
         * between the line through the centerpoint and perpendicular to s. Given the assumptions, there must always
         * be 2 intersections, which are returned as a pair of points. The point pair can be used as part of
         * the rectangle surrounding the segment which is used to determine if a point is located on the
         * segment.
         * @param centerPoint
         * @param s
         * @return
         */
        std::pair<Point, Point> getPerpendicularCircleIntersections(Point centerPoint, Segment &s);
    };
}
#endif // SPVGEOMETRYUTIL_H
