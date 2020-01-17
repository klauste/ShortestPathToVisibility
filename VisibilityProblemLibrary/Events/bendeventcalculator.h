#ifndef BENDEVENTCALCULATOR_H
#define BENDEVENTCALCULATOR_H

#include "basecalculator.h"

namespace SPV {
    class BendEventCalculator : public BaseCalculator {
    public:
        BendEventCalculator(EventSegment *fS, const std::vector<PointOnShortestPath* > &sP) {
            firstEventSegment = fS;
            shortestPath = sP;
        }
        ~BendEventCalculator()
        {
            EventSegment *nextSegment = firstEventSegment;
            EventSegment *currentSegment = firstEventSegment;

            bool allDestroyed = false;
            while(!allDestroyed) {
                currentSegment = nextSegment;
                if (!currentSegment->hasSuccessor()) {
                    allDestroyed = true;
                } else {
                    nextSegment = currentSegment->getSuccessor();
                }
            }
            delete currentSegment;
        }

        void calculateBendEvents();

    private:
        void calculateEventsForCurrentEventSegment();
        void setFirstEventEndSideDegenerateInformation();

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
        bool handleBendEventWithPointAddition(bool checkSegmentStartOnly);
        bool handleBendEventWithPointLoss(bool checkSegmentStartOnly);
        void addNewEventSegment(Point eventPoint);
        void handleDegenerateBendEvent(Point eventPoint);
        void handleDegenerateBendEventForSegmentStart();
        void handleSegmentToProtrudingVertex(EventSegment *previousEventSegment);
        void setDistanceToLastVertex();

        bool calculateEventsOnStartSide;
        void setCurrentSegmentOrderFromLeftToRight();
        void addPreviousSettingsToCurrentES(EventSegment *previousEventSegment, bool pointsOnly);
    };
}

#endif // BENDEVENTCALCULATOR_H
