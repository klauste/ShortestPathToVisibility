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
    class GeometryUtil {
    public:

        // y grows towards bottom of screen so adjust checks
        bool isOnRightSide(Point p1, Point p2, Point p3) {
            Line l = Line(p1, p2);

            return l.has_on_positive_side(p3);
        }

        bool isOnLeftSide(Point p1, Point p2, Point p3) {
            Line l = Line(p1, p2);

            return l.has_on_negative_side(p3);
        }

        // y grows towards bottom of screen so adjust checks
        bool isOnRightSideOfPerpendicularLine(Line l, Point p1, Point p2) {
            Line p = l.perpendicular(p1);

            return p.has_on_negative_side(p2);
        }

        bool isOnLeftSideOfPerpendicularLine(Line l, Point p1, Point p2) {
            Line p = l.perpendicular(p1);

            return l.has_on_positive_side(p2);
        }

        bool pointsAreEqual(Point p1, Point p2) {
            return (
                abs(p1.x() - p2.x()) <= precision &&
                abs(p1.y() - p2.y()) <= precision
            );
        }

        Point getPerpendicularIntersectionPoint(Line l, Point p1) {
            Line p = l.perpendicular(p1);
            CGAL::cpp11::result_of<Intersect(Line, Line)>::type result = intersection(l, p);
            if (result) {
                if (const Point* p = boost::get<Point>(&*result)) {
                    return Point(p->x(), p->y());
                }
            }
            return p1;
        }

        boost::variant<Point, bool> getIntersectionBetweenLineAndSegment(Line l, Point p1, Point p2) {
            Segment s = Segment(p1, p2);

            CGAL::cpp11::result_of<Intersect(Line, Segment)>::type result = intersection(l, s);
            if (result) {
                if (const Point* p = boost::get<Point>(&*result)) {
                    return Point(p->x(), p->y());
                }
            }
            return false;
        }

        boost::variant<std::vector<Point>, bool> getCircleSegmentIntersection(Point center, Point pOnCircle, Point segStart, Point segEnd) {
            Pt2 centerPoint = Pt2(center.x(), center.y());
            Circ2 circle = Circ2(centerPoint, Segment(center, pOnCircle).squared_length());
            LineArc2 segment = LineArc2(Pt2(segStart.x(), segStart.y()), Pt2(segEnd.x(), segEnd.y()));

            std::vector<InterRes> result;
            CGAL::intersection(circle, segment, std::back_inserter(result));
            if (result.empty()) {
                return false;
            }

            std::vector<Point> pointVector;
            for (unsigned i = 0; i < result.size(); i++) {
                ResType pair = boost::get<ResType>(result.at(i));
                pointVector.push_back(Point(CGAL::to_double(pair.first.x()), CGAL::to_double(pair.first.y())));
            }
            if (pointVector.empty()) {
                return false;
            }
            return pointVector;
        }

        // This function creates a polygon around Segment s given the precision and checks if Point
        // p is contained in that polygon
        bool isPointOnSegment(Segment s, Point p) {
            Polygon supportingPolygon;
            Line supportingLine = s.supporting_line();
            std::pair<Point, Point> sourcePoints = getPerpendicularCircleIntersections(s.source(), s);
            std::pair<Point, Point> targetPoints = getPerpendicularCircleIntersections(s.target(), s);

            if (supportingLine.has_on_negative_side(sourcePoints.first)) {
                supportingPolygon.push_back(sourcePoints.first);
                supportingPolygon.push_back(sourcePoints.second);
            } else {
                supportingPolygon.push_back(sourcePoints.second);
                supportingPolygon.push_back(sourcePoints.first);
            }
            if (supportingLine.has_on_negative_side(targetPoints.first)) {
                supportingPolygon.push_back(targetPoints.second);
                supportingPolygon.push_back(targetPoints.first);
            } else {
                supportingPolygon.push_back(targetPoints.first);
                supportingPolygon.push_back(targetPoints.second);
            }
            return supportingPolygon.has_on_bounded_side(p);
        }

    private:
        double precision = 0.0001;
        std::pair<Point, Point> getPerpendicularCircleIntersections(Point centerPoint, Segment &s) {
            Pt2 source = Pt2(s.source().x(), s.source().y());
            Pt2 target = Pt2(s.target().x(), s.target().y());
            CircLine l = CircLine(source, target);
            Pt2 centerPointPt2 = Pt2(centerPoint.x(), centerPoint.y());
            CircLine perpLine = l.perpendicular(centerPointPt2);
            double squaredRadius = (precision / 2) * (precision / 2);
            Circ2 circle = Circ2(centerPointPt2, squaredRadius);
            std::vector<InterRes> result;
            CGAL::intersection(circle, perpLine, std::back_inserter(result));
            Point p1, p2;

            for (unsigned i = 0; i < result.size(); i++) {
                ResType pair = boost::get<ResType>(result.at(i));
                if (i == 0) {
                    p1 = Point(CGAL::to_double(pair.first.x()), CGAL::to_double(pair.first.y()));
                } else {
                    p2 = Point(CGAL::to_double(pair.first.x()), CGAL::to_double(pair.first.y()));
                }
            }
            return std::make_pair(p1, p2);
        }
    };
}
#endif // SPVGEOMETRYUTIL_H
