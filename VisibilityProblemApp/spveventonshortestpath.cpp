#include "spveventonshortestpath.h"

Point SPV::EventOnShortestPath::getFirstDefiningPoint() {
    return firstDefiningPoint;
}
Point SPV::EventOnShortestPath::getSecondDefiningPoint() {
    return secondDefiningPoint;
}

Point SPV::EventOnShortestPath::getFirstPointIntersection() {
    return firstPointIntersection;
}

Point SPV::EventOnShortestPath::getSecondPointIntersection() {
    return secondPointIntersection;
}

void SPV::EventOnShortestPath::setFirstPointIntersection(Point p) {
    firstPointIntersection = p;
}

void SPV::EventOnShortestPath::setSecondPointIntersection(Point p) {
    secondPointIntersection = p;
}
