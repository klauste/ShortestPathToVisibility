#include "ShortestPath/shortestpathtreecalculator.h"

const std::vector<std::shared_ptr<SPV::PointOnShortestPath>> SPV::ShortestPathTreeCalculator::getShortestPath()
{
    calculateShortestPath();
    return shortestPath;
}

void SPV::ShortestPathTreeCalculator::calculateShortestPath()
{
    ShortestPathCalculator::calculateShortestPath();

    if (directPathBetweenFinalPointsExists()) {
        return;
    }

    rootAtEndPoint = false;
    rootPoint = startPoint;
    currentPointOnShortestPathIndex = 0;
    setSweptSegmentsInShortestPath(facesFromStartToEnd.at(0)->faceHandle);
    shortestPathTree.clear();

    rootAtEndPoint = true;
    rootPoint = endPoint;
    currentPointOnShortestPathIndex = shortestPath.size() - 1;
    setSweptSegmentsInShortestPath(facesFromStartToEnd.back()->faceHandle);
    shortestPathTree.clear();
}

void SPV::ShortestPathTreeCalculator::setSweptSegmentsInShortestPath(CDT::Face_handle firstFace) {
    int oppositePointIndex, leftPointIndex, rightPointIndex;

    std::shared_ptr<PointOnShortestPathTree> startPointOnTree = std::make_shared<PointOnShortestPathTree>(rootPoint);

    addPointToShortestPathTree(startPointOnTree);

    // add all points in the start triangle
    for (int i = 0; i < 3; i++) {
        std::shared_ptr<PointOnShortestPathTree> trianglePoint = std::make_shared<PointOnShortestPathTree>(
            firstFace->vertex(i)->point(),
            startPointOnTree
        );
        addPointToShortestPathTree(trianglePoint);
    }

    // Recursively handle the diagonals on all three sides. Each triangle can have a
    // maximum of three triangle sharing a diagonal. In CGAL you get the triangle opposite
    // a point by calling the neighbour function with the index, the opposite point has
    // in the current triangle face.
    for (oppositePointIndex = 0; oppositePointIndex < 3; oppositePointIndex++) {
        std::vector<std::shared_ptr<PointOnShortestPathTree>> leftFunnel;
        std::vector<std::shared_ptr<PointOnShortestPathTree>> rightFunnel;

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
    std::shared_ptr<PointOnShortestPathTree> apex,
    std::shared_ptr<PointOnShortestPathTree> leftFunnelPoint,
    std::shared_ptr<PointOnShortestPathTree> rightFunnelPoint,
    Point leftTriangleEdgePoint,
    Point rightTriangleEdgePoint
)
{
    auto currentPointOnSp = shortestPath.at(apex->getIndexOnShortestPath());
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

    auto newSegment = std::make_shared<SweptSegment>(
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
   std::shared_ptr<PointOnShortestPathTree> apex,
   std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
   std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
   std::shared_ptr<ShortestPathTreeCalculator::triangulationIndexInformation> tI
) {
    Point leftTriangleEdgePoint = currentFace->vertex(tI->leftPointIndex)->point();
    Point rightTriangleEdgePoint = currentFace->vertex(tI->rightPointIndex)->point();
    std::shared_ptr<PointOnShortestPathTree> currentApex;
    std::shared_ptr<PointOnShortestPathTree> currentLeftFunnelPoint;
    std::shared_ptr<PointOnShortestPathTree> currentRightFunnelPoint;
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
        std::shared_ptr<PointOnShortestPathTree> apex,
        std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
        std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
        std::shared_ptr<triangulationIndexInformation> indexInfo
)
{
    auto nextPointOnTree = std::make_shared<PointOnShortestPathTree>(
        nextFace->vertex(indexInfo->nextPointIndex)->point()
    );
    std::vector<std::shared_ptr<PointOnShortestPathTree>> newSplitFunnelRight;
    std::vector<std::shared_ptr<PointOnShortestPathTree>> newSplitFunnelLeft;

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
        std::shared_ptr<PointOnShortestPathTree> apex,
        std::shared_ptr<PointOnShortestPathTree> firstPointOnTree,
        bool lastPointOnLeftFunnel
) {
    if (currentFace->info().inDomain()) {
        std::vector<std::shared_ptr<PointOnShortestPathTree>> firstFunnel;
        std::vector<std::shared_ptr<PointOnShortestPathTree>> secondFunnel;
        firstFunnel.push_back(firstPointOnTree);

        // Calling the function with this argument will result in the following:
        // apex -> leftPointIndex
        // firstPointOnTree -> rightPointIndex
        // next point -> nexPointIndex
        // This is important to remember when splitting further
        auto indexInfo = getTriangulationIndexInformation(
            apex->getPoint(),
            firstPointOnTree->getPoint(),
            currentFace
        );
        std::shared_ptr<PointOnShortestPathTree> secondPointOnTree = std::make_shared<PointOnShortestPathTree>(
            currentFace->vertex(indexInfo->nextPointIndex)->point(),
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
    }
}

void SPV::ShortestPathTreeCalculator::splitFunnelAtLastPoint(
        CDT::Face_handle nextFace,
        std::shared_ptr<PointOnShortestPathTree> apex,
        std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
        std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
        bool nextPointOnLeftFunnel,
        std::shared_ptr<triangulationIndexInformation> indexInfo
)
{
    std::shared_ptr<PointOnShortestPathTree> newApex;
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

    auto nextPointOnTree = std::make_shared<PointOnShortestPathTree>(
        nextFace->vertex(indexInfo->nextPointIndex)->point(),
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
        std::shared_ptr<PointOnShortestPathTree> apex,
        std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
        std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel,
        bool nextPointOnLeftFunnel,
        std::shared_ptr<triangulationIndexInformation> indexInfo,
        unsigned newApexIndex
) {
    std::vector<std::shared_ptr<PointOnShortestPathTree>> funnelToApexIndex;
    std::vector<std::shared_ptr<PointOnShortestPathTree>> funnelWithNextPoint;
    std::vector<std::shared_ptr<PointOnShortestPathTree>> funnelAfterApexIndex;
    unsigned i;

    std::shared_ptr<PointOnShortestPathTree> newApex;

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

    auto nextPointOnTree = std::make_shared<PointOnShortestPathTree>(
        nextFace->vertex(indexInfo->nextPointIndex)->point(),
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
    std::shared_ptr<PointOnShortestPathTree> apex,
    std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
    std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel
) {
    // The next face is the triangle face opposite the vertex which has
    // neighborIndex in the currentFace.
    CDT::Face_handle nextFace = currentFace->neighbor(neighborIndex);

    // Find the index of the left point, the right point and the index of the point not on the current funnel
    // i.e. Point v in https://graphics.stanford.edu/courses/cs268-09-winter/notes/handout7.pdf, page 6.
    auto tI = getTriangulationIndexInformation(
        leftFunnel.back()->getPoint(),
        rightFunnel.back()->getPoint(),
        nextFace
    );

    // End of recursion: nextFace is outside of the constrained triangulation
    if (!nextFace->info().inDomain()) {
        calculateSweptSegments(
            nextFace,
            apex,
            leftFunnel,
            rightFunnel,
            tI
        );
        return;
    }

    int leftFunnelSize = leftFunnel.size();
    int rightFunnelSize = rightFunnel.size();

    auto info = findPredecessor(
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
}

std::shared_ptr<SPV::ShortestPathTreeCalculator::predecessorInfo> SPV::ShortestPathTreeCalculator::findPredecessor(
        Point p,
        std::shared_ptr<PointOnShortestPathTree> apex,
        std::vector<std::shared_ptr<PointOnShortestPathTree>> &leftFunnel,
        std::vector<std::shared_ptr<PointOnShortestPathTree>> &rightFunnel
) {
    int leftFunnelSize = leftFunnel.size();
    Point first, second;
    auto result = std::make_shared<predecessorInfo>();

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

bool SPV::ShortestPathTreeCalculator::allPointsOnShortestPathHandled()
{
    if (rootAtEndPoint) {
        return currentPointOnShortestPathIndex <= 1;
    }
    return currentPointOnShortestPathIndex >= shortestPath.size() - 1;
}

Point SPV::ShortestPathTreeCalculator::getNextPointOnShortestPath()
{
    int index;
    if (rootAtEndPoint) {
        index = currentPointOnShortestPathIndex - 1;
    } else {
        index = currentPointOnShortestPathIndex + 1;
    }
    return shortestPath.at(index)->getPoint();
}

bool SPV::ShortestPathTreeCalculator::isPointOnShortestPath(std::shared_ptr<PointOnShortestPathTree> pointToCheck)
{
    if (allPointsOnShortestPathHandled()) {
        return false;
    }
    if (getNextPointOnShortestPath() == pointToCheck->getPoint()) {
        // Set the shortest path to the
        if (rootAtEndPoint) {
            currentPointOnShortestPathIndex = currentPointOnShortestPathIndex - 1;
        } else {
            currentPointOnShortestPathIndex = currentPointOnShortestPathIndex + 1;
        }
        return true;
    }
    return false;
}

void SPV::ShortestPathTreeCalculator::addPointToShortestPathTree(std::shared_ptr<PointOnShortestPathTree> p)
{
    if (isPointOnShortestPath(p)) {
        p->setIndexOnShortestPath(currentPointOnShortestPathIndex);
    }
    shortestPathTree.push_back(p);
}

std::shared_ptr<SPV::ShortestPathTreeCalculator::triangulationIndexInformation> SPV::ShortestPathTreeCalculator::getTriangulationIndexInformation(
        Point leftPoint,
        Point rightPoint,
        CDT::Face_handle faceHandle
) {
    auto tI = std::make_shared<triangulationIndexInformation>();

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

