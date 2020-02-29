#include "ShortestPath/shortestpathcalculator.h"

SPV::ShortestPathCalculator::ShortestPathCalculator(const Polygon &p, Point s, Point e) {
    triangulationCalculator = Triangulation(p);
    polygon = p;
    triangulation = triangulationCalculator.getTriangulation();
    startPoint = s;
    endPoint = e;
    checkDirectPath();
}

const std::vector<std::shared_ptr<SPV::PointOnShortestPath>> SPV::ShortestPathCalculator::getShortestPath()
{
    calculateShortestPath();
    return shortestPath;
}

void SPV::ShortestPathCalculator::calculateShortestPath() {
    if (directPathBetweenFinalPoints) {
        shortestPath.push_back(std::make_shared<PointOnShortestPath>(startPoint));
        shortestPath.push_back(std::make_shared<PointOnShortestPath>(endPoint));
        return;
    }
    setFacesFromStartToEndPoint();

    std::vector<std::shared_ptr<PointOnShortestPath>> forwardVector;
    auto currentFaceOnPath = facesFromStartToEnd.at(0);
    unsigned lastIndex = facesFromStartToEnd.size() - 1;
    CDT::Face_handle currentFaceHandle = currentFaceOnPath->faceHandle;
    CDT::Face_handle lastFace = facesFromStartToEnd.at(lastIndex)->faceHandle;

    int nextFaceIndex = currentFaceOnPath->nextFaceIndex;
    auto firstPoint = std::make_shared<PointOnShortestPath>(startPoint);
    firstPoint->setIndexOnShortestPath(0);
    auto lastPoint = std::make_shared<PointOnShortestPath>(endPoint);

    shortestPath.push_back(firstPoint);

    int vertexIndex = currentFaceHandle->ccw(nextFaceIndex);
    auto leftPoint = std::make_shared<PointOnShortestPath>(currentFaceHandle->vertex(vertexIndex)->point());
    funnelLeftPath.push_back(firstPoint);
    funnelLeftPath.push_back(leftPoint);

    vertexIndex = currentFaceHandle->cw(nextFaceIndex);
    std::shared_ptr<PointOnShortestPath> rightPoint = std::make_shared<PointOnShortestPath>(currentFaceHandle->vertex(vertexIndex)->point());
    funnelRightPath.push_back(firstPoint);
    funnelRightPath.push_back(rightPoint);

    // Loop over all the diagonals
    for (unsigned i = 1; i < facesFromStartToEnd.size() - 1; i++) {
        bool startOnLeftPath = true;
        currentFaceOnPath = facesFromStartToEnd.at(i);
        currentFaceHandle = currentFaceOnPath->faceHandle;
        nextFaceIndex = currentFaceOnPath->nextFaceIndex;

        // The next point to be handled is the one which is different from the left or right point
        vertexIndex = currentFaceHandle->ccw(nextFaceIndex);
        auto nextPoint = std::make_shared<PointOnShortestPath>(currentFaceHandle->vertex(vertexIndex)->point());

        // If the next shortest path point is the same as the left point, set the next point to the right point
        if (nextPoint->getPoint() == leftPoint->getPoint()) {
            startOnLeftPath = false;
            vertexIndex = currentFaceHandle->cw(nextFaceIndex);
            nextPoint = std::make_shared<PointOnShortestPath>(currentFaceHandle->vertex(vertexIndex)->point());
            rightPoint = nextPoint;
        } else {
            leftPoint = nextPoint;
        }

        forwardVector.clear();
        // Check if nextPoint is part of the right or left sleeve
        if (startOnLeftPath) {
            // Add the elements from end to front to forwardVector
            for (int j = funnelRightPath.size() - 1; j >= 0; j--) {
                forwardVector.push_back(funnelRightPath.at(j));
                funnelRightPath.pop_back();
            }
            handleNextPoint(funnelLeftPath, forwardVector, nextPoint, false);
            for (int j = forwardVector.size() - 1; j >= 0; j--) {
                funnelRightPath.push_back(forwardVector.at(j));
            }
        } else {
            // Add the elements from end to front to forwardVector
            for (int j = funnelLeftPath.size() - 1; j >= 0; j--) {
                forwardVector.push_back(funnelLeftPath.at(j));
                funnelLeftPath.pop_back();
            }
            handleNextPoint(funnelRightPath, forwardVector, nextPoint, true);
            for (int j = forwardVector.size() - 1; j >= 0; j--) {
                funnelLeftPath.push_back(forwardVector.at(j));
            }
        }
    }

    // Handle the last point
    forwardVector.clear();
    for (int i = funnelRightPath.size() - 1; i >= 0; i--) {
        forwardVector.push_back(funnelRightPath.at(i));
        funnelRightPath.pop_back();
    }

    handleNextPoint(funnelLeftPath, forwardVector, lastPoint, false);

    // Add the last points to the shortestPath
    for (int i = 1; i < funnelLeftPath.size(); i++) {
        std::shared_ptr<PointOnShortestPath> currentPoint = funnelLeftPath.at(i);
        currentPoint->setIndexOnShortestPath(shortestPath.size());
        shortestPath.push_back(currentPoint);
    }

    setDistances();
    funnelLeftPath.clear();
    funnelRightPath.clear();
}

