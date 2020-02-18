#ifndef FACEINFO_H
#define FACEINFO_H

#include <vector>
#include <boost/bind.hpp>

namespace SPV {
    /**
     * @brief The FaceInfo class contains information about a triangulation face. In particular, it contains
     * information if a give face is inside of the polygon or not. For further information, consult
     * the CGAL documentation about triangulation. (Good luck with that!)
     */
    class FaceInfo {
    public:
        /**
         * @brief inDomain returns the flag indicating if this face is inside of the polygon or not
         * @return
         */
        bool inDomain();

        /**
         * @brief getNestingLevel gets the nesting level of this face
         * @return
         */
        int getNestingLevel();

        /**
         * @brief setNestingLevel sets the nesting level of this face
         * @param nl
         */
        void setNestingLevel(int nl);
    private:
        /**
         * @brief nestingLevel stores this face's nesting level
         */
        int nestingLevel;
    };
}

#endif // FACEINFO_H
