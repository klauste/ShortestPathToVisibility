#ifndef SPVMINIMUMCALCULATORMINMAX_H
#define SPVMINIMUMCALCULATORMINMAX_H

#include "spvminimumcalculator.h"

namespace SPV {
    class MinimumCalculatorMinMax: public MinimumCalculator {
    public:
        using MinimumCalculator::MinimumCalculator;
    protected:
        void calculateMinimumBetween2Events (
            EventIntersection *firstIntersection,
            EventIntersection *secondIntersection,
            unsigned pivotPointIndex,
            bool goLeft
        );
    };
}
#endif // SPVMINIMUMCALCULATORMINMAX_H
