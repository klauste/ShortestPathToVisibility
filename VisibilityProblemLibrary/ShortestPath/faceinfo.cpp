#include "ShortestPath/faceinfo.h"
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
