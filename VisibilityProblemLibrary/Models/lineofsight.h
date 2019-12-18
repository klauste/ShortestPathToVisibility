#ifndef LINEOFSIGHT_H
#define LINEOFSIGHT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

namespace SPV {
    class LineOfSight {
    public:
        LineOfSight() {}
        LineOfSight(Point pS, bool pSV, Point pE, bool pEV) :
            pointOnStartSide(pS),
            pointOnStartSideIsVertex(pSV),
            pointOnEndSide(pE),
            pointOnEndSideIsVertex(pEV) {}

        Point getPointOnStartSide()
        {
            return pointOnStartSide;
        }

        void setPointOnStartSide(Point p)
        {
            pointOnStartSide = p;
        }

        Point getPointOnEndSide()
        {
            return pointOnEndSide;
        }

        void setPointOnEndSide(Point p)
        {
            pointOnEndSide = p;
        }

        bool isStartPointVertex()
        {
            return pointOnStartSideIsVertex;
        }

        void setIsStartPointVertex(bool s)
        {
            pointOnStartSideIsVertex = s;
        }

        bool isEndPointVertex()
        {
            return pointOnEndSideIsVertex;
        }

        void setIsEndPointVertex(bool e)
        {
            pointOnEndSideIsVertex = e;
        }
    private:
        Point pointOnStartSide;
        Point pointOnEndSide;
        bool pointOnStartSideIsVertex;
        bool pointOnEndSideIsVertex;
    };
}

#endif // LINEOFSIGHT_H
