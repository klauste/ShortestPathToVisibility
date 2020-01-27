#ifndef SPVMINSUMCALCULATOR_H
#define SPVMINSUMCALCULATOR_H

#include <vector>
#include <CGAL/squared_distance_2.h>
#include <math.h>
#include "Models/eventsegment.h"
#include "Models/minimum.h"
#include "Minima/abstractmincalculator.h"

namespace SPV {
    class MinSumCalculator : public AbstractMinimumCalculator {
    public:
        MinSumCalculator (const Polygon &p, Point s, Point e) :
            AbstractMinimumCalculator (p, s, e) {}
        void calculateMinima();

    private:
        void handleLocalMinimaWithBothPathsFree();
        void handleLocalMinimaWithBothPathsBlocked();
        void handleLocalMinimaWithOnePathBlocked();
        bool handleLocalMinimumAtPivotPoint();
        Point getFurthestPointOnBoundary(bool onStartSide, bool firstLoS);
    };
}
#endif // MINSUMCALCULATOR_H
