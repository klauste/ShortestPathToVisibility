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
            double temp = p1.x() - p2.x();
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

        boost::variant<Point, bool> getIntersectionBetweenLineAndLine(Line l, Point p1, Point p2) {
            Line newL = Line(p1, p2);

            CGAL::cpp11::result_of<Intersect(Line, Line)>::type result = intersection(l, newL);
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

        boost::variant<std::vector<Point>, bool> getCircleLineIntersection(Point center, Point pOnCircle, Point lineFirstPoint, Point lineSecondPoint) {
            Pt2 centerPoint = Pt2(center.x(), center.y());
            Circ2 circle = Circ2(centerPoint, Segment(center, pOnCircle).squared_length());
            CircLine line = CircLine(Pt2(lineFirstPoint.x(), lineFirstPoint.y()), Pt2(lineSecondPoint.x(), lineSecondPoint.y()));

            std::vector<InterRes> result;
            CGAL::intersection(circle, line, std::back_inserter(result));
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

        bool isPerpendicularFootObstructedByEdge(Point segmentStart, Point segmentEnd, Point pivotPoint) {
            Line lineFromStartToPp = Line(segmentStart, pivotPoint);
            Line orthogonalLine = lineFromStartToPp.perpendicular(segmentStart);

            if (orthogonalLine.has_on(segmentEnd)) {
                return true;
            }
            return (orthogonalLine.has_on_positive_side(segmentEnd) == orthogonalLine.has_on_positive_side(pivotPoint));
        }

        bool isEdgeVisibleFromLastPoint(Point lastPointOnPath, Point edgeStart, Point edgeEnd, Point pivotPoint) {
            Line lineFromLastPointToEdgeStart = Line(lastPointOnPath, edgeStart);

            // The edge end point should not be on the line, but check anyway
            if (lineFromLastPointToEdgeStart.has_on(edgeEnd)) {
                return true;
            }
            return (lineFromLastPointToEdgeStart.has_on_positive_side(edgeEnd) == lineFromLastPointToEdgeStart.has_on_positive_side(pivotPoint));
        }

        bool isPerpendicularFootObstructedAtBoundaryVertex(Point lastPointOnPath, Point boundaryVertex, Point pivotPoint) {
            Line lineFromStartToPp = Line(boundaryVertex, pivotPoint);
            Line orthogonalLine = lineFromStartToPp.perpendicular(lastPointOnPath);

            return (orthogonalLine.has_on_positive_side(boundaryVertex) == orthogonalLine.has_on_positive_side(pivotPoint));
        }

        bool isPerpendicularFootOnVertex(Point lastPointOnPath, Point boundaryVertex, Point pivotPoint) {
            Line lineFromVertexToPp = Line(boundaryVertex, pivotPoint);
            Point perpIntersection = getPerpendicularIntersectionPoint(lineFromVertexToPp, lastPointOnPath);

            return pointsAreEqual(perpIntersection, boundaryVertex);
        }

        bool isEdgeWithStartPointOnCircleObstructingShortestPath(Point lastPointOnPath, Point edgeStart, Point edgeEnd, Point pivotPoint) {
            Point centerPoint = Point((lastPointOnPath.x() + pivotPoint.x()) / 2, (lastPointOnPath.y() + pivotPoint.y()) / 2);
            boost::variant<std::vector<Point>, bool> result = getCircleLineIntersection(centerPoint, edgeStart, edgeStart, edgeEnd);
            Line lastPointToPivot = Line(lastPointOnPath, pivotPoint);

            // If there are no intersections, there is no obstruction
            if (result.type() == typeid(bool)) {
                return false;
            }

            std::vector<Point> iSPoints = boost::get<std::vector<Point>>(result);

            if (iSPoints.size() == 1) {
                Point iPoint = iSPoints.at(0);
                if (pointsAreEqual(iPoint, edgeStart)) {
                    return false;
                }

                // If the intersection point is not the edge start point, the edge obstructs the view,
                // if the intersection is in the same half plane as the edge start point
                return (lastPointToPivot.has_on_positive_side(iPoint) == lastPointToPivot.has_on_positive_side(edgeStart));
            }

            // If two intersections are found, the edge obstructs the view if both of them are in the same half-plane
            return (
                lastPointToPivot.has_on_positive_side(iSPoints.at(0)) == lastPointToPivot.has_on_positive_side(iSPoints.at(1))
            );
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
