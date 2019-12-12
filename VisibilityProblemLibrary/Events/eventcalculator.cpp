#include "Events/eventcalculator.h"

void SPV::EventCalculator::calculatePathAndBoundaryEvents()
{

}

std::vector<SPV::SweptSegment *> SPV::EventCalculator::getStartSideSegmentsForFirstPoint()
{
    std::vector<SweptSegment *> endSideSegments = shortestPath.at(1)->getSegmentsFromEnd();
    std::vector<SweptSegment *> startSideSegments = shortestPath.at(1)->getSegmentsFromStart();
}


std::vector<Segment *> getEndSideSegmentsForLastPoint()
{

}
