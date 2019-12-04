#include "spvfaceinfo.h"
SPV::FaceInfo::FaceInfo() {
    hasShortestPathEvents = false;
}

bool SPV::FaceInfo::inDomain() {
    return nestingLevel%2 == 1;
}

int SPV::FaceInfo::getNestingLevel() {
    return nestingLevel;
}

void SPV::FaceInfo::setNestingLevel(int nl) {
    nestingLevel = nl;
}

void SPV::FaceInfo::addShortestPathEvent(SPV::EventOnShortestPath* spr) {
    shortestPathEvents.push_back(spr);
    hasShortestPathEvents = true;
}

std::vector<SPV::EventOnShortestPath*> SPV::FaceInfo::getShortestPathEvents() {
    return shortestPathEvents;
}

bool SPV::FaceInfo::getHasShortestPathEvent(Point startingPoint, Point endPoint) {
    int eventSize = shortestPathEvents.size();

    for (int i = 0; i < eventSize; i++) {
        if (startingPoint == shortestPathEvents.at(i)->getFirstDefiningPoint() && endPoint == shortestPathEvents.at(i)->getSecondDefiningPoint()) {
            return true;
        }
    }
    return false;
}

SPV::EventOnShortestPath* SPV::FaceInfo::getShortestPathEvent(Point startingPoint, Point endPoint) {
    int eventSize = shortestPathEvents.size();

    for (int i = 0; i < eventSize; i++) {
        if (startingPoint == shortestPathEvents.at(i)->getFirstDefiningPoint() && endPoint == shortestPathEvents.at(i)->getSecondDefiningPoint()) {
            return shortestPathEvents.at(i);
        }
    }
    return nullptr;
}

bool SPV::FaceInfo::getHasShortestPathEvents() {
    return hasShortestPathEvents;
}
