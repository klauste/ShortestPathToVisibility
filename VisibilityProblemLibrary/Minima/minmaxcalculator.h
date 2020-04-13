#ifndef MINMAXCALCULATOR_H
#define MINMAXCALCULATOR_H
#include <vector>
#include <CGAL/squared_distance_2.h>
#include <math.h>
#include "Models/eventsegment.h"
#include "Models/minimum.h"
#include "Events/bendeventcalculator.h"

namespace SPV {
    class MinMaxCalculator : public BendEventCalculator {
        public:
            MinMaxCalculator (Polygon p, Point s, Point e);
            virtual ~MinMaxCalculator() {}

            /**
             * @brief calculateMinima calculates the min-max minima
             */
            void calculateMinima();

        private:
            /**
             * @brief isMinimumInCurrentSegment checks if the minimum is in the current event segment
             * @return
             */
            bool isMinimumInCurrentSegment();

            /**
             * @brief handleMinimum handles a minimum
             */
            void handleMinimum();

            /**
             * Checks if the there is a sudden change in the distance, when moving from
             * one event segment to the other. If there is and the minimum is within that
             * distance change, handle the minimum and return true. Otherwise return false.
             * @brief handleMinimumWithSuddenDistanceChange
             * @return
             */
            bool handleMinimumWithSuddenDistanceChange();

            /**
             * @brief handleMinimumAtPivotPoint handles a minimum at a pivot point
             * @return
             */
            bool handleMinimumAtPivotPoint();

            /**
             * @brief findInnerMinimum finds a minimum between the start and end line of sight of an event
             * segments
             * @param firstPointOnStartSide
             * @param secondPointOnStartSide
             * @param firstPointOnEndSide
             * @param secondPointOnEndSide
             */
            void findInnerMinimum(
                    Point firstPointOnStartSide,
                    Point secondPointOnStartSide,
                    Point firstPointOnEndSide,
                    Point secondPointOnEndSide
            );
    };
}
#endif // MINMAXCALCULATOR_H
