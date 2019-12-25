#ifndef BENDEVENTCALCULATOR_H
#define BENDEVENTCALCULATOR_H

#include "Events/baseeventcalculator.h"

namespace SPV {
    class BendEventCalculator : public BaseEventCalculator {
    public:
        BendEventCalculator(EventSegment *fS, const std::vector<PointOnShortestPath* > &sP) {
            firstEventSegment = fS;
            shortestPath = sP;
        }

        void calculateBendEvents();

    private:
        void calculateEventsForCurrentEventSegment();

        /**
         * @brief getNextDegenerateBendEvent
         * This function checks if there is a degenerate bend event on the current edge defined by the
         * two intersection events. If there isn't, false is returned. If there are degenerate events, the
         * degenerate event closer to ei1 is returned.
         * @param onStartSide
         * @return
         */
        boost::variant<Point, bool> getNextDegenerateBendEvent();
        void handlePathOrBoundaryEvent();
        void handleBoundaryEvent(EventSegment *previousEventSegment);
        void handlePathEvent(EventSegment *previousEventSegment);
        bool handleBendEventsWithPointAddition();
        bool handleBendEventsWithPointLoss();
        void addNewEventSegment(Point eventPoint);
        void handleDegenerateBendEvent(Point eventPoint);

        bool calculateEventsOnStartSide;
        void setCurrentSegmentOrderFromLeftToRight();
        Point getLastPointOnShortestPath(EventSegment *eS, bool onStartSide) {
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

        void addPreviousSettingsToCurrentES(EventSegment *previousEventSegment, bool pointsOnly);
    };
}

#endif // BENDEVENTCALCULATOR_H
