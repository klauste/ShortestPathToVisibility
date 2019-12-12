#ifndef EVENT_H
#define EVENT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

namespace SPV {
    class Event
    {
    public:
        Event(Segment sE, Segment eE, Point pP, Point iS, Point eS) :
            polygonEdgeOnStartSide(sE),
            polygonEdgeOnEndSide(eE),
            pivotPoint(pP),
            intersectionWithStartSideEdge(iS),
            intersectionWithEndSideEdge(eS)
        {}

        Segment getPolygonEdgeOnStartSide()
        {
            return polygonEdgeOnStartSide;
        }

        Segment getPolygonEdgeOnEndSide()
        {
            return polygonEdgeOnEndSide;
        }

        Point getPivotPoint()
        {
            return pivotPoint;
        }

        Point getIntersectionWithStartSideEdge()
        {
            return intersectionWithStartSideEdge;
        }

        Point getIntersectionWithEndSideEdge()
        {
            return intersectionWithEndSideEdge;
        }

        Event* getPredecessor()
        {
            return predecessor;
        }

        void setPredecessor(Event *p)
        {
            hasPredecessor = true;
            predecessor = p;
        }

        Event* getSuccessor()
        {
            return successor;
        }

        void setSuccessor(Event* s)
        {
            hasSuccessor = true;
            successor = s;
        }

        void addPointToPathFromStart(Point p)
        {
            pathFromStart.push_back(p);
        }

        void addPointToPathFromEnd(Point p)
        {
            pathFromEnd.push_back(p);
        }

        std::vector<Point> getPathFromStart()
        {
            return pathFromStart;
        }

        std::vector<Point> getPathFromEnd()
        {
            return pathFromEnd;
        }

        void setStartSideLoSVisible(bool s)
        {
            startSideLoSVisible = s;
        }

        bool getStartSideLoSVisible()
        {
            return startSideLoSVisible;
        }

        void setEndSideLoSVisibe(bool e)
        {
            endSideLoSVisible = e;
        }

        bool getEndSideLoSVisibe()
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

    private:
        Event *predecessor;
        bool hasPredecessor = false;
        Event *successor;
        bool hasSuccessor = false;
        Segment polygonEdgeOnStartSide;
        Segment polygonEdgeOnEndSide;
        Point pivotPoint;
        Point intersectionWithStartSideEdge;
        Point intersectionWithEndSideEdge;
        std::vector<Point> pathFromStart;
        std::vector<Point> pathFromEnd;
        bool startSideLoSVisible;
        bool endSideLoSVisible;
        bool startSideOnPolygonEdge;
        bool endSideOnPolygonEdge;
    };
}


#endif // EVENT_H
