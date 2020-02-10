#ifndef BASECALCULATOR_H
#define BASECALCULATOR_H
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include "Models/eventsegment.h"
#include "Models/pointonshortestpath.h"
#include "Models/sweptsegment.h"
#include "Utils/geometryutil.h"
#include "Models/lineofsight.h"
#include "ShortestPath/shortestpathtreecalculator.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Line_2 Line;

namespace SPV {
    class BaseCalculator
    {
    public:
        BaseCalculator(const Polygon &p, const Point s, Point e) {
            std::unique_ptr<ShortestPathTreeCalculator> spt = std::unique_ptr<ShortestPathTreeCalculator>(new ShortestPathTreeCalculator(p, s, e));
            shortestPath = spt->getShortestPath();
        }

        EventSegment* getFirstEventSegment()
        {
            return firstEventSegment;
        }

        const std::vector<std::shared_ptr<PointOnShortestPath>> getShortestPath()
        {
            return shortestPath;
        }

        Point getLastPointBeforeLoS(EventSegment *eS, bool onStartSide) {
            std::vector<Point> extraPoints;
            if (onStartSide) {
                extraPoints = eS->getExtraPointsOnStartSide();
                if (extraPoints.size() > 0) {
                    return extraPoints.at(extraPoints.size() - 1);
                }
                return shortestPath.at(eS->getIndexOfLastSPPointOnStartSide())->getPoint();
            }
            extraPoints = eS->getExtraPointsOnEndSide();
            if (extraPoints.size() > 0) {
                return extraPoints.at(extraPoints.size() - 1);
            }
            return shortestPath.at(eS->getIndexOfLastSPPointOnEndSide())->getPoint();
        }

    protected:
        std::vector<std::shared_ptr<PointOnShortestPath>> shortestPath;
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
#endif // BASECALCULATOR_H
