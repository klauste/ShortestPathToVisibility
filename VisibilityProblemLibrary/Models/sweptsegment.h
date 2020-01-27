#ifndef SWEPTSEGMENT_H
#define SWEPTSEGMENT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;

namespace SPV {
    class SweptSegment {
    public:
        SweptSegment(Point l, bool lP, Point r, bool rP) :
            leftPoint(l),
            leftPointPolygonVertex(lP),
            rightPoint(r),
            rightPointPolygonVertex(rP) {}

        std::shared_ptr<SPV::SweptSegment> getClone()
        {
            return std::make_shared<SweptSegment>(leftPoint, leftPointPolygonVertex, rightPoint, rightPointPolygonVertex);
        }

        Point getLeftPoint()
        {
            return leftPoint;
        }

        bool leftPointIsPolygonVertex()
        {
            return leftPointPolygonVertex;
        }

        Point getRightPoint()
        {
            return rightPoint;
        }

        bool rightPointIsPolygonVertex()
        {
            return rightPointPolygonVertex;
        }
    private:
        Point leftPoint;
        bool leftPointPolygonVertex;
        Point rightPoint;
        bool rightPointPolygonVertex;
    };
}


#endif // SWEPTSEGMENT_H
