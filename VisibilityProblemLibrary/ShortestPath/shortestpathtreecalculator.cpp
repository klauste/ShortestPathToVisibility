#include "ShortestPath/shortestpathtreecalculator.h"

void SPV::ShortestPathTreeCalculator::setSweptSegmentsInShortestPath(CDT::Face_handle firstFace) {
    int oppositePointIndex, leftPointIndex, rightPointIndex;

    SPV::PointOnShortestPathTree *startPointOnTree = new SPV::PointOnShortestPathTree(rootPoint);

    addPointToShortestPathTree(startPointOnTree);

    // add all points in the start triangle
    for (int i = 0; i < 3; i++) {
        SPV::PointOnShortestPathTree * trianglePoint = new SPV::PointOnShortestPathTree(
            new PointWithTriangulationInfo(firstFace, i),
            startPointOnTree
        );
        addPointToShortestPathTree(trianglePoint);
    }

    // Recursively handle the diagonals on all three sides. Each triangle can have a
    // maximum of three triangle sharing a diagonal. In CGAL you get the triangle opposite
    // a point by calling the neighbour function with the index, the opposite point has
    // in the current triangle face.
    for (oppositePointIndex = 0; oppositePointIndex < 3; oppositePointIndex++) {
        std::vector<PointOnShortestPathTree*> leftFunnel;
        std::vector<PointOnShortestPathTree*> rightFunnel;

        leftPointIndex = firstFace->ccw(oppositePointIndex);
        rightPointIndex = firstFace->cw(oppositePointIndex);

        leftFunnel.push_back(shortestPathTree.at(leftPointIndex + 1));
        rightFunnel.push_back(shortestPathTree.at(rightPointIndex + 1));

        splitFunnel(
            firstFace,
            oppositePointIndex,
            startPointOnTree,
            leftFunnel,
            rightFunnel
        );
    }
}

void SPV::ShortestPathTreeCalculator::calculateAndAddSegment(
    PointOnShortestPathTree* apex,
    PointOnShortestPathTree* leftFunnelPoint,
    PointOnShortestPathTree* rightFunnelPoint,
    Point leftTriangleEdgePoint,
    Point rightTriangleEdgePoint
)
{
    std::cout << "Calculate and Add Segment" << std::endl;
    std::cout << "local apex" << apex->getPoint() << std::endl;

    PointOnShortestPath *currentPointOnSp = shortestPath.at(apex->getIndexOnShortestPath());
    Point leftIntersectionPoint = leftFunnelPoint->getPoint();
    bool leftPointIsVertex = true;
    Point rightIntersectionPoint = rightFunnelPoint->getPoint();
    bool rightPointIsVertex = true;

    // Is the left funnel end point on the current triangle? If not calculate its
    // position
    if (!gU.pointsAreEqual(leftIntersectionPoint, leftTriangleEdgePoint)) {
        // The left point of the segment is the intersection of the current
        // polygon edge and the ray through the apex and the first point on
        // the left funnel
        boost::variant<Point, bool> result =
                gU.getIntersectionBetweenLineAndSegment(
                    Line(leftIntersectionPoint, apex->getPoint()),
                    leftTriangleEdgePoint,
                    rightTriangleEdgePoint
        );
        if (result.type() == typeid(bool)) {
            std::cout << "No intersection found on triangle edge";
        } else {
            leftIntersectionPoint = boost::get<Point>(result);
            if (!gU.pointsAreEqual(leftIntersectionPoint, leftTriangleEdgePoint)) {
                leftPointIsVertex = false;
            } else {
                leftIntersectionPoint = leftTriangleEdgePoint;
            }
        }
    }

    // Is the right funnel end point on the current triangle
    if (!gU.pointsAreEqual(rightIntersectionPoint, rightTriangleEdgePoint)) {
        // The right point of the segment is the intersection of the current
        // polygon edge and the ray through the apex and the first point on
        // the right funnel
        boost::variant<Point, bool> result =
                gU.getIntersectionBetweenLineAndSegment(
                    Line(rightIntersectionPoint, apex->getPoint()),
                    leftTriangleEdgePoint,
                    rightTriangleEdgePoint
        );
        if (result.type() == typeid(bool)) {
            std::cout << "No intersection found on triangle edge";
        } else {
            rightIntersectionPoint = boost::get<Point>(result);
            if (!gU.pointsAreEqual(rightIntersectionPoint, rightTriangleEdgePoint)) {
                rightPointIsVertex = false;
            } else {
                rightIntersectionPoint = rightTriangleEdgePoint;
            }
        }
    }

    // If the points are equal (which can happen if some points in the polygon are colinear), don't add them
    if (leftIntersectionPoint == rightIntersectionPoint) {
        return;
    }

    SweptSegment *newSegment = new SweptSegment(
                leftIntersectionPoint,
                leftPointIsVertex,
                rightIntersectionPoint,
                rightPointIsVertex
    );

    if (rootAtEndPoint) {
        currentPointOnSp->addSegmentFromEnd(newSegment);
    } else {
        currentPointOnSp->addSegmentFromStart(newSegment);
    }
}

