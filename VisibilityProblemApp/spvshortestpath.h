#ifndef SPVSHORTESTPATH_H
#define SPVSHORTESTPATH_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <vector>
#include <iostream>
#include "spvshortestpathtree.h"
#include "spvfaceinfo.h"
#include "spventryonshortestpath.h"
#include "spveventintersection.h"
#include "spveventmap.h"
#include <CGAL/intersections.h>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include "spvboundaryevents.h"
#include "spvbendevents.h"
#include "spvminimumcalculator.h"
#include "spvgeometryutil.h"
#include "spvminimum.h"
#include "spvbaseevents.h"

typedef K::Ray_2 Ray;
typedef K::Intersect_2 Intersect_2;
typedef CGAL::Exact_predicates_inexact_constructions_kernel       K;
typedef CGAL::Triangulation_vertex_base_2<K>                      Vb;
typedef CGAL::Triangulation_face_base_with_info_2<SPV::FaceInfo,K>    Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K,Fbb>        Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_predicates_tag                                Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>  CDT;
typedef K::Segment_2 Segment;
typedef K::Point_2 Point;
typedef K::Triangle_2 Triangle;
typedef CGAL::Polygon_2<K> Polygon;
typedef K::Line_2 Line;
typedef CDT::Face_circulator Face_circulator;

struct FaceOnPath
{
    FaceOnPath(TDS::Face_handle currentFace) : currentFace(currentFace){}
    int nextFaceIndex;
    TDS::Face_handle currentFace;
};

namespace SPV {
    class SPVShortestPath: public BaseEvents
    {
    public:
        void initialize(const Polygon &polygon);
        const CDT& getTriangulation();
        bool calculateShortestPath();
        void setPoint(int index, float x, float y);
        const std::vector<ShortestPathEntry *>& getSleevePath(int i);
        std::vector<SPV::PointOnShortestPath *> getShorttestPathTree();
        void calculateShortestPathTree(bool startFromEnd);
        std::vector<SPV::Minimum*> getMinima() {
            return minimumCalculator.getAllMinima();
        }
    private:
        void setShortestPathMapInfo(
                CDT::Face_handle currentFace,
                int neighborIndex,
                SPV::PointOnShortestPath* apex,
                std::vector<SPV::PointOnShortestPath*> &funnel,
                bool startFromEnd
        );
        struct predecessorInfo {
            predecessorInfo() : isApex(false),
                                isLastPointOnFunnel(false),
                                onLeftFunnel(false),
                                onRightFunnel(false),
                                indexOnFunnel(-1) {}
            bool isApex;
            bool isLastPointOnFunnel;
            bool onLeftFunnel;
            bool onRightFunnel;
            int indexOnFunnel;
        };
        std::vector<ShortestPathEntry *> funnelTail;
        std::vector<ShortestPathEntry *> funnelLeftPath;
        std::vector<ShortestPathEntry *> funnelRightPath;
        ShortestPathEntry * startPoint;
        Point sPoint;
        Point ePoint;
        ShortestPathEntry * endPoint;
        CDT cdt;
        std::vector<FaceOnPath *> facesFromStartToEnd;
        std::vector<SPV::PointOnShortestPath *> shortestPathTree;
        std::vector<SPV::PointOnShortestPath *> shortestPathTreeFromEnd;

        void splitFunnel(
                CDT::Face_handle currentFace,
                int neighborIndex,
                SPV::PointOnShortestPath* apex,
                std::vector<SPV::PointOnShortestPath*> &leftFunnel,
                std::vector<SPV::PointOnShortestPath*> &rightFunnel,
                bool startFromEnd
        );
        predecessorInfo* findPredecessor(
                Point p,
                SPV::PointOnShortestPath* apex,
                std::vector<SPV::PointOnShortestPath*> &leftFunnel,
                std::vector<SPV::PointOnShortestPath*> &rightFunnel
        );
        void calculateTriangulation();
        void markDomains(CDT& ct,
                     CDT::Face_handle start,
                     int index,
                     std::list<CDT::Edge>& border );
        void markDomains(CDT& cdt);
        bool setFacesFromStartToEndPoint();
        bool recursivelyfindEndPoint(TDS::Face_handle &currentFaceHandle);
        void handleNextPoint(
                std::vector<ShortestPathEntry *> &backwardPath,
                std::vector<ShortestPathEntry *> &forwardPath,
                ShortestPathEntry *nextPoint,
                bool isBackwardPathOnTheRight
        );
        bool isOnRightSide(Point p1, Point p2, Point p3);
        bool isOnLeftSide(Point p1, Point p2, Point p3);
        Polygon polygon;
        BoundaryEvents boundaryEvents;
        BendEvents bendEvents;
        MinimumCalculator minimumCalculator;
        bool setEventIntersection(Point seg1, Point seg2, EventOnShortestPath* spEvent, bool startFromEnd);

        /**
         * This function checks if startPoint and endPoint are entries in the shortes path. If they are,
         * a path event should be added and the function returns true. If not, false is returned
         *
         * @brief shouldAddPathEventForEntries
         * @param endPoint
         * @param startPoint
         * @param startFromEnd
         * @return
         */
        bool shouldAddPathEventForEntries(ShortestPathEntry* endPoint, ShortestPathEntry* startPoint, bool startFromEnd);
    };
}
#endif // SPVSHORTESTPATH_H