void SPV::ShortestPathCalculator::handleNextPoint(
    std::vector<std::shared_ptr<PointOnShortestPath>> &backwardPath,
    std::vector<std::shared_ptr<PointOnShortestPath>> &forwardPath,
    std::shared_ptr<PointOnShortestPath> nextPoint,
    bool isBackwardPathOnTheRight
) {
    std::shared_ptr<PointOnShortestPath> currentEntry;
    unsigned backwardPathSize = backwardPath.size();

    // If the backward path consists only of the apex or of no point, just add the next point
    if (backwardPathSize <= 1) {
        backwardPath.push_back(nextPoint);
        return;
    }
    bool sideCheck;

    // Backward path size is larger than 1
    for (int i = backwardPathSize - 1; i > 0; i--) {
        if (isBackwardPathOnTheRight) {
            sideCheck = gU.isOnRightSide(backwardPath.at(i - 1)->getPoint(), backwardPath.at(i)->getPoint(), nextPoint->getPoint());
        } else {
            sideCheck = gU.isOnLeftSide(backwardPath.at(i - 1)->getPoint(), backwardPath.at(i)->getPoint(), nextPoint->getPoint());
        }
        if (sideCheck) {
            backwardPath.push_back(nextPoint);
            return;
        }
        // Remove the current point from the backward path
        backwardPath.pop_back();
    }

    int forwardPathSize = forwardPath.size();

    // If the forward path only consists of the apex, add the next point to the backward path
    if (forwardPathSize <= 1) {
        backwardPath.push_back(nextPoint);
        return;
    }

    // Remove all remaining entries from the backward path (there should only be one, the apex)
    while (backwardPath.size() > 0) {
        backwardPath.pop_back();
    }

    // Check the forwardPath
    for (int i = forwardPathSize - 1; i > 0; i--) {
        if (isBackwardPathOnTheRight) {
            sideCheck = gU.isOnRightSide(forwardPath.at(i)->getPoint(), forwardPath.at(i - 1)->getPoint(), nextPoint->getPoint());
        } else {
            sideCheck = gU.isOnLeftSide(forwardPath.at(i)->getPoint(), forwardPath.at(i - 1)->getPoint(), nextPoint->getPoint());
        }
        if (sideCheck) {
            backwardPath.push_back(forwardPath.at(i));
            backwardPath.push_back(nextPoint);
            return;
        }
        currentEntry = forwardPath.at(i - 1);
        currentEntry->setIndexOnShortestPath(shortestPath.size());
        shortestPath.push_back(currentEntry);
        forwardPath.pop_back();
    }

    // Handle the last point on the forward path
    if (forwardPath.size() == 1) {
        backwardPath.push_back(forwardPath.at(0));
        backwardPath.push_back(nextPoint);
    }
}

