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
    /**
     * @brief The PathAndBoundaryEventCalculator class calculates the path and boundary
     * events for a given polygon and a start and end point.
     */
    class PathAndBoundaryEventCalculator : public BaseCalculator
    {
    public:
        PathAndBoundaryEventCalculator (Polygon p, Point s, Point e);

        virtual ~PathAndBoundaryEventCalculator()
        {
            if (!directPathExists) {
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
        }

        /**
         * @brief getSegmentsForFinalPoint returns the segments which are swept when the second or
         * second to last point on the shortest path is the pivot point for the lines of sight.
         * These segments are different from the other ones as they end/start on the edge containig
         * the start/end point. This function could be private, but is left as public for testing
         * purposes
         * @param forFirstPoint indicates if the segments for the first point on the shortes point
         * or the last one should be returned
         * @return
         */
        std::vector<std::shared_ptr<SweptSegment>> getSegmentsForFinalPoint(bool forFirstPoint);

        /**
         * @brief setCurrentSegmentOrderFromLeftToRight set the currentSegmentOrderFromLeftToRight
         * flag which indicates if the swept segments for the current pivot point need to inspected
         * from left to right or from right to left. This function is only used in tests, which is
         * not great, but worth it.
         * @param c
         */
        void setCurrentSegmentOrderFromLeftToRight(bool c);

        /**
         * @brief calculatePathAndBoundaryEvents calculate the path and the boundary events for the
         * given polygon and start and end point. Path and boundary events are represented by instances
         * of EventSegment which are linked together via pointers.
         */
        void calculatePathAndBoundaryEvents();

    protected:
        /**
         * @brief currentSegmentOrderFromLeftToRight indicates if the swept segments for the
         * current pivot point should be iterated from left to right or right to left
         */
        bool currentSegmentOrderFromLeftToRight;

        /**
         * @brief isSegmentOrderFromLeftToRight returns if the swept segments for the shortest path
         * point at index in the shortest path vector should should be iterated from left to right
         * or right to left
         * @param index
         * @return
         */
        bool isSegmentOrderFromLeftToRight(unsigned index);
    private:
        /**
         * @brief The EventSegmentCreationResult struct helper data structure used when creating a
         * new event segment
         */
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

        /**
         * @brief createPathEventSegment creates a path event segmentg
         * at endSideSegment
         * @param startSideSegment
         * @param endSideSegment
         * @param pivotPoint
         * @return
         */
        EventSegmentCreationResult createPathEventSegment(
            std::shared_ptr<SweptSegment> startSideSegment,
            std::shared_ptr<SweptSegment> endSideSegment,
            std::shared_ptr<PointOnShortestPath> pivotPoint
        );

        /**
         * @brief createBoundaryEventSegment creates a boundary event segment
         * @param startSideSegment
         * @param endSideSegment
         * @param pivotPoint
         * @param endOfSegmentReached
         * @param endOfEndSegmentReached
         * @return
         */
        EventSegmentCreationResult createBoundaryEventSegment(
            std::shared_ptr<SweptSegment> startSideSegment,
            std::shared_ptr<SweptSegment> endSideSegment,
            std::shared_ptr<PointOnShortestPath> pivotPoint,
            bool endOfSegmentReached,
            bool endOfEndSegmentReached
        );

        /**
         * @brief createEventSegment helper function to create an event segment of type t (PATH or BOUNDARY).
         * The first line of sight starts at firstStartPoint and ends at firstEndPoint. The second line of
         * sight starts at secondStartPoint and ends at secondEndPoint.
         * @param firstStartPoint
         * @param firstStartPointIsVertex
         * @param firstEndPoint
         * @param firstEndPointIsVertex
         * @param secondStartPoint
         * @param secondStartPointIsVertex
         * @param secondEndPoint
         * @param secondEndPointIsVertex
         * @param pivotPoint
         * @param t
         * @return
         */
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

        /**
         * @brief getStartSegmentsForLoop helper function to get the swept segments on the start point
         * side which rotate around the shortest path point at index i
         * @param segments
         * @param i
         * @return
         */
        std::vector<std::shared_ptr<SweptSegment>> getStartSegmentsForLoop(
            const std::vector<std::shared_ptr<SweptSegment>> &segments,
            unsigned i
        );

        /**
         * @brief getEndSegmentsForLoop helper function to get the swept segments on the end point
         * side which rotate around the shortest path point at index i
         * @param segments
         * @param i
         * @return
         */
        std::vector<std::shared_ptr<SweptSegment>> getEndSegmentsForLoop(
            const std::vector<std::shared_ptr<SweptSegment>> &segments,
            unsigned i
        );
    };
}

#endif // PATHANDBOUNDARYEVENTCALCULATOR_H
