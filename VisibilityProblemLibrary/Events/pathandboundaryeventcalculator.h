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
#include "Events/baseeventcalculator.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Line_2 Line;

namespace SPV {
    class PathAndBoundaryEventCalculator : public BaseEventCalculator
    {
    public:
        PathAndBoundaryEventCalculator(const std::vector<PointOnShortestPath* > &sP) {
            shortestPath = sP;
        }

        void calculateEvents();

        // Move to private after testing
        std::vector<SweptSegment *> getSegmentsForFinalPoint(bool forFirstPoint);
        void setCurrentSegmentOrderFromLeftToRightFromOutside(bool c)
        {
            currentSegmentOrderFromLeftToRight = c;
        }
        void calculatePathAndBoundaryEvents();

        EventSegment* getFirstEventSegment()
        {
            return firstEventSegment;
        }
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
            SweptSegment* startSideSegment,
            SweptSegment* endSideSegment,
            PointOnShortestPath *pivotPoint
        );
        EventSegmentCreationResult createBoundaryEventSegment(
            SweptSegment* startSideSegment,
            SweptSegment* endSideSegment,
            PointOnShortestPath *pivotPoint,
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
                PointOnShortestPath *pivotPoint
        );
        std::vector<EventSegment *> allEventSegments;
        void calculateBendEvents();
        void addStartEvent();
        std::vector<SweptSegment*> getStartSegmentsForLoop(
            const std::vector<SweptSegment* > &segments,
            unsigned i
        );
        std::vector<SweptSegment*> getEndSegmentsForLoop(
            const std::vector<SweptSegment* > &segments,
            unsigned i
        );
        void addSegment(SweptSegment *leftSegment, SweptSegment *rightSegment);
    };
}

#endif // PATHANDBOUNDARYEVENTCALCULATOR_H
