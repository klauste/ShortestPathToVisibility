#ifndef MINMAXCALCULATOR_H
#define MINMAXCALCULATOR_H
#include <vector>
#include <CGAL/squared_distance_2.h>
#include <math.h>
#include "Models/eventsegment.h"
#include "Models/minimum.h"
#include "Minima/abstractmincalculator.h"

namespace SPV {
    class MinMaxCalculator : public AbstractMinimumCalculator {
        public:
            MinMaxCalculator (const Polygon &p, Point s, Point e) :
                AbstractMinimumCalculator (p, s, e) {}
            void calculateMinima();

        private:
            bool isMinimumInCurrentSegment();
            void handleMinimum();
            bool handleMinimumAtPivotPoint();
            void findInnerMinimum(
                    Point firstPointOnStartSide,
                    Point secondPointOnStartSide,
                    Point firstPointOnEndSide,
                    Point secondPointOnEndSide
            );
    };
}
#endif // MINMAXCALCULATOR_H
