#ifndef BASEEVENTCALCULATOR_H
#define BASEEVENTCALCULATOR_H
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include "Models/eventsegment.h"
#include "Models/pointonshortestpath.h"
#include "Models/sweptsegment.h"
#include "Utils/geometryutil.h"
#include "Models/lineofsight.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Line_2 Line;

namespace SPV {
    class BaseEventCalculator
    {

    protected:
        std::vector<PointOnShortestPath *> shortestPath;
        bool currentSegmentOrderFromLeftToRight = true;
        EventSegment *currentEventSegment;
        EventSegment *firstEventSegment;
        GeometryUtil gU = GeometryUtil();

        bool isSegmentOrderFromLeftToRight(unsigned index) {
            Point previousPoint = shortestPath.at(index - 1)->getPoint();
            Point currentPoint = shortestPath.at(index)->getPoint();
            Point nextPoint = shortestPath.at(index + 1)->getPoint();

            // If the next point is on the right of the line through the previous and current point,
            // then the segments are swept from left to right
            return gU.isOnRightSide(previousPoint, currentPoint, nextPoint);
        }
    };
}
#endif // BASEEVENTCALCULATOR_H