void SPV::ShortestPathTreeCalculator::calculateSweptSegments(
   CDT::Face_handle currentFace,
   SPV::PointOnShortestPathTree* apex,
   std::vector<SPV::PointOnShortestPathTree*> &leftFunnel,
   std::vector<SPV::PointOnShortestPathTree*> &rightFunnel,
   SPV::ShortestPathTreeCalculator::triangulationIndexInformation *tI
) {
    Point leftTriangleEdgePoint = currentFace->vertex(tI->leftPointIndex)->point();
    Point rightTriangleEdgePoint = currentFace->vertex(tI->rightPointIndex)->point();
    PointOnShortestPathTree *currentApex;
    PointOnShortestPathTree *currentLeftFunnelPoint;
    PointOnShortestPathTree *currentRightFunnelPoint;
    int i;

    // Calculate the swept segments on the left funnel (if any)
    if (leftFunnel.size() > 1) {
        for (i = leftFunnel.size() - 2; i >= 0; i--) {
            currentApex = leftFunnel.at(i);
            if (currentApex->isPartOfShortestPath()) {
                currentLeftFunnelPoint = leftFunnel.at(i + 1);
                if (i > 0) {
                    currentRightFunnelPoint = leftFunnel.at(i - 1);
                } else {
                    currentRightFunnelPoint = apex;
                }
                calculateAndAddSegment(currentApex, currentLeftFunnelPoint, currentRightFunnelPoint, leftTriangleEdgePoint, rightTriangleEdgePoint);
            }
        }
    }

    // Check the apex
    if (apex->isPartOfShortestPath()) {
        calculateAndAddSegment(apex, leftFunnel.at(0), rightFunnel.at(0), leftTriangleEdgePoint, rightTriangleEdgePoint);
    }

    // Calculate the swept segments on the right funnel. The direction is different here, so that
    // the order from left to right is kept
    if (rightFunnel.size() > 1) {
        for (i = 0; i < rightFunnel.size() - 1; i++) {
            currentApex = rightFunnel.at(i);
            if (currentApex->isPartOfShortestPath()) {
                currentRightFunnelPoint = rightFunnel.at(i + 1);
                if (i > 0) {
                    currentLeftFunnelPoint = rightFunnel.at(i - 1);
                } else {
                    currentLeftFunnelPoint = apex;
                }
                calculateAndAddSegment(currentApex, currentLeftFunnelPoint, currentRightFunnelPoint, leftTriangleEdgePoint, rightTriangleEdgePoint);
            }
        }
    }
}

void SPV::ShortestPathTreeCalculator::splitFunnelAtApex(
        CDT::Face_handle nextFace,
        SPV::PointOnShortestPathTree *apex,
        std::vector<SPV::PointOnShortestPathTree*> &leftFunnel,
        std::vector<SPV::PointOnShortestPathTree*> &rightFunnel,
        triangulationIndexInformation *indexInfo
)
{
    PointOnShortestPathTree *nextPointOnTree = new SPV::PointOnShortestPathTree(
        new PointWithTriangulationInfo(nextFace, indexInfo->nextPointIndex)
    );
    std::vector<PointOnShortestPathTree* > newSplitFunnelRight;
    std::vector<PointOnShortestPathTree* > newSplitFunnelLeft;

    addPointToShortestPathTree(nextPointOnTree);

    // Add the next point to the split funnel
    newSplitFunnelRight.push_back(nextPointOnTree);
    newSplitFunnelLeft.push_back(nextPointOnTree);

    splitFunnel(
        nextFace,
        indexInfo->rightPointIndex,
        apex,
        leftFunnel,
        newSplitFunnelRight
    );
    splitFunnel(
        nextFace,
        indexInfo->leftPointIndex,
        apex,
        newSplitFunnelLeft,
        rightFunnel
    );
    return;
}

