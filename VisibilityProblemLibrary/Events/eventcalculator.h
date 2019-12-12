#ifndef EVENTCALCULATOR_H
#define EVENTCALCULATOR_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>
#include "Models/event.h"
#include "Models/pointonshortestpath.h"
#include "Models/sweptsegment.h"
#include "Utils/geometryutil.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Line_2 Line;

namespace SPV {
    class EventCalculator
    {
    public:
        EventCalculator(const std::vector<PointOnShortestPath* > &sP) :
            shortestPath(sP)
        {}

        std::vector<Event *> calculateEvents();

        // Move to private after testing
        std::vector<SweptSegment *> getSegmentsForFinalPoint(bool forFirstPoint);
        void setCurrentSegmentOrderFromLeftToRight(bool c)
        {
            currentSegmentOrderFromLeftToRight = c;
        }

    private:
        std::vector<PointOnShortestPath *> shortestPath;
        std::vector<Event *> allEvents;
        void calculatePathAndBoundaryEvents();
        void calculateBendEvents();
        bool currentSegmentOrderFromLeftToRight = true;
        Event *currentEvent;
        void addStartEvent();
        GeometryUtil gU = GeometryUtil();
    };
}


#endif // EVENTCALCULATOR_H
