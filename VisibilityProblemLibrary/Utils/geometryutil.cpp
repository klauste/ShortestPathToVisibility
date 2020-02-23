#include "Utils/geometryutil.h"

SPV::GeometryUtil::GeometryUtil()
{
    precision = 0.0001;
}

bool SPV::GeometryUtil::isOnRightSide(Point p1, Point p2, Point p3) {
    Line l = Line(p1, p2);

    return l.has_on_positive_side(p3);
}

bool SPV::GeometryUtil::isOnLeftSide(Point p1, Point p2, Point p3) {
    Line l = Line(p1, p2);

    return l.has_on_negative_side(p3);
}

bool SPV::GeometryUtil::pointsAreEqual(Point p1, Point p2) {
    return (
        abs(p1.x() - p2.x()) <= precision &&
        abs(p1.y() - p2.y()) <= precision
    );
}

bool SPV::GeometryUtil::valuesAreEqual(double d1, double d2) {
    double diff = d1 - d2;

    return (abs(diff) <= precision);
}

bool SPV::GeometryUtil::valuesAreEqualHighPrecision(double d1, double d2) {
    double diff = d1 - d2;

    return (abs(diff) <= (precision * 0.01));
}

bool SPV::GeometryUtil::isLarger(double d1, double d2)
{
    double diff = d1 -d2;

    return diff > precision;
}

bool SPV::GeometryUtil::isLargerOrEqual(double d1, double d2)
{
    if (valuesAreEqual(d1, d2)) {
        return true;
    }
    return isLarger(d1, d2);
}

Point SPV::GeometryUtil::getPerpendicularIntersectionPoint(Line l, Point p1) {
    Line p = l.perpendicular(p1);
    CGAL::cpp11::result_of<Intersect(Line, Line)>::type result = intersection(l, p);
    if (result) {
        if (const Point* p = boost::get<Point>(&*result)) {
            return Point(p->x(), p->y());
        }
    }
    return p1;
}

boost::variant<Point, bool> SPV::GeometryUtil::getIntersectionBetweenLineAndSegment(Line l, Point p1, Point p2) {
    Segment s = Segment(p1, p2);

    CGAL::cpp11::result_of<Intersect(Line, Segment)>::type result = intersection(l, s);
    if (result) {
        if (const Point* p = boost::get<Point>(&*result)) {
            return Point(p->x(), p->y());
        }
    }
    return false;
}

boost::variant<Point, bool> SPV::GeometryUtil::getIntersectionBetweenSegmentAndSegment(Segment s, Point p1, Point p2) {
    Segment s1 = Segment(p1, p2);

    CGAL::cpp11::result_of<Intersect(Line, Segment)>::type result = intersection(s, s1);
    if (result) {
        if (const Point* p = boost::get<Point>(&*result)) {
            return Point(p->x(), p->y());
        }
    }
    return false;
}

boost::variant<Point, bool> SPV::GeometryUtil::getIntersectionBetweenLineAndLine(Line l, Point p1, Point p2) {
    Line newL = Line(p1, p2);

    CGAL::cpp11::result_of<Intersect(Line, Line)>::type result = intersection(l, newL);
    if (result) {
        if (const Point* p = boost::get<Point>(&*result)) {
            return Point(p->x(), p->y());
        }
    }
    return false;
}

boost::variant<std::vector<Point>, bool> SPV::GeometryUtil::getCircleSegmentIntersection(Point center, Point pOnCircle, Point segStart, Point segEnd) {
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

boost::variant<std::vector<Point>, bool> SPV::GeometryUtil::getCircleLineIntersection(Point center, Point pOnCircle, Point lineFirstPoint, Point lineSecondPoint) {
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
bool SPV::GeometryUtil::isPointOnSegment(Segment s, Point p) {
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

bool SPV::GeometryUtil::isPerpendicularFootObstructedByEdge(Point segmentStart, Point segmentEnd, Point pivotPoint) {
    Line lineFromStartToPp = Line(segmentStart, pivotPoint);
    Line orthogonalLine = lineFromStartToPp.perpendicular(segmentStart);

    // If the end point on the segment is on the orthogonal line, then
    // on the direct path to the LoS is visible
    if (orthogonalLine.has_on(segmentEnd)) {
        return false;
    }
    return (orthogonalLine.has_on_positive_side(segmentEnd) == orthogonalLine.has_on_positive_side(pivotPoint));
}

bool SPV::GeometryUtil::isEdgeVisibleFromLastPoint(Point lastPointOnPath, Point edgeStart, Point edgeEnd, Point pivotPoint) {
    Line lineFromLastPointToEdgeStart = Line(lastPointOnPath, edgeStart);

    // The edge end point should not be on the line, but check anyway
    if (lineFromLastPointToEdgeStart.has_on(edgeEnd)) {
        return true;
    }
    return (lineFromLastPointToEdgeStart.has_on_positive_side(edgeEnd) == lineFromLastPointToEdgeStart.has_on_positive_side(pivotPoint));
}

bool SPV::GeometryUtil::isPerpendicularFootObstructedAtBoundaryVertex(Point lastPointOnPath, Point boundaryVertex, Point pivotPoint) {
    Line lineFromStartToPp = Line(boundaryVertex, pivotPoint);
    Line orthogonalLine = lineFromStartToPp.perpendicular(lastPointOnPath);

    return (orthogonalLine.has_on_positive_side(boundaryVertex) == orthogonalLine.has_on_positive_side(pivotPoint));
}

bool SPV::GeometryUtil::isPerpendicularFootOnVertex(Point lastPointOnPath, Point boundaryVertex, Point pivotPoint) {
    Line lineFromVertexToPp = Line(boundaryVertex, pivotPoint);
    Point perpIntersection = getPerpendicularIntersectionPoint(lineFromVertexToPp, lastPointOnPath);

    return pointsAreEqual(perpIntersection, boundaryVertex);
}

bool SPV::GeometryUtil::isEdgeWithStartPointOnCircleObstructingShortestPath(Point lastPointOnPath, Point edgeStart, Point edgeEnd, Point pivotPoint) {
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

std::pair<Point, Point> SPV::GeometryUtil::getPerpendicularCircleIntersections(Point centerPoint, Segment &s) {
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
