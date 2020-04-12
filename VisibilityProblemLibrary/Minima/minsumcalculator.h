#ifndef SPVMINSUMCALCULATOR_H
#define SPVMINSUMCALCULATOR_H

#include <vector>
#include <CGAL/squared_distance_2.h>
#include <math.h>
#include "Models/eventsegment.h"
#include "Models/minimum.h"
#include "Events/bendeventcalculator.h"

namespace SPV {
    class MinSumCalculator : public BendEventCalculator {
    public:
        MinSumCalculator (Polygon p, Point s, Point e);
        virtual ~MinSumCalculator() {}

        /**
         * @brief calculateMinima calculates the min-sum minima
         */
        void calculateMinima();

    private:
        /**
         * @brief handleLocalMinimaWithBothPathsFree handles local minima if the path to the line of sight is
         * not obstructed by a polygon edge on either side
         */
        void handleLocalMinimaWithBothPathsFree();

        /**
         * @brief handleLocalMinimaWithBothPathsBlocked handles local minima if the path to the line of sight
         * is obstructed by a polygon edge on both sides
         */
        void handleLocalMinimaWithBothPathsBlocked();

        /**
         * @brief handleLocalMinimaWithOnePathBlocked handles local minima if the path to the line of sight is obstructed
         * by a polygon edge on one side
         */
        void handleLocalMinimaWithOnePathBlocked();

        /**
         * @brief handleLocalMinimumAtPivotPoint handles a minimum at the pivot point
         * @return
         */
        bool handleLocalMinimumAtPivotPoint();
    };
}
#endif // MINSUMCALCULATOR_H
