#ifndef EVENTSEGMENT_H
#define EVENTSEGMENT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>
#include "Models/lineofsight.h"
#include "Models/pointonshortestpath.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

namespace SPV {
    /**
     * @brief The EventSegment class stores information about two successive events. The events are represented
     * as instances of class LineOfSight. An instance of this class contains the necessary information
     * to calculate a local minimum. Event segments are linked via pointers, so that all event segments for
     * a given visibility problem can be inspected in the correct order.
     *
     * The terms 'start side' and 'end side' used in the comments refer to the half of the lines of sight
     * which is closer to the start/end point of the visibility problem.
     */
    class EventSegment
    {
    public:
        EventSegment(
            std::shared_ptr<LineOfSight> fL,
            std::shared_ptr<LineOfSight> sL,
            std::shared_ptr<PointOnShortestPath> pP) :
            firstLineOfSightFromStart(fL),
            secondLineOfSightFromStart(sL),
            pivotPoint(pP),
            predecessorSet(false),
            successorSet(false),
            startSideLoSVisible(true),
            endSideLoSVisible(true),
            startSideOnPolygonEdge(false),
            endSideOnPolygonEdge(false),
            bendEventsOnStartSideHandled(false),
            bendEventsOnEndSideHandled(false),
            distanceOnStartSideSet(false),
            distanceOnEndSideSet(false)
        {}

        /**
         * @brief clone returns a cloned instance of the current instance containing all relevant information
         * @return
         */
        EventSegment* clone();

        /**
         * @brief createNewSuccessor creates a successor of the current instance at the splitline.
         * @param splitLine
         * @return
         */
        EventSegment *createNewSuccessor(std::shared_ptr<LineOfSight> splitLine);

        /**
         * @brief createNewPredecessor creates a predecessor of the current instance at the splitline
         * @param splitLine
         * @return
         */
        EventSegment* createNewPredecessor(std::shared_ptr<LineOfSight> splitLine);

        /**
         * @brief getPredecessor returns this instance's predecessor. Should only be called, if
         * hasPredecessor returns true
         * @return
         */
        EventSegment* getPredecessor();

        /**
         * @brief setPredecessor set this instance's predecessor to p
         * @param p
         */
        void setPredecessor(EventSegment *p);

        /**
         * @brief getSuccessor returns this instance's successor. Should only be called if
         * hasSuccessor return true
         * @return
         */
        EventSegment* getSuccessor();

        /**
         * @brief setSuccessor sets this instance's successor to s
         * @param s
         */
        void setSuccessor(EventSegment* s);

        /**
         * @brief addExtraPointsOnStartSide adds an extra point, i.e. a point which does not belong to
         * the shortest path from start point to end point to the path from start point to the lines of
         * sights in this event segment.
         * @param p
         */
        void addExtraPointsOnStartSide(Point p);

        /**
         * @brief removeExtraPointOnStartSide removes an extra point from the path starting at the start point
         */
        void removeExtraPointOnStartSide();

        /**
         * @brief addExtraPointsOnEndSide adds an extra point, i.e. a point which does not belong to
         * the shortest path from start point to end point to the path from end point to the lines of
         * sights in this event segment.
         * @param p
         */
        void addExtraPointsOnEndSide(Point p);

        /**
         * @brief removeExtraPointOnEndSide removes an extra point from the path starting at the end point
         */
        void removeExtraPointOnEndSide();

        /**
         * @brief getExtraPointsOnStartSide returns the extra points for a path from the start point to a line of sight
         * @return
         */
        std::vector<Point> getExtraPointsOnStartSide();

        /**
         * @brief getExtraPointsOnEndSide returns the extra points for a path from the end point to a line of sight
         * @return
         */
        std::vector<Point> getExtraPointsOnEndSide();

        /**
         * @brief setIndexOfLastSPPointOnStartSide sets the index up to which the path starting at the
         * start point to a line of sight follows the shortest path between start and end point
         * @param i
         */
        void setIndexOfLastSPPointOnStartSide(unsigned i);

        /**
         * @brief setIndexOfLastSPPointOnEndSide sets the index up to which the path starting at the
         * end point to a line of sight follows the shortest path between start and end point
         * @param i
         */
        void setIndexOfLastSPPointOnEndSide(unsigned i);

