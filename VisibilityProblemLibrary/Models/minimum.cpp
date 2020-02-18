#include "Models/minimum.h"

void SPV::Minimum::setStartSideIntersectionOnLoS(Point p) {
    startSideIntersectionOnLoS = p;
}

void SPV::Minimum::setEndSideIntersectionOnLoS(Point p) {
    endSideIntersectionOnLoS = p;
}

void SPV::Minimum::setStartSideIntersectionOnEdge(Point p) {
    startSideIntersectionOnEdge = p;
}

void SPV::Minimum::setEndSideIntersectionOnEdge(Point p) {
    endSideIntersectionOnEdge = p;
}

Point SPV::Minimum::getStartSideIntersectionOnLoS()
{
    return startSideIntersectionOnLoS;
}

Point SPV::Minimum::getStartSideIntersectionOnEdge()
{
    return startSideIntersectionOnEdge;
}

Point SPV::Minimum::getEndSideIntersectionOnLoS() {
    return endSideIntersectionOnLoS;
}

Point SPV::Minimum::getEndSideIntersectionOnEdge() {
    return endSideIntersectionOnEdge;
}

void SPV::Minimum::setEventSegment(EventSegment *eS) {
    eventSegment = eS;
}

SPV::EventSegment* SPV::Minimum::getEventSegment() {
    return eventSegment;
}

void SPV::Minimum::setIsInDiscArea(bool value) {
    isInDiscArea = value;
}

bool SPV::Minimum::getIsInDiscArea() {
    return isInDiscArea;
}

void SPV::Minimum::setDiscRadius(double r) {
    discRadius = r;
}

double SPV::Minimum::getDiscRadius() {
    if (isInDiscArea) {
        return discRadius;
    }
    return 0;
}

void SPV::Minimum::setDistance(double d) {
    distance = d;
}

double SPV::Minimum::getDistance() {
    return distance;
}

void SPV::Minimum::setMinSectorStart(bool b)
{
    minSectorStart = b;
}

void SPV::Minimum::setMinSectorEnd(bool b)
{
    minSectorEnd = b;
}

bool SPV::Minimum::isMinSectorStart()
{
    return minSectorStart;
}

bool SPV::Minimum::isMinSectorEnd()
{
    return minSectorEnd;
}

void SPV::Minimum::setDiscOnStartSide(bool b)
{
    discOnStartSide = b;
}

bool SPV::Minimum::isDiscOnStartSide()
{
    return discOnStartSide;
}
