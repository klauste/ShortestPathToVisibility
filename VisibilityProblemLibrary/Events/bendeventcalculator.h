#ifndef BENDEVENTCALCULATOR_H
#define BENDEVENTCALCULATOR_H

#include "Events/pathandboundaryeventcalculator.h"

namespace SPV {
    class BendEventCalculator : public PathAndBoundaryEventCalculator {
    public:
        BendEventCalculator (const Polygon &p, Point s, Point e) :
            PathAndBoundaryEventCalculator (p, s, e) {}

        virtual ~BendEventCalculator() {}

        /**
         * @brief calculateBendEvents calculates the bend events by adding new event segments
         */
        void calculateBendEvents();

    private:
        bool calculateEventsOnStartSide;

        /**
         * @brief calculateEventsForCurrentEventSegment calculates the bend events for the currentl event segment
         * instance. Called while iterating over all path and boundary event segments
         */
        void calculateEventsForCurrentEventSegment();

        /**
         * @brief getNextDegenerateBendEvent checks if there is a degenerate bend event on the current edge defined by the
         * two intersection events. If there isn't, false is returned. If there are degenerate events, the
         * degenerate event closer to the start point of the edge is returned.
         * @param onStartSide
         * @return
         */
        boost::variant<Point, bool> getNextDegenerateBendEvent();

        /**
         * @brief handlePathOrBoundaryEvent handles path or boundary events which coincide with bend events
         */
        void handlePathOrBoundaryEvent();

        /**
         * @brief handleBoundaryEvent handles boundary events which coincide with bend events
         * @param previousEventSegment
         */
        void handleBoundaryEvent(EventSegment *previousEventSegment);

        /**
         * @brief handlePathEvent handles path events which coincide with bend events
         * @param previousEventSegment
         */
        void handlePathEvent(EventSegment *previousEventSegment);

        /**
         * @brief handleBendEventWithPointAddition handles bend events which add a polygon vertex to
         * the shortest path to a line of sight
         * @param checkSegmentStartOnly if true only the segment start is checked for the addition of a point
         * @return
         */
        bool handleBendEventWithPointAddition(bool checkSegmentStartOnly);

        /**
         * @brief handleBendEventWithPointLoss handles bend events where points are removed from the shortest
         * path to a line of sight
         * @param checkSegmentStartOnly if true only the segment start is checked for a point loss
         * @return
         */
        bool handleBendEventWithPointLoss(bool checkSegmentStartOnly);

        /**
         * @brief addNewEventSegment adds a new event segment by splitting the current event segment along the
         * line through eventPoint and the current pivotPoint
         * @param eventPoint
         */
        void addNewEventSegment(Point eventPoint);

        /**
         * @brief handleDegenerateBendEvent adds a degenerate bend event by splitting the current event segment
         * along the line through eventPoint and current pivotPoint
         * @param eventPoint
         */
        void handleDegenerateBendEvent(Point eventPoint);

        /**
         * @brief handleDegenerateBendEventForSegmentStart handles a degenerate event at the start of the
         * event segment
         */
        void handleDegenerateBendEventForSegmentStart();

        /**
         * @brief handleSegmentToProtrudingVertex handles the segment on a line of sight from a point on the polygon
         * boundary and a polygon vertex which the line of sight touches. It is possible that the shortest path to
         * the line of sight on this segments loses a point and this function handles that scenario
         * @param previousEventSegment
         */
        void handleSegmentToProtrudingVertex(EventSegment *previousEventSegment);

        /**
         * @brief setDistanceToLastVertex calculates and set the distanc to last polygon vertex before the
         * lines of sight in this segment are reached
         */
        void setDistanceToLastVertex();

        /**
         * @brief setCurrentSegmentOrderFromLeftToRight sets the currentSegmentOrderFromLeftToRight flag. For bend
         * events calculation this is only required to check if there is change in rotation at a path event. In that
         * case the shortest path to the line of sight follows the shortest path to the previous pivot point.
         */
        void setCurrentSegmentOrderFromLeftToRight();

        /**
         * @brief addPreviousSettingsToCurrentES adds the settings of the previous event segment to the
         * current one.
         * @param previousEventSegment
         * @param pointsOnly
         */
        void addPreviousSettingsToCurrentES(EventSegment *previousEventSegment, bool pointsOnly);
    };
}

#endif // BENDEVENTCALCULATOR_H
