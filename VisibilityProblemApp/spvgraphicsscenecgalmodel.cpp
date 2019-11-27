#include "spvgraphicsscenecgalmodel.h"

void SPV::SPVGraphicsSceneCGALModel::addSegment(const QPointF &start, const QPointF &end) {
    Point cgalStart = Point(start.x(), start.y());
    Point cgalEnd = Point(end.x(), end.y());
    polygon.push_back(cgalStart);
    segmentsAddedSoFar.push_back(Segment(cgalStart, cgalEnd));
}

bool SPV::SPVGraphicsSceneCGALModel::doSegmentsIntersect(const QPointF &start, const QPointF &end) {
    bool intersect = false;
    Point cgalStart = Point(start.x(), start.y());
    Point cgalEnd = Point(end.x(), end.y());
    Segment newSegment = Segment(cgalStart, cgalEnd);

    for (auto &currentSegment : segmentsAddedSoFar) {
        Point currentEndPoint = currentSegment.target();
        bool checkIntersect = currentEndPoint != cgalStart;

        if (checkIntersect && CGAL::do_intersect(currentSegment, newSegment)) {
            intersect = true;
            break;
        }
    }
    return intersect;
}

void SPV::SPVGraphicsSceneCGALModel::setPolylineStartPoint(const QPointF &qPoint) {
    polylineStartPoint = Point(qPoint.x(), qPoint.y());
}

bool SPV::SPVGraphicsSceneCGALModel::shouldClosePolyline(const QPointF &currentPoint) {
    Point currentCgalPoint = Point(currentPoint.x(), currentPoint.y());
    double distance = CGAL::squared_distance(currentCgalPoint, polylineStartPoint);

    return (distance < minSquaredDistanceToStartPoint);
}

void SPV::SPVGraphicsSceneCGALModel::closePolyline(const QPointF &lastPointAdded) {
    polygon.push_back(Point(lastPointAdded.x(), lastPointAdded.y()));
    polygon = Polygon();

    /*polygon.push_back(Point(104, 493));
    polygon.push_back(Point(269,484));
    polygon.push_back(Point(319, 347));
    polygon.push_back(Point(365, 523));
    polygon.push_back(Point(487,512));
    polygon.push_back(Point(500,236));
    polygon.push_back(Point(101,239));*/

    /*polygon.push_back(Point(104, 493));
    polygon.push_back(Point(269,484));
    polygon.push_back(Point(319, 347));
    polygon.push_back(Point(365, 523));
    polygon.push_back(Point(487,512));
    polygon.push_back(Point(500,236));
    polygon.push_back(Point(201,239));
    polygon.push_back(Point(202,422));
    polygon.push_back(Point(101,419));*/

    /*polygon.push_back(Point(125,469));
    polygon.push_back(Point(165,431));
    polygon.push_back(Point(181,451));
    polygon.push_back(Point(220,365));
    polygon.push_back(Point(253,427));
    polygon.push_back(Point(350,376));
    polygon.push_back(Point(346,269));
    polygon.push_back(Point(301,190));
    polygon.push_back(Point(206,170));
    polygon.push_back(Point(89,145));
    polygon.push_back(Point(90,258));
    polygon.push_back(Point(198,245));
    polygon.push_back(Point(274,286));
    polygon.push_back(Point(198,336));
    polygon.push_back(Point(115,363));*/

    polygon.push_back(Point(49,472));
    polygon.push_back(Point(108,401));
    polygon.push_back(Point(160,458));
    polygon.push_back(Point(245,353));
    polygon.push_back(Point(317,431));
    polygon.push_back(Point(411,290));
    polygon.push_back(Point(396,137));
    polygon.push_back(Point(334,160));
    polygon.push_back(Point(292,118));
    polygon.push_back(Point(240,182));
    polygon.push_back(Point(192,83));
    polygon.push_back(Point(87,140));
    polygon.push_back(Point(133,194));
    polygon.push_back(Point(171,142));
    polygon.push_back(Point(199,267));

    polygon.push_back(Point(284,165));

    polygon.push_back(Point(340,303));
    polygon.push_back(Point(234,292));
    polygon.push_back(Point(173,350));
    polygon.push_back(Point(122,294));
    polygon.push_back(Point(45,401));

    if (polygon.orientation() == -1) {
        polygon.reverse_orientation();
    }
    shortestPath.initialize(polygon);
    CDT cdt = shortestPath.getTriangulation();

    polygonGraphicItem = new PolygonGraphic(&polygon);
    polygonGraphicItem->setEdgesPen(QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    polygonGraphicItem->setVerticesPen(QPen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

PolygonGraphic* SPV::SPVGraphicsSceneCGALModel::getQtPolygon() {
    return polygonGraphicItem;
}

bool SPV::SPVGraphicsSceneCGALModel::isPointInPolygon(const QPointF &currentPoint) {
    Point pointToCheck = Point(currentPoint.x(), currentPoint.y());
    return (polygon.bounded_side(pointToCheck) == CGAL::ON_BOUNDED_SIDE);
}

void SPV::SPVGraphicsSceneCGALModel::addPairPoint(const QPointF &currentPoint, int index) {
    if (index >= 0 && index < 2) {
        shortestPath.setPoint(index, currentPoint.x(), currentPoint.y());
    }
}

void SPV::SPVGraphicsSceneCGALModel::calculateShortestPath() {
    shortestPath.calculateShortestPath();
}
