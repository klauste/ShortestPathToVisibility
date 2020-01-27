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
    class EventSegment
    {
    public:
        EventSegment(std::shared_ptr<LineOfSight> fL, std::shared_ptr<LineOfSight> sL, std::shared_ptr<PointOnShortestPath> pP) :
            firstLineOfSightFromStart(fL),
            secondLineOfSightFromStart(sL),
            pivotPoint(pP)
        {}

        EventSegment* clone()
        {
            EventSegment *newSegment = new EventSegment(firstLineOfSightFromStart, secondLineOfSightFromStart, pivotPoint);
            if (successorSet) {
                newSegment->setSuccessor(successor);
            }
            if (predecessorSet) {
                newSegment->setPredecessor(predecessor);
            }
            newSegment->setStartSideLoSVisible(startSideLoSVisible);
            newSegment->setStartSideOnPolygonEdge(startSideOnPolygonEdge);
            newSegment->setEndSideLoSVisible(endSideLoSVisible);
            newSegment->setEndSideOnPolygonEdge(endSideOnPolygonEdge);
            newSegment->setIndexOfLastSPPointOnStartSide(indexOfLastSPPointOnStartSide);
            newSegment->setIndexOfLastSPPointOnEndSide(indexOfLastSPPointOnEndSide);
            if (distanceOnStartSideSet) {
                newSegment->setDistanceToLastVertex(distanceToLastVertexOnStartSide, true);
            }
            if (distanceOnEndSideSet) {
                newSegment->setDistanceToLastVertex(distanceToLastVertexOnEndSide, false);
            }
            for (unsigned i = 0; i < extraPointsOnStartSide.size(); i++) {
                newSegment->addExtraPointsOnStartSide(extraPointsOnStartSide.at(i));
            }

            for (unsigned i = 0; i < extraPointsOnEndSide.size(); i++) {
                newSegment->addExtraPointsOnEndSide(extraPointsOnEndSide.at(i));
            }
            return newSegment;
        }

        EventSegment *createNewSuccessor(std::shared_ptr<LineOfSight> splitLine)
        {
            EventSegment *newSegment = clone();
            newSegment->setFirstLineOfSightFromStart(splitLine);
            setSecondLineOfSightFromStart(splitLine);
            setSuccessor(newSegment);
            newSegment->setPredecessor(this);
            if (newSegment->hasSuccessor()) {
                newSegment->getSuccessor()->setPredecessor(newSegment);
            }

            return newSegment;
        }

        EventSegment* createNewPredecessor(std::shared_ptr<LineOfSight> splitLine)
        {
            EventSegment* newSegment = clone();
            newSegment->setDistanceToLastVertex(distanceToLastVertexOnStartSide, true);
            newSegment->setSecondLineOfSightFromStart(splitLine);
            setFirstLineOfSightFromStart(splitLine);
            setPredecessor(newSegment);
            newSegment->setSuccessor(this);
            if (newSegment->hasPredecessor()) {
                newSegment->getPredecessor()->setSuccessor(newSegment);
            }

            return newSegment;
        }

        EventSegment* getPredecessor()
        {
            return predecessor;
        }

        void setPredecessor(EventSegment *p)
        {
            predecessorSet = true;
            predecessor = p;
        }

        EventSegment* getSuccessor()
        {
            return successor;
        }

        void setSuccessor(EventSegment* s)
        {
            successorSet = true;
            successor = s;
        }

        void addExtraPointsOnStartSide(Point p)
        {
            extraPointsOnStartSide.push_back(p);
        }

        void removeExtraPointOnStartSide()
        {
            if (extraPointsOnStartSide.size() > 0) {
                extraPointsOnStartSide.pop_back();
            }
        }

        void addExtraPointsOnEndSide(Point p)
        {
            extraPointsOnEndSide.push_back(p);
        }

        void removeExtraPointOnEndSide()
        {
            if (extraPointsOnEndSide.size() > 0) {
                extraPointsOnEndSide.pop_back();
            }
        }

        std::vector<Point> getExtraPointsOnStartSide()
        {
            return extraPointsOnStartSide;
        }

        std::vector<Point> getExtraPointsOnEndSide()
        {
            return extraPointsOnEndSide;
        }

        void setIndexOfLastSPPointOnStartSide(unsigned i)
        {
            indexOfLastSPPointOnStartSide = i;
        }

        void setIndexOfLastSPPointOnEndSide(unsigned i)
        {
            indexOfLastSPPointOnEndSide = i;
        }

        unsigned getIndexOfLastSPPointOnStartSide()
        {
            return indexOfLastSPPointOnStartSide;
        }

        unsigned getIndexOfLastSPPointOnEndSide()
        {
            return indexOfLastSPPointOnEndSide;
        }

        void setStartSideLoSVisible(bool s)
        {
            startSideLoSVisible = s;
        }

        bool getStartSideLoSVisible()
        {
            return startSideLoSVisible;
        }

        bool isLoSVisible(bool onStartSide)
        {
            if (onStartSide) {
                return startSideLoSVisible;
            }
            return endSideLoSVisible;
        }

        void setEndSideLoSVisible(bool e)
        {
            endSideLoSVisible = e;
        }

        bool getEndSideLoSVisible()
        {
            return endSideLoSVisible;
        }

        void setStartSideOnPolygonEdge(bool s)
        {
            startSideOnPolygonEdge = s;
        }

        bool getStartSideOnPolygonEdge()
        {
            return startSideOnPolygonEdge;
        }

        void setEndSideOnPolygonEdge(bool e)
        {
            endSideOnPolygonEdge = e;
        }

        bool getEndSideOnPolygonEdge()
        {
            return endSideOnPolygonEdge;
        }

        bool isPathOnPolygonEdgeAtBeginning(bool onStartSide)
        {
            if (onStartSide) {
                return startSideOnPolygonEdge;
            }
            return endSideOnPolygonEdge;
        }

        std::shared_ptr<LineOfSight> getFirstLineOfSightFromStart()
        {
            return firstLineOfSightFromStart;
        }

        void setFirstLineOfSightFromStart(std::shared_ptr<LineOfSight> fL)
        {
            firstLineOfSightFromStart = fL;
        }

        std::shared_ptr<LineOfSight> getSecondLineOfSightFromStart()
        {
            return secondLineOfSightFromStart;
        }

        void setSecondLineOfSightFromStart(std::shared_ptr<LineOfSight> sL)
        {
            secondLineOfSightFromStart = sL;
        }

        std::shared_ptr<PointOnShortestPath> getPivotPoint()
        {
             return pivotPoint;
        }

        bool hasSuccessor()
        {
            return successorSet;
        }

        bool hasPredecessor()
        {
            return predecessorSet;
        }

        Point getSegmentStartPoint(bool onStartSide)
        {
            if (onStartSide) {
                return firstLineOfSightFromStart->getPointOnStartSide();
            }
            return secondLineOfSightFromStart->getPointOnEndSide();
        }

        Point getSegmentEndPoint(bool onStartSide)
        {
            if (onStartSide) {
                return secondLineOfSightFromStart->getPointOnStartSide();
            }
            return firstLineOfSightFromStart->getPointOnEndSide();
        }

        bool bendEventsOnStartSideAreHandled()
        {
            return bendEventsOnStartSideHandled;
        }

        void setEventsOnStartSideHandled()
        {
            bendEventsOnStartSideHandled = true;
        }

        bool bendEventsOnEndSideAreHandled()
        {
            return bendEventsOnEndSideHandled;
        }

        void setEventsOnEndSideHandled()
        {
            bendEventsOnEndSideHandled = true;
        }

        double getDistanceToLastVertex(bool onStartSide)
        {
            if (onStartSide) {
                return distanceToLastVertexOnStartSide;
            }
            return distanceToLastVertexOnEndSide;
        }

        void setDistanceToLastVertex(double d, bool onStartSide)
        {
            if (onStartSide) {
                distanceToLastVertexOnStartSide = d;
                distanceOnStartSideSet = true;
            } else {
                distanceToLastVertexOnEndSide = d;
                distanceOnEndSideSet = true;
            }
        }

    private:
        EventSegment *predecessor;
        bool predecessorSet = false;
        EventSegment *successor;
        bool successorSet = false;
        std::shared_ptr<PointOnShortestPath> pivotPoint;

        unsigned indexOfLastSPPointOnStartSide;
        unsigned indexOfLastSPPointOnEndSide;
        std::vector<Point> extraPointsOnStartSide;
        std::vector<Point> extraPointsOnEndSide;
        // The first line of sight (as seen from the start point) delimiting this event segment
        std::shared_ptr<LineOfSight> firstLineOfSightFromStart;

        // The second line of sight (as seen from the start point) delimiting this event segment
        std::shared_ptr<LineOfSight> secondLineOfSightFromStart;

        bool startSideLoSVisible = true;
        bool endSideLoSVisible = true;
        bool startSideOnPolygonEdge = false;
        bool endSideOnPolygonEdge = false;
        bool bendEventsOnStartSideHandled = false;
        bool bendEventsOnEndSideHandled = false;
        double distanceToLastVertexOnStartSide;
        bool distanceOnStartSideSet = false;
        double distanceToLastVertexOnEndSide;
        bool distanceOnEndSideSet = false;
    };
}


#endif // EVENTSEGMENT_H
