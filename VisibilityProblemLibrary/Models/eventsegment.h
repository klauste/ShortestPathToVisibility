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
        EventSegment(LineOfSight *fL, LineOfSight *sL, PointOnShortestPath *pP) :
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
            for (unsigned i = 0; i < extraPointsOnStartSide.size(); i++) {
                newSegment->addExtraPointsOnStartSide(extraPointsOnStartSide.at(i));
            }

            for (unsigned i = 0; i < extraPointsOnEndSide.size(); i++) {
                newSegment->addExtraPointsOnEndSide(extraPointsOnEndSide.at(i));
            }
            return newSegment;
        }

        EventSegment* createNewSuccessor(LineOfSight *splitLine)
        {
            EventSegment *newSegment = clone();
            newSegment->setFirstLineOfSightFromStart(splitLine);
            setSecondLineOfSightFromStart(splitLine);
            setSuccessor(newSegment);
            newSegment->setPredecessor(this);

            return newSegment;
        }

        EventSegment* createNewPredecessor(LineOfSight *splitLine)
        {
            EventSegment *newSegment = clone();
            newSegment->setSecondLineOfSightFromStart(splitLine);
            setFirstLineOfSightFromStart(splitLine);
            setPredecessor(newSegment);
            newSegment->setSuccessor(this);

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

        bool isPathOnOnPolygonEdgeAtBeginning(bool onStartSide)
        {
            if (onStartSide) {
                return startSideOnPolygonEdge;
            }
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

        PointOnShortestPath* getPivotPoint()
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
    private:
        EventSegment *predecessor;
        bool predecessorSet = false;
        EventSegment *successor;
        bool successorSet = false;
        PointOnShortestPath *pivotPoint;

        unsigned indexOfLastSPPointOnStartSide;
        unsigned indexOfLastSPPointOnEndSide;
        std::vector<Point> extraPointsOnStartSide;
        std::vector<Point> extraPointsOnEndSide;
        // The first line of sight (as seen from the start point) delimiting this event segment
        LineOfSight *firstLineOfSightFromStart;

        // The second line of sight (as seen from the start point) delimiting this event segment
        LineOfSight *secondLineOfSightFromStart;

        bool startSideLoSVisible = true;
        bool endSideLoSVisible = true;
        bool startSideOnPolygonEdge = false;
        bool endSideOnPolygonEdge = false;
    };
}


#endif // EVENTSEGMENT_H
