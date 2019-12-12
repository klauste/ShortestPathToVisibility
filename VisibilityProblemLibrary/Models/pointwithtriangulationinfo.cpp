#include "Models/pointwithtriangulationinfo.h"

Point SPV::PointWithTriangulationInfo::getPoint() {
    if (onTriangle) {
        return currentFace->vertex(pointIndex)->point();
    }
    return point;
}

CDT::Face_handle SPV::PointWithTriangulationInfo::getFaceHandle() {
    return currentFace;
}

CDT::Vertex_handle SPV::PointWithTriangulationInfo::getVertexHandle() {
    return currentFace->vertex(pointIndex);
}
