#ifndef SPVFACEINFO_H
#define SPVFACEINFO_H

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

#endif // SPVFACEINFO_H