        /**
         * @brief getIndexOfLastSPPointOnStartSide returns the index
         */
        unsigned getIndexOfLastSPPointOnStartSide();

        /**
         * @brief getIndexOfLastSPPointOnEndSide returns the index
         */
        unsigned getIndexOfLastSPPointOnEndSide();

        /**
         * @brief setStartSideLoSVisible sets the visibility flag for the start side
         * @param s
         */
        void setStartSideLoSVisible(bool s);

        /**
         * @brief getStartSideLoSVisible gets the visiblity flag for the start side
         * @return
         */
        bool getStartSideLoSVisible();

        /**
         * @brief isLoSVisible convenience function to get the visibility flags
         * @param onStartSide
         * @return
         */
        bool isLoSVisible(bool onStartSide);

        /**
         * @brief setEndSideLoSVisible sets the visibility flag for the end side
         * @param e
         */
        void setEndSideLoSVisible(bool e);

        /**
         * @brief getEndSideLoSVisible gets the visiblity flag for the end side
         * @return
         */
        bool getEndSideLoSVisible();

        /**
         * @brief setStartSideOnPolygonEdge sets the flag indicating if the path to the lines of sight
         * start on the polygon edge
         * @param s
         */
        void setStartSideOnPolygonEdge(bool s);

        /**
         * @brief getStartSideOnPolygonEdge returns the flag
         * @return
         */
        bool getStartSideOnPolygonEdge();

        /**
         * @brief setEndSideOnPolygonEdge sets the flag indicating if the path to the lines of sight
         * start on the polygon edge
         * @param e
         */
        void setEndSideOnPolygonEdge(bool e);

        /**
         * @brief getEndSideOnPolygonEdge returns the flag
         * @return
         */
        bool getEndSideOnPolygonEdge();

        /**
         * @brief isPathOnPolygonEdgeAtBeginning convenience function to get the flags
         * @param onStartSide
         * @return
         */
        bool isPathOnPolygonEdgeAtBeginning(bool onStartSide);

        /**
         * @brief getFirstLineOfSightFromStart returns the line of sight where the event segment starts
         * @return
         */
        std::shared_ptr<LineOfSight> getFirstLineOfSightFromStart();

        /**
         * @brief setFirstLineOfSightFromStart sets the first line of sight
         * @param fL
         */
        void setFirstLineOfSightFromStart(std::shared_ptr<LineOfSight> fL);

        /**
         * @brief getSecondLineOfSightFromStart returns the line of sight where the event segment ends
         * @return
         */
        std::shared_ptr<LineOfSight> getSecondLineOfSightFromStart();

        /**
         * @brief setSecondLineOfSightFromStart sets the second line of sight
         * @param sL
         */
        void setSecondLineOfSightFromStart(std::shared_ptr<LineOfSight> sL);

        /**
         * @brief getPivotPoint returns the pivotPoint information
         * @return
         */
        std::shared_ptr<PointOnShortestPath> getPivotPoint();

        /**
         * @brief hasSuccessor returns whether or not the successor is set
         * @return
         */
        bool hasSuccessor();

        /**
         * @brief hasPredecessor returns whether or not the predecessor is set
         * @return
         */
        bool hasPredecessor();

        /**
         * @brief getSegmentStartPoint get the start point of the segment either on the
         * start or end side
         * @param onStartSide
         * @return
         */
        Point getSegmentStartPoint(bool onStartSide);

        /**
         * @brief getSegmentEndPoint get the end point on of the segment either on the
         * start or end side
         * @param onStartSide
         * @return
         */
        Point getSegmentEndPoint(bool onStartSide);

        /**
         * @brief bendEventsOnStartSideAreHandled returns whether bend events on the
         * start side have been handled
         * @return
         */
        bool bendEventsOnStartSideAreHandled();

        /**
         * @brief setEventsOnStartSideHandled sets the flag whether bend events on the start
         * side have been handled
         */
        void setEventsOnStartSideHandled();

        /**
         * @brief bendEventsOnEndSideAreHandled returns whether bend events on the end side
         * have been handled
         * @return
         */
        bool bendEventsOnEndSideAreHandled();

        /**
         * @brief setEventsOnEndSideHandled sets the flag wheter bend events on the end side have
         * been handled
         */
        void setEventsOnEndSideHandled();

