#include "spventryonshortestpath.h"

Point SPV::ShortestPathEntry::getPoint() {
    // this is face type
    if (type == 1) {
        return currentFace->vertex(pointIndex)->point();
    }
    return entryPoint;
}

CDT::Face_handle SPV::ShortestPathEntry::getFaceHandle() {
    return currentFace;
}

bool SPV::ShortestPathEntry::isStartPoint() {
    return type == 0;
}

bool SPV::ShortestPathEntry::isEndPoint() {
    return type == 2;
}

bool SPV::ShortestPathEntry::isMidPoint() {
    return type == 1;
}

CDT::Vertex_handle SPV::ShortestPathEntry::getVertexHandle() {
    return currentFace->vertex(pointIndex);
}
