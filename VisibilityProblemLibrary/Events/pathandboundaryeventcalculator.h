#ifndef PATHANDBOUNDARYEVENTCALCULATOR_H
#define PATHANDBOUNDARYEVENTCALCULATOR_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>
#include "Models/eventsegment.h"
#include "Models/pointonshortestpath.h"
#include "Models/sweptsegment.h"
#include "Utils/geometryutil.h"
#include "Models/lineofsight.h"
#include "basecalculator.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Line_2 Line;

namespace SPV {
    class PathAndBoundaryEventCalculator : public BaseCalculator
    {
    public:
        PathAndBoundaryEventCalculator (const Polygon &p, Point s, Point e) :
            BaseCalculator (p, s, e) {}
        ~PathAndBoundaryEventCalculator()
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

        // Move to private after testing
        std::vector<std::shared_ptr<SweptSegment>> getSegmentsForFinalPoint(bool forFirstPoint);
        void setCurrentSegmentOrderFromLeftToRight(bool c)
        {
            currentSegmentOrderFromLeftToRight = c;
        }
        void calculatePathAndBoundaryEvents();
    private:
        struct EventSegmentCreationResult {
            EventSegmentCreationResult () {}
            EventSegmentCreationResult (EventSegment *eS, bool sE, bool eE) :
                newEventSegment(eS),
                startSideIsEndOfSegment(sE),
                endSideIsEndOfSegment(eE) {}
            EventSegment *newEventSegment;
            bool startSideIsEndOfSegment;
            bool endSideIsEndOfSegment;
        };
        EventSegmentCreationResult createPathEventSegment(
            std::shared_ptr<SweptSegment> startSideSegment,
            std::shared_ptr<SweptSegment> endSideSegment,
            std::shared_ptr<PointOnShortestPath> pivotPoint
        );
        EventSegmentCreationResult createBoundaryEventSegment(
            std::shared_ptr<SweptSegment> startSideSegment,
            std::shared_ptr<SweptSegment> endSideSegment,
            std::shared_ptr<PointOnShortestPath> pivotPoint,
            bool endOfSegmentReached,
            bool endOfEndSegmentReached
        );
        EventSegmentCreationResult createEventSegment(
                Point firstStartPoint,
                bool firstStartPointIsVertex,
                Point firstEndPoint,
                bool firstEndPointIsVertex,
                Point secondStartPoint,
                bool secondStartPointIsVertex,
                Point secondEndPoint,
                bool secondEndPointIsVertex,
                std::shared_ptr<PointOnShortestPath> pivotPoint,
                EventType t
        );
        std::vector<std::shared_ptr<SweptSegment>> getStartSegmentsForLoop(
            const std::vector<std::shared_ptr<SweptSegment>> &segments,
            unsigned i
        );
        std::vector<std::shared_ptr<SweptSegment>> getEndSegmentsForLoop(
            const std::vector<std::shared_ptr<SweptSegment>> &segments,
            unsigned i
        );
    };
}

#endif // PATHANDBOUNDARYEVENTCALCULATOR_H
