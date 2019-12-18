#ifndef EVENTSEGMENT_H
#define EVENTSEGMENT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>
#include "Models/lineofsight.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

namespace SPV {
    class EventSegment
    {
    public:
        EventSegment(LineOfSight *fL, LineOfSight *sL, Point pP) :
            firstLineOfSightFromStart(fL),
            secondLineOfSightFromStart(sL),
            pivotPoint(pP)
        {}

        EventSegment* createNewSuccessor(EventSegment *currentSegment, LineOfSight *splitLine)
        {
            EventSegment *newSegment = new EventSegment(currentSegment->getFirstLineOfSightFromStart(), splitLine, currentSegment->getPivotPoint());
            currentSegment->setFirstLineOfSightFromStart(splitLine);
            if (currentSegment->hasPredecessor()) {
                newSegment->setPredecessor(currentSegment->getPredecessor());
            }
            currentSegment->setPredecessor(newSegment);
            newSegment->setSuccessor(currentSegment);

            return newSegment;
        }

        EventSegment* createNewPredecessor(EventSegment *currentSegment, LineOfSight *splitLine)
        {
            EventSegment *newSegment = new EventSegment(splitLine, currentSegment->getSecondLineOfSightFromStart(), currentSegment->getPivotPoint());
            currentSegment->setSecondLineOfSightFromStart(splitLine);
            if (currentSegment->hasSuccessor()) {
                newSegment->setSuccessor(currentSegment->getSuccessor());
            }
            currentSegment->setSuccessor(newSegment);
            newSegment->setPredecessor(currentSegment);

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

        void addExtraPointsOnEndSide(Point p)
        {
            extraPointsOnEndSide.push_back(p);
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

        LineOfSight* getFirstLineOfSightFromStart()
        {
            return firstLineOfSightFromStart;
        }

        void setFirstLineOfSightFromStart(LineOfSight *fL)
        {
            firstLineOfSightFromStart = fL;
        }

        LineOfSight* getSecondLineOfSightFromStart()
        {
            return secondLineOfSightFromStart;
        }

        void setSecondLineOfSightFromStart(LineOfSight *sL)
        {
            secondLineOfSightFromStart = sL;
        }

        Point getPivotPoint()
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
    private:
        EventSegment *predecessor;
        bool predecessorSet = false;
        EventSegment *successor;
        bool successorSet = false;
        Point pivotPoint;

        unsigned indexOfLastSPPointOnStartSide;
        unsigned indexOfLastSPPointOnEndSide;
        std::vector<Point> extraPointsOnStartSide;
        std::vector<Point> extraPointsOnEndSide;
        // The first line of sight (as seen from the start point) delimiting this event segment
        LineOfSight *firstLineOfSightFromStart;

        // The second line of sight (as seen from the start point) delimiting this event segment
        LineOfSight *secondLineOfSightFromStart;

        bool startSideLoSVisible;
        bool endSideLoSVisible;
        bool startSideOnPolygonEdge;
        bool endSideOnPolygonEdge;
    };
}


#endif // EVENTSEGMENT_H
