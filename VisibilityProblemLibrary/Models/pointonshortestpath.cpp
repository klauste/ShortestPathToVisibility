#include "Models/pointonshortestpath.h"

Point SPV::PointOnShortestPath::getPoint()
{
    return point;
}

std::vector<std::shared_ptr<SPV::SweptSegment>> SPV::PointOnShortestPath::getSegmentsFromStart()
{
    return segmentsFromStart;
}

std::vector<std::shared_ptr<SPV::SweptSegment>> SPV::PointOnShortestPath::getSegmentsFromEnd()
{
    return segmentsFromEnd;
}

void SPV::PointOnShortestPath::addSegmentFromStart(std::shared_ptr<SPV::SweptSegment> s)
{
    segmentsFromStart.push_back(s);
}

void SPV::PointOnShortestPath::addSegmentFromEnd(std::shared_ptr<SweptSegment> s)
{
    segmentsFromEnd.push_back(s);
}

unsigned SPV::PointOnShortestPath::getIndexOnShortestPath()
{
    return indexOnShortestPath;
}

void SPV::PointOnShortestPath::setIndexOnShortestPath(unsigned i)
{
    indexOnShortestPath = i;
}

double SPV::PointOnShortestPath::getDistanceFromStartPoint()
{
    return distanceFromStartPoint;
}

double SPV::PointOnShortestPath::getDistanceFromEndPoint()
{
    return distanceFromEndPoint;
}

void SPV::PointOnShortestPath::setDistanceFromStartPoint(double d)
{
    distanceFromStartPoint = d;
}

void SPV::PointOnShortestPath::setDistanceFromEndPoint(double d)
{
    distanceFromEndPoint = d;
}