        /**
         * @brief getDistanceToLastVertex returns the distance of the shortest path from
         * either the start or end point to the last vertex of the polygon before the lines
         * of sight in this segement are reached
         * @param onStartSide
         * @return
         */
        double getDistanceToLastVertex(bool onStartSide);

        /**
         * @brief setDistanceToLastVertex sets the distance to the last vertex on the polygon
         * before the lines of sight in this segment are reached
         * @param d
         * @param onStartSide
         */
        void setDistanceToLastVertex(double d, bool onStartSide);

    private:
        /**
         * @brief firstLineOfSightFromStart pointer to the first line of sight (as seen from the start point)
         * delimiting this event segment
         */
        std::shared_ptr<LineOfSight> firstLineOfSightFromStart;

        /**
         * @brief secondLineOfSightFromStart pointer to the second line of sight (as seen from the start point)
         * delimiting this event segment
         */
        std::shared_ptr<LineOfSight> secondLineOfSightFromStart;

        /**
         * @brief pivotPoint pointer to this event segment's pivot point
         */
        std::shared_ptr<PointOnShortestPath> pivotPoint;

        /**
         * @brief predecessor pointer to this event's predecessor
         */
        EventSegment *predecessor;

        /**
         * @brief successor pointer to this event's successor
         */
        EventSegment *successor;

        /**
         * @brief predecessorSet whether or not the predecessor is set
         */
        bool predecessorSet;

        /**
         * @brief successorSet whether or not the successor is set
         */
        bool successorSet;

        /**
         * @brief indexOfLastSPPointOnStartSide the index of the last point on the shortest path
         * from the start point to this segment. After this index, the path to a line of sight
         * no longer follows the shortest path between start and end point.
         */
        unsigned indexOfLastSPPointOnStartSide;

        /**
         * @brief indexOfLastSPPointOnEndSide the index of the last point on the shortest path
         * from the end point to this segment. After this index, the path to a line of sight
         * no longer follows the shortest path between start and end point.
         */
        unsigned indexOfLastSPPointOnEndSide;

        /**
         * @brief extraPointsOnStartSide stores polygon vertices which are not part of the shortest path
         * from start to end point but which are part of the path from the start point to lines
         * of sight in this segment
         */
        std::vector<Point> extraPointsOnStartSide;

        /**
         * @brief extraPointsOnEndSide stores polygon vertices which are not part of the shortest path
         * from start to end point but which are part of the path from the end point to lines
         * of sight in this segment
         */
        std::vector<Point> extraPointsOnEndSide;

        /**
         * @brief startSideLoSVisible indicates whether the shortest path from the last vertex on
         * the polygon to the line of sight on the start side is visible or whether it is obstructed
         * by a polygon edge
         */
        bool startSideLoSVisible;

        /**
         * @brief endSideLoSVisible indicates whether the shortest path from the last vertex on
         * the polygon to the line of sight on the end side is visible or whether it is obstructed
         * by a polygon edge
         */
        bool endSideLoSVisible;

        /**
         * @brief startSideOnPolygonEdge indicates for the start side whether the path from the last vertex to
         * a line of sight starts on the polygon edge
         */
        bool startSideOnPolygonEdge;

        /**
         * @brief endSideOnPolygonEdge indicates for the end side whether the path from the last vertex to
         * a line of sight starts on the polygon edge
         */
        bool endSideOnPolygonEdge;

        /**
         * @brief bendEventsOnStartSideHandled indicates whether bend events on the start side have been handled
         */
        bool bendEventsOnStartSideHandled;

        /**
         * @brief bendEventsOnEndSideHandled indicates whether bend events on the end side have been handled
         */
        bool bendEventsOnEndSideHandled;

        /**
         * @brief distanceToLastVertexOnStartSide stores the distance from the start point to the last
         * polygon vertex before the lines of sight in this segment
         */
        double distanceToLastVertexOnStartSide;

        /**
         * @brief distanceOnStartSideSet indicates if distanceToLastVertexOnStartSide has been set
         */
        bool distanceOnStartSideSet = false;

        /**
         * @brief distanceToLastVertexOnEndSide stores the distance from the end point to the last
         * polygon vertex before the lines of sight in this segment
         */
        double distanceToLastVertexOnEndSide;

        /**
         * @brief distanceOnEndSideSet indicates if distanceToLastVertexOnEndSide has been set
         */
        bool distanceOnEndSideSet = false;
    };
}


#endif // EVENTSEGMENT_H
