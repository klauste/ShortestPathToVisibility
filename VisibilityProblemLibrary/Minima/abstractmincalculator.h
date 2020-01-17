#ifndef ABSTRACTMINCALCULATOR_H
#define ABSTRACTMINCALCULATOR_H
#include <vector>
#include <CGAL/squared_distance_2.h>
#include <math.h>
#include "Models/eventsegment.h"
#include "Models/minimum.h"
#include "basecalculator.h"

namespace SPV {
    class AbstractMinimumCalculator : public BaseCalculator {
    public:
        AbstractMinimumCalculator(EventSegment *fS, std::vector<PointOnShortestPath *> sP) {
            shortestPath = sP;
            firstEventSegment = fS;
        }
        virtual void calculateMinima() = 0;
        std::vector<Minimum*> getAllMinima() {
            return allMinima;
        }

    protected:
        std::vector<Minimum*> allMinima;
        double currentMinimum = -1;
        double getDistanceToIntersectionPoint(Point intersectionPoint, bool onStartSide)
        {
            Point lastPointOnPath = getLastPointOnShortestPath(currentEventSegment, onStartSide);

            return sqrt(CGAL::squared_distance(lastPointOnPath, intersectionPoint));
        }

        Point getIntersectionPointOnLoS(Point intersectionPointOnBoundary, bool onStartSide)
        {
            Point lastPointOnPath = getLastPointOnShortestPath(currentEventSegment, onStartSide);
            Point pivotPoint = currentEventSegment->getPivotPoint()->getPoint();

            // If the last point on the path is the pivotPoint, return that as intersection
            if (gU.pointsAreEqual(lastPointOnPath, pivotPoint)) {
                return pivotPoint;
            }

            // If the last point on the path is on the LoS return the last point on the path
            if (gU.isPointOnSegment(Segment(intersectionPointOnBoundary, pivotPoint), lastPointOnPath)) {
                return lastPointOnPath;
            }

            if (!currentEventSegment->isLoSVisible(onStartSide)) {
                return intersectionPointOnBoundary;
            }

            return gU.getPerpendicularIntersectionPoint(Line(intersectionPointOnBoundary, pivotPoint), lastPointOnPath);
        }

        void handleNewGlobalMinimum (
            double newMinimumValue,
            Point startSideIntersectionOnLoS,
            Point endSideIntersectionOnLoS,
            Point startSideIntersectionOnEdge,
            Point endSideIntersectionOnEdge,
            bool calculateMinimumSector = false
        )
        {
            if (currentMinimum >= 0 && gU.isLarger(newMinimumValue, currentMinimum)) {
                return;
            }

            if (currentMinimum < 0) {
                currentMinimum = newMinimumValue;
            }

            if (gU.isLarger(currentMinimum, newMinimumValue)) {
                currentMinimum = newMinimumValue;

                if (allMinima.size() > 0) {
                    allMinima.clear();
                }
            }

            bool isMinSectorStart = calculateMinimumSector;
            bool isMinSectorEnd = false;
            if (allMinima.size() > 0) {
                Minimum *lastMin = allMinima.back();

                // If this is a duplicate, then there is nothing to do
                if (gU.pointsAreEqual(lastMin->getStartSideIntersectionOnLoS(), startSideIntersectionOnLoS)) {
                    return;
                }
                if (calculateMinimumSector) {
                    // If the last minimum was the sector start, this minimum should be the sector end
                    if (lastMin->isMinSectorStart()) {
                        isMinSectorStart = false;
                        isMinSectorEnd = true;
                    // If the last minium was the sector end, reset it
                    } else if (lastMin->isMinSectorEnd()) {
                        setMinimumDetails(
                            lastMin,
                            newMinimumValue,
                            startSideIntersectionOnLoS,
                            endSideIntersectionOnLoS,
                            startSideIntersectionOnEdge,
                            endSideIntersectionOnEdge,
                            false,
                            true
                        );
                        return;
                    }
                }
            }
            Minimum *newMinimum = new Minimum();
            setMinimumDetails(
                newMinimum,
                newMinimumValue,
                startSideIntersectionOnLoS,
                endSideIntersectionOnLoS,
                startSideIntersectionOnEdge,
                endSideIntersectionOnEdge,
                isMinSectorStart,
                isMinSectorEnd
            );
            allMinima.push_back(newMinimum);
        }
        double stepPrecision = 0.001;

    private:
        void setMinimumDetails(
            Minimum *min,
            double newMinimumValue,
            Point startSideIntersectionOnLoS,
            Point endSideIntersectionOnLoS,
            Point startSideIntersectionOnEdge,
            Point endSideIntersectionOnEdge,
            bool isMinSectorStart,
            bool isMinSectorEnd
        )
        {
            min->setEventSegment(currentEventSegment);
            min->setDistance(newMinimumValue);
            min->setStartSideIntersectionOnLoS(startSideIntersectionOnLoS);
            min->setEndSideIntersectionOnLoS(endSideIntersectionOnLoS);
            min->setStartSideIntersectionOnEdge(startSideIntersectionOnEdge);
            min->setEndSideIntersectionOnEdge(endSideIntersectionOnEdge);
            min->setDistance(currentMinimum);
            min->setMinSectorStart(isMinSectorStart);
            min->setMinSectorEnd(isMinSectorEnd);
        }
    };
}
#endif // ABSTRACTMINCALCULATOR_H
