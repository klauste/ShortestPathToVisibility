#ifndef FACEINFO_H
#define FACEINFO_H

#include <vector>
#include <boost/bind.hpp>

namespace SPV {
    class FaceInfo {
    public:
        FaceInfo();
        bool inDomain();
        int getNestingLevel();
        void setNestingLevel(int nl);
    private:
        int nestingLevel;
        bool hasShortestPathEvents = false;
        int firstFromRightToLeft;
    };
}

#endif // FACEINFO_H
