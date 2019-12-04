#include "spveventmap.h"

void SPV::PolygonTriangle::setLeftTriangle(PolygonTriangle *pt) {
    leftTriangle = pt;
}

void SPV::PolygonTriangle::setRightTriangle(PolygonTriangle *pt) {
    rightTriangle = pt;
}


SPV::PolygonTriangle* SPV::PolygonTriangle::getLeftTriangle() {
    return leftTriangle;
}

SPV::PolygonTriangle* SPV::PolygonTriangle::getRightTriangle() {
    return rightTriangle;
}

void SPV::PolygonTriangle::addRightToLeftVertexIndex(int i) {
    rightToLeftVertexIndex.push_back(i);
}

std::vector<int> SPV::PolygonTriangle::getRightToLeftIndices() {
    return rightToLeftVertexIndex;
}

CDT::Face_handle SPV::PolygonTriangle::getFace() {
    return currentFace;
}

void SPV::PolygonTriangle::addIndexAtStart(int index) {
    rightToLeftVertexIndex.insert(rightToLeftVertexIndex.begin(), index);
}

bool SPV::PolygonTriangle::getIsStartTriangle() {
    return isStartTriangle;
}

Point SPV::PolygonTriangle::getLeftPoint(Point p) {
    int i;
    int numberOfPoints = rightToLeftVertexIndex.size();
    for (i = 0; i < numberOfPoints; i++) {
        if (currentFace->vertex(rightToLeftVertexIndex.at(i))->point() == p) {
            break;
        }
    }

    if (i == numberOfPoints - 1) {
        return getLeftTriangle()->getLeftPoint(p);
    }
    return currentFace->vertex(rightToLeftVertexIndex.at(i + 1))->point();
}

Point SPV::PolygonTriangle::getRightPoint(Point p) {
    int i;
    int numberOfPoints = rightToLeftVertexIndex.size();
    for (i = 0; i < numberOfPoints; i++) {
        if (currentFace->vertex(rightToLeftVertexIndex.at(i))->point() == p) {
            break;
        }
    }

    if (i == 0) {
        return getRightTriangle()->getRightPoint(p);
    }
    return currentFace->vertex(rightToLeftVertexIndex.at(i - 1))->point();}

SPV::EventMap::EventMap(Polygon &p, CDT &cdt)
{
    setPolygonTriangles(p, cdt);
}

void SPV::EventMap::setPolygonTriangles(Polygon &p, CDT &cdt) {
    int polygonSize = p.size();
    int currentIndex = 0;
    Point currentPoint;
    Point firstPoint = p.vertex(0);
    Point secondPoint = p.vertex(1);
    bool finished = false;
    CDT::Face_handle currentFace;
    CDT::Face_handle nextFace;
    PolygonTriangle *nextTriangle;

    // Find the face that contains both the first and second point
    for (
         CDT::Finite_faces_iterator fit=cdt.finite_faces_begin();
         fit!=cdt.finite_faces_end();
         ++fit
    ) {
        int countPoints = 0;
        if (fit->info().inDomain()) {
            for (int i = 0; i < 3; i++) {
                currentPoint = fit->vertex(i)->point();
                if (currentPoint == firstPoint || currentPoint == secondPoint) {
                    countPoints++;
                }
            }
            if (countPoints == 2) {
                currentFace = fit;
                break;
            }
        }
    }

    PolygonTriangle *currentTriangle = new PolygonTriangle(currentFace, true);
    startPointTriangle = currentTriangle;
    bool handleMore = true;
    int index = 0;

    // Go through all the points and link the triangles together
    while (handleMore) {
        int lastPointIndex = addPointsToTriangle(p, index, currentTriangle);
        index++;

        // If three points were added to the current triangle, one point can be skipped
        if (currentTriangle->getRightToLeftIndices().size() == 3) {
            index++;
        }
        if (index >= polygonSize - 1) {
            handleMore = false;
            index = polygonSize - 1;
            currentFace = findNextFace(currentFace, lastPointIndex, p.vertex(index));
            if (currentFace != startPointTriangle->getFace()) {
                // There is one more triangle between the current triangle and the end triangle
                nextTriangle = new PolygonTriangle(currentFace, false);
                currentTriangle->setLeftTriangle(nextTriangle);
                nextTriangle->setRightTriangle(currentTriangle);
                currentTriangle = nextTriangle;
                addPointsToTriangle(p, index, currentTriangle);
            }
            endPointTriangle = currentTriangle;
            nextTriangle = startPointTriangle;
        } else {
            currentFace = findNextFace(currentFace, lastPointIndex, p.vertex((index + 1) % polygonSize));
            nextTriangle = new PolygonTriangle(currentFace, false);
        }
        currentTriangle->setLeftTriangle(nextTriangle);
        nextTriangle->setRightTriangle(currentTriangle);
        currentTriangle = nextTriangle;
    }
    handleLastPoint(p.vertex(polygonSize - 1));
}

int SPV::EventMap::addPointsToTriangle(Polygon &p, unsigned index, PolygonTriangle *currentTriangle) {
    unsigned polygonSize = p.size();
    int index1;
    int index2;
    int index3 = -1;
    int lastPointIndex;
    CDT::Face_handle currentFace = currentTriangle->getFace();
    Point p1 = p.vertex(index);
    Point p2 = p.vertex((index + 1) % polygonSize);
    Point p3 = p.vertex((index + 2) % polygonSize);
    for (int j = 0; j < 3; j++) {
        if (p1 == currentFace->vertex(j)->point()) {
            index1 = j;
        }
        if (p2 == currentFace->vertex(j)->point()) {
            index2 = j;
        }
        if (p3 == currentFace->vertex(j)->point()) {
            index3 = j;
        }
    }
    currentTriangle->addRightToLeftVertexIndex(index1);
    currentTriangle->addRightToLeftVertexIndex(index2);
    lastPointIndex = index2;
    if (index3 > -1) {
        lastPointIndex = index3;
        currentTriangle->addRightToLeftVertexIndex(index3);
    }
    return lastPointIndex;
}

void SPV::EventMap::handleLastPoint(Point p) {
    CDT::Face_handle fh = startPointTriangle->getFace();
    std::vector<int> indexVector = startPointTriangle->getRightToLeftIndices();
    Point firstPoint = fh->vertex(indexVector.at(0))->point();
    if (indexVector.size() == 3 || firstPoint == p) {
        return;
    }
    int vertexIndex = -1;

    for (int i = 0; i < 3; i++) {
        if (fh->vertex(i)->point() == p) {
            vertexIndex = i;
        }
    }
    if (vertexIndex > -1) {
        startPointTriangle->addIndexAtStart(vertexIndex);
    }
}

CDT::Face_handle SPV::EventMap::findNextFace(CDT::Face_handle fh, int lastPointIndex, Point nextPoint) {
    bool foundFace = false;
    CDT::Face_handle nextFace;
    Face_circulator faceCirculator = fh->vertex(lastPointIndex)->incident_faces(),
            done(faceCirculator);
    if (faceCirculator != 0) {
        do {
            if (faceCirculator->info().inDomain()) {
                for (int i = 0; i < 3; i++) {
                    Point p = faceCirculator->vertex(i)->point();
                    if (p == nextPoint) {
                        nextFace = faceCirculator;
                        foundFace = true;
                    }
                }
            }
        } while (++faceCirculator != done && !foundFace);
    }
    return nextFace;
}
