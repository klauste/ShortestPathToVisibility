#include "ShortestPath/shortestpathcalculator.h"

std::vector<SPV::PointOnShortestPath *> SPV::ShortestPathCalculator::calculateShortestPath() {
    setFacesFromStartToEndPoint();

    FaceOnShortestPath *currentFaceOnPath = facesFromStartToEnd.at(0);
    unsigned lastIndex = facesFromStartToEnd.size() - 1;
    CDT::Face_handle currentFaceHandle = currentFaceOnPath->faceHandle;
    CDT::Face_handle lastFace = facesFromStartToEnd.at(lastIndex)->faceHandle;

    int nextFaceIndex = currentFaceOnPath->nextFaceIndex;
    PointOnShortestPath *firstPoint = new PointOnShortestPath(startPoint);
    firstPoint->setIndexOnShortestPath(0);
    PointOnShortestPath *lastPoint = new PointOnShortestPath(endPoint);

    funnelTail.push_back(firstPoint);

    int vertexIndex = currentFaceHandle->ccw(nextFaceIndex);
    PointOnShortestPath *leftPoint = new PointOnShortestPath(currentFaceHandle->vertex(vertexIndex)->point());
    funnelLeftPath.push_back(firstPoint);
    funnelLeftPath.push_back(leftPoint);

    vertexIndex = currentFaceHandle->cw(nextFaceIndex);
    PointOnShortestPath *rightPoint = new PointOnShortestPath(currentFaceHandle->vertex(vertexIndex)->point());
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
        std::vector<PointOnShortestPath *> forwardVector;
        PointOnShortestPath *nextPoint = new PointOnShortestPath(currentFaceHandle->vertex(vertexIndex)->point());

        // If the next shortest path point is the same as the left point, set the next point to the right point
        if (nextPoint->getPoint() == leftPoint->getPoint()) {
            startOnLeftPath = false;
            vertexIndex = currentFaceHandle->cw(nextFaceIndex);
            delete nextPoint;
            nextPoint = new PointOnShortestPath(currentFaceHandle->vertex(vertexIndex)->point());
            rightPoint = nextPoint;
        } else {
            leftPoint = nextPoint;
        }

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
    std::vector<PointOnShortestPath *> forwardVector;
    for (int i = funnelRightPath.size() - 1; i >= 0; i--) {
        forwardVector.push_back(funnelRightPath.at(i));
        funnelRightPath.pop_back();
    }

    handleNextPoint(funnelLeftPath, forwardVector, lastPoint, false);

    // Add the last points to the funnelTail
    for (int i = 1; i < funnelLeftPath.size(); i++) {
        PointOnShortestPath* currentPoint = funnelLeftPath.at(i);
        currentPoint->setIndexOnShortestPath(funnelTail.size());
        funnelTail.push_back(currentPoint);
    }

    // After handling all the triangles between the start and end point,
    // the funnel tail is the shortest path
    return funnelTail;
}

void SPV::ShortestPathCalculator::handleNextPoint(
    std::vector<PointOnShortestPath *> &backwardPath,
    std::vector<PointOnShortestPath *> &forwardPath,
    PointOnShortestPath *nextPoint,
    bool isBackwardPathOnTheRight
) {
    PointOnShortestPath* currentEntry;
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
        currentEntry->setIndexOnShortestPath(funnelTail.size());
        funnelTail.push_back(currentEntry);
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
            if (t.has_on_bounded_side(startPoint)) {
                break;
            }
        }
    }
    recursivelyfindEndPoint(currentFace);
}

bool SPV::ShortestPathCalculator::recursivelyfindEndPoint(TDS::Face_handle &currentFaceHandle) {
    bool endPointFoundOnPath = false;
    int previousIndex = facesFromStartToEnd.size() - 1;
    FaceOnShortestPath *currentFaceOnPath = new FaceOnShortestPath(currentFaceHandle);

    currentFaceOnPath->nextFaceIndex = -1;
    facesFromStartToEnd.push_back(currentFaceOnPath);

    Triangle t = triangulation.triangle(currentFaceHandle);

    // If the end point is found, end the recursion by returning true
    if (t.has_on_bounded_side(endPoint)) {
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
