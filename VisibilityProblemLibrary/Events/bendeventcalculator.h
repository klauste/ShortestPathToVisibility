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
        void calculateEventsBetween2Events ();

        /**
         * @brief getNextDegenerateBendEvent
         * This function checks if there is a degenerate bend event on the current edge defined by the
         * two intersection events. If there isn't, false is returned. If there are degenerate events, the
         * degenerate event closer to ei1 is returned.
         * @param onStartSide
         * @return
         */
        boost::variant<Point, bool> getNextDegenerateBendEvent(
            bool onStartSide
        );
        void handlePathOrBoundaryEvents(
                bool onStartSide
        );
        void handleBendEventsWithPointAddition(
                bool onStartSide
        );
        void handleBendEventsWithPointLoss(
                bool onStartSide
        );

        // This function checks if the shortest path to the line of sight in this event segment starts on the polygon edge
        bool doesShortestPathStartOnEdge(bool onStartSide);
    };
}

#endif // BENDEVENTCALCULATOR_H