void SPV::ShortestPathCalculator::setFacesFromStartToEndPoint() {
    TDS::Face_handle currentFace;

    // Find the face containing the start point
    for (
         CDT::Finite_faces_iterator fit = triangulation.finite_faces_begin();
         fit != triangulation.finite_faces_end();
         fit++
         ) {
        if ( fit->info().inDomain() ) {
            currentFace = fit;
            Triangle t = triangulation.triangle(fit);

            if (t.has_on_bounded_side(startPoint) || t.has_on_boundary(startPoint)) {
                break;
            }
        }
    }
    recursivelyfindEndPoint(currentFace);
}

bool SPV::ShortestPathCalculator::recursivelyfindEndPoint(TDS::Face_handle &currentFaceHandle) {
    bool endPointFoundOnPath = false;
    int previousIndex = facesFromStartToEnd.size() - 1;
    auto currentFaceOnPath = std::make_shared<FaceOnShortestPath>(currentFaceHandle);

    currentFaceOnPath->nextFaceIndex = -1;
    facesFromStartToEnd.push_back(currentFaceOnPath);

    Triangle t = triangulation.triangle(currentFaceHandle);

    // If the end point is found, end the recursion by returning true
    if (t.has_on_bounded_side(endPoint) || t.has_on_boundary(endPoint)) {
        return true;
    }

    // Recursively call the function for all the neighbors
    for (int i = 0; i < 3; i++) {
        TDS::Face_handle neighbor = currentFaceHandle->neighbor(i);
        if (neighbor->info().inDomain()) {
            // Only continue, if the neighbor is not the last face
            if (previousIndex < 0 || neighbor != facesFromStartToEnd[previousIndex]->faceHandle) {
                endPointFoundOnPath = recursivelyfindEndPoint(neighbor);
                if (endPointFoundOnPath == true) {
                    currentFaceOnPath->nextFaceIndex = i;
                    break;
                }
            }
        }
    }

    // remove the current face handle
    if (endPointFoundOnPath == false) {
        facesFromStartToEnd.pop_back();
    }
    return endPointFoundOnPath;
}

void SPV::ShortestPathCalculator::setDistances()
{
    int i;
    unsigned lastIndex = shortestPath.size() - 1;
    double distanceToLastPoint, currentDistance;
    for (i = 0; i <= lastIndex; i++) {
        if (i == 0) {
            shortestPath.at(i)->setDistanceFromStartPoint(0);
        } else {
            distanceToLastPoint = shortestPath.at(i - 1)->getDistanceFromStartPoint();
            currentDistance = distanceToLastPoint +
                sqrt(CGAL::squared_distance(shortestPath.at(i - 1)->getPoint(), shortestPath.at(i)->getPoint()));
            shortestPath.at(i)->setDistanceFromStartPoint(currentDistance);
        }
    }
    for (i = lastIndex; i >= 0; i--) {
        if (i == lastIndex) {
            shortestPath.at(i)->setDistanceFromEndPoint(0);
        } else {
            distanceToLastPoint = shortestPath.at(i + 1)->getDistanceFromEndPoint();
            currentDistance = distanceToLastPoint +
                sqrt(CGAL::squared_distance(shortestPath.at(i + 1)->getPoint(), shortestPath.at(i)->getPoint()));
            shortestPath.at(i)->setDistanceFromEndPoint(currentDistance);
        }
    }
}

void SPV::ShortestPathCalculator::checkDirectPath()
{
    directPathBetweenFinalPoints = true;
    unsigned i;
    Segment s = Segment(startPoint, endPoint);

    for (i = 0; i < polygon.size() - 1; i ++) {
        auto intersection = gU.getIntersectionBetweenSegmentAndSegment(s, polygon.vertex(i), polygon.vertex(i + 1));
        if (intersection.type() != typeid(bool)) {
            directPathBetweenFinalPoints = false;
            return;
        }
    }
}

bool SPV::ShortestPathCalculator::directPathBetweenFinalPointsExists()
{
    return directPathBetweenFinalPoints;
}