void SPV::ShortestPathTreeCalculator::handleTriangleBeyondLastEdge(
        CDT::Face_handle currentFace,
        SPV::PointOnShortestPathTree *apex,
        SPV::PointOnShortestPathTree *firstPointOnTree,
        bool lastPointOnLeftFunnel
) {
    if (currentFace->info().inDomain()) {
        std::vector<SPV::PointOnShortestPathTree*> firstFunnel;
        std::vector<SPV::PointOnShortestPathTree*> secondFunnel;
        firstFunnel.push_back(firstPointOnTree);

        // Calling the function with this argument will result in the following:
        // apex -> leftPointIndex
        // firstPointOnTree -> rightPointIndex
        // next point -> nexPointIndex
        // This is important to remember when splitting further
        triangulationIndexInformation *indexInfo = getTriangulationIndexInformation(
            apex->getPoint(),
            firstPointOnTree->getPoint(),
            currentFace
        );
        SPV::PointOnShortestPathTree* secondPointOnTree = new SPV::PointOnShortestPathTree(
            new PointWithTriangulationInfo(currentFace, indexInfo->nextPointIndex),
            apex
        );
        addPointToShortestPathTree(secondPointOnTree);
        secondFunnel.push_back(secondPointOnTree);

        // Chosse the correct left and right funnel depending on lastPointOnLeftFunnel
        if (lastPointOnLeftFunnel) {
            // Try to go further left
            handleTriangleBeyondLastEdge(
                currentFace->neighbor(indexInfo->rightPointIndex),
                apex,
                secondPointOnTree,
                true
            );

            // Split the funnel ond the diagonal opposite the current
            // apex (i.e. with index leftPointIndex)
            splitFunnel(
                currentFace,
                indexInfo->leftPointIndex,
                apex,
                secondFunnel,
                firstFunnel
            );
        } else {
            // Split the funnel ond the diagonal opposite the current
            // apex (i.e. with index leftPointIndex)
            splitFunnel(
                currentFace,
                indexInfo->leftPointIndex,
                apex,
                firstFunnel,
                secondFunnel
            );

            // Try to go further right
            handleTriangleBeyondLastEdge(
                currentFace->neighbor(indexInfo->rightPointIndex),
                apex,
                secondPointOnTree,
                false
            );
        }
        delete indexInfo;
    }
}

void SPV::ShortestPathTreeCalculator::splitFunnelAtLastPoint(
        CDT::Face_handle nextFace,
        SPV::PointOnShortestPathTree *apex,
        std::vector<SPV::PointOnShortestPathTree*> &leftFunnel,
        std::vector<SPV::PointOnShortestPathTree*> &rightFunnel,
        bool nextPointOnLeftFunnel,
        triangulationIndexInformation *indexInfo
)
{
    SPV::PointOnShortestPathTree* newApex;
    unsigned neigborIndex;
    CDT::Face_handle faceBeyondSplittingEdge;

    // First build up the new left/right funnel
    if (nextPointOnLeftFunnel) {
        newApex = leftFunnel.back();
        neigborIndex = indexInfo->leftPointIndex;
    } else {
        newApex = rightFunnel.back();
        neigborIndex = indexInfo->rightPointIndex;
    }

    SPV::PointOnShortestPathTree* nextPointOnTree = new SPV::PointOnShortestPathTree(
        new PointWithTriangulationInfo(nextFace, indexInfo->nextPointIndex),
        newApex
    );
    addPointToShortestPathTree(nextPointOnTree);

    if (nextPointOnLeftFunnel) {
        faceBeyondSplittingEdge = nextFace->neighbor(indexInfo->rightPointIndex);

        // Need to check the triangles on the left first to keep the recursion order
        handleTriangleBeyondLastEdge(
            faceBeyondSplittingEdge,
            newApex,
            nextPointOnTree,
            true
        );

        leftFunnel.push_back(nextPointOnTree);
    } else {
        rightFunnel.push_back(nextPointOnTree);
    }

    // Call split funnel with the incremented left/right funnel
    splitFunnel(
        nextFace,
        neigborIndex,
        apex,
        leftFunnel,
        rightFunnel
    );

    // Now handle the triangle if the new splitting edge is on the right funnel
    if (!nextPointOnLeftFunnel) {
        faceBeyondSplittingEdge = nextFace->neighbor(indexInfo->leftPointIndex);

        // Need to check the triangles on the left first to keep the recursion order
        handleTriangleBeyondLastEdge(
            faceBeyondSplittingEdge,
            newApex,
            nextPointOnTree,
            false
        );
    }
}

