#include "ShortestPath/faceinfo.h"
bool SPV::FaceInfo::inDomain() {
    return nestingLevel%2 == 1;
}

int SPV::FaceInfo::getNestingLevel() {
    return nestingLevel;
}

void SPV::FaceInfo::setNestingLevel(int nl) {
    nestingLevel = nl;
}