void SPV::ShortestPathTreeCalculator::splitFunnelAtMidPoint(
        CDT::Face_handle nextFace,
        SPV::PointOnShortestPathTree* apex,
        std::vector<SPV::PointOnShortestPathTree*> &leftFunnel,
        std::vector<SPV::PointOnShortestPathTree*> &rightFunnel,
        bool nextPointOnLeftFunnel,
        triangulationIndexInformation *indexInfo,
        unsigned newApexIndex
) {
    std::vector<SPV::PointOnShortestPathTree*> funnelToApexIndex;
    std::vector<SPV::PointOnShortestPathTree*> funnelWithNextPoint;
    std::vector<SPV::PointOnShortestPathTree*> funnelAfterApexIndex;
    unsigned i;

    SPV::PointOnShortestPathTree* newApex;

    if (nextPointOnLeftFunnel) {
        for (i = 0; i <= newApexIndex; i++) {
            funnelToApexIndex.push_back(leftFunnel.at(i));
        }
        for (i = newApexIndex + 1; i < leftFunnel.size(); i++) {
            funnelAfterApexIndex.push_back(leftFunnel.at(i));
        }
        newApex = leftFunnel.at(newApexIndex);
    } else {
        for (i = 0; i <= newApexIndex; i++) {
            funnelToApexIndex.push_back(rightFunnel.at(i));
        }
        for (i = newApexIndex + 1; i < rightFunnel.size(); i++) {
            funnelAfterApexIndex.push_back(rightFunnel.at(i));
        }
        newApex = rightFunnel.at(newApexIndex);
    }

    SPV::PointOnShortestPathTree *nextPointOnTree = new SPV::PointOnShortestPathTree(
        new PointWithTriangulationInfo(nextFace, indexInfo->nextPointIndex),
        newApex
    );

    addPointToShortestPathTree(nextPointOnTree);
    funnelWithNextPoint.push_back(nextPointOnTree);
    funnelToApexIndex.push_back(nextPointOnTree);

    // Split the new funnels
    if (nextPointOnLeftFunnel) {
        splitFunnel(
            nextFace,
            indexInfo->rightPointIndex,
            newApex,
            funnelAfterApexIndex,
            funnelWithNextPoint
        );
        splitFunnel(
            nextFace,
            indexInfo->leftPointIndex,
            apex,
            funnelToApexIndex,
            rightFunnel
        );
    } else {
        splitFunnel(
            nextFace,
            indexInfo->rightPointIndex,
            apex,
            leftFunnel,
            funnelToApexIndex
        );
        splitFunnel(
            nextFace,
            indexInfo->leftPointIndex,
            newApex,
            funnelWithNextPoint,
            funnelAfterApexIndex
        );
    }
}

void SPV::ShortestPathTreeCalculator::splitFunnel(
    CDT::Face_handle currentFace,
    int neighborIndex,
    SPV::PointOnShortestPathTree* apex,
    std::vector<SPV::PointOnShortestPathTree*> &leftFunnel,
    std::vector<SPV::PointOnShortestPathTree*> &rightFunnel
) {
    // The next face is the triangle face opposite the vertex which has
    // neighborIndex in the currentFace.
    CDT::Face_handle nextFace = currentFace->neighbor(neighborIndex);

    std::cout << "Apex: " << apex->getPoint() << std::endl;
    std::cout << "Left Funnel: " << std::endl;
    for (unsigned i =0; i < leftFunnel.size(); i++) {
        std::cout <<leftFunnel.at(i)->getPoint() << std::endl;
    }
    std::cout << "Right Funnel: " << std::endl;
    for (unsigned i =0; i < rightFunnel.size(); i++) {
        std::cout <<rightFunnel.at(i)->getPoint() << std::endl;
    }
    // Find the index of the left point, the right point and the index of the point not on the current funnel
    // i.e. Point v in https://graphics.stanford.edu/courses/cs268-09-winter/notes/handout7.pdf, page 6.
    triangulationIndexInformation *tI = getTriangulationIndexInformation(
        leftFunnel.back()->getPoint(),
        rightFunnel.back()->getPoint(),
        nextFace
    );

    std::cout << "next point: " << tI->nextPoint << std::endl;
    // End of recursion: nextFace is outside of the constrained triangulation
    if (!nextFace->info().inDomain()) {
        calculateSweptSegments(
            nextFace,
            apex,
            leftFunnel,
            rightFunnel,
            tI
        );
        delete tI;
        return;
    }

    int leftFunnelSize = leftFunnel.size();
    int rightFunnelSize = rightFunnel.size();

    predecessorInfo* info = findPredecessor(
        tI->nextPoint,
        apex,
        leftFunnel,
        rightFunnel
    );

    // Handle the splitting if the next point is
    // the last point on one of the funnels
    if (info->isLastPointOnFunnel) {
        splitFunnelAtLastPoint(
            nextFace,
            apex,
            leftFunnel,
            rightFunnel,
            info->onLeftFunnel,
            tI
        );
        delete info;
        delete tI;
        return;
    }

    // Split the funnel at the apex
    if (info->isApex) {
        splitFunnelAtApex(
            nextFace,
            apex,
            leftFunnel,
            rightFunnel,
            tI
        );
        delete info;
        delete tI;
        return;
    }

    // Last possibility: point is in the middle of one funnel
    splitFunnelAtMidPoint(
        nextFace,
        apex,
        leftFunnel,
        rightFunnel,
        info->onLeftFunnel,
        tI,
        info->indexOnFunnel
    );
    delete info;
    delete tI;
}

SPV::ShortestPathTreeCalculator::predecessorInfo* SPV::ShortestPathTreeCalculator::findPredecessor(
        Point p,
        SPV::PointOnShortestPathTree* apex,
        std::vector<SPV::PointOnShortestPathTree*> &leftFunnel,
        std::vector<SPV::PointOnShortestPathTree*> &rightFunnel
) {
    int leftFunnelSize = leftFunnel.size();
    Point first, second;
    predecessorInfo* result = new predecessorInfo();

    if (leftFunnel.size() > 1) {
        for (int i = leftFunnel.size() - 1; i > 0; i--) {
           first = leftFunnel.at(i - 1)->getPoint();
            second = leftFunnel.at(i)->getPoint();
            if (gU.isOnLeftSide(first, second, p)) {
                result->onLeftFunnel = true;
                result->indexOnFunnel = i;
                if (i == leftFunnel.size() - 1) {
                    result->isLastPointOnFunnel = true;
                }
                return result;
            }
        }
    }

    first = apex->getPoint();
    second = leftFunnel.at(0)->getPoint();
    if (gU.isOnLeftSide(first, second, p)) {
        result->onLeftFunnel = true;
        result->indexOnFunnel = 0;
        if (leftFunnel.size() == 1) {
            result->isLastPointOnFunnel = true;
        }
        return result;
    }

    second = rightFunnel.at(0)->getPoint();
    if (gU.isOnLeftSide(first, second, p)) {
        result->isApex = true;
        return result;
    }

    // The predecessor must be on the right funnel
    result->onRightFunnel = true;

    if (rightFunnel.size() > 1) {
        for (int i = 0; i < rightFunnel.size() - 1; i++) {
            first = rightFunnel.at(i) ->getPoint();
            second = rightFunnel.at(i + 1)->getPoint();
            if (gU.isOnLeftSide(first, second, p)) {
                result->indexOnFunnel = i;
                return result;
            }
        }
    }

    // return the last point on the right Funnel
    result->indexOnFunnel = rightFunnel.size() - 1;
    result->isLastPointOnFunnel = true;
    return result;
}

SPV::ShortestPathTreeCalculator::triangulationIndexInformation* SPV::ShortestPathTreeCalculator::getTriangulationIndexInformation(
        Point leftPoint,
        Point rightPoint,
        CDT::Face_handle faceHandle
) {
    triangulationIndexInformation* tI = new triangulationIndexInformation();

    // Find the index of the left point, the right point and the index of the point not on the current funnel
    // i.e. Point v in https://graphics.stanford.edu/courses/cs268-09-winter/notes/handout7.pdf, page 6.
    for (unsigned i = 0; i < 3; i++) {
        Point p = faceHandle->vertex(i)->point();

        if (p == leftPoint) {
            tI->leftPointIndex = i;
        } else if (p == rightPoint) {
            tI->rightPointIndex = i;
        } else {
            tI->nextPointIndex = i;
            tI->nextPoint = p;
        }
    }
    return tI;
}

