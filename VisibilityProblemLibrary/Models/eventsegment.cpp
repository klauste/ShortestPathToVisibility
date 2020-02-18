#include "Models/eventsegment.h"

SPV::EventSegment* SPV::EventSegment::clone()
{
    EventSegment *newSegment = new EventSegment(firstLineOfSightFromStart, secondLineOfSightFromStart, pivotPoint);
    if (successorSet) {
        newSegment->setSuccessor(successor);
    }
    if (predecessorSet) {
        newSegment->setPredecessor(predecessor);
    }
    newSegment->setStartSideLoSVisible(startSideLoSVisible);
    newSegment->setStartSideOnPolygonEdge(startSideOnPolygonEdge);
    newSegment->setEndSideLoSVisible(endSideLoSVisible);
    newSegment->setEndSideOnPolygonEdge(endSideOnPolygonEdge);
    newSegment->setIndexOfLastSPPointOnStartSide(indexOfLastSPPointOnStartSide);
    newSegment->setIndexOfLastSPPointOnEndSide(indexOfLastSPPointOnEndSide);
    if (distanceOnStartSideSet) {
        newSegment->setDistanceToLastVertex(distanceToLastVertexOnStartSide, true);
    }
    if (distanceOnEndSideSet) {
        newSegment->setDistanceToLastVertex(distanceToLastVertexOnEndSide, false);
    }
    for (unsigned i = 0; i < extraPointsOnStartSide.size(); i++) {
        newSegment->addExtraPointsOnStartSide(extraPointsOnStartSide.at(i));
    }

    for (unsigned i = 0; i < extraPointsOnEndSide.size(); i++) {
        newSegment->addExtraPointsOnEndSide(extraPointsOnEndSide.at(i));
    }
    return newSegment;
}

SPV::EventSegment* SPV::EventSegment::createNewSuccessor(std::shared_ptr<LineOfSight> splitLine)
{
    EventSegment *newSegment = clone();
    newSegment->setFirstLineOfSightFromStart(splitLine);
    setSecondLineOfSightFromStart(splitLine);
    setSuccessor(newSegment);
    newSegment->setPredecessor(this);
    if (newSegment->hasSuccessor()) {
        newSegment->getSuccessor()->setPredecessor(newSegment);
    }

    return newSegment;
}

SPV::EventSegment* SPV::EventSegment::createNewPredecessor(std::shared_ptr<LineOfSight> splitLine)
{
    EventSegment* newSegment = clone();
    newSegment->setDistanceToLastVertex(distanceToLastVertexOnStartSide, true);
    newSegment->setSecondLineOfSightFromStart(splitLine);
    setFirstLineOfSightFromStart(splitLine);
    setPredecessor(newSegment);
    newSegment->setSuccessor(this);
    if (newSegment->hasPredecessor()) {
        newSegment->getPredecessor()->setSuccessor(newSegment);
    }

    return newSegment;
}

SPV::EventSegment* SPV::EventSegment::getPredecessor()
{
    return predecessor;
}

void SPV::EventSegment::setPredecessor(EventSegment *p)
{
    predecessorSet = true;
    predecessor = p;
}

SPV::EventSegment* SPV::EventSegment::getSuccessor()
{
    return successor;
}

void SPV::EventSegment::setSuccessor(EventSegment* s)
{
    successorSet = true;
    successor = s;
}

void SPV::EventSegment::addExtraPointsOnStartSide(Point p)
{
    extraPointsOnStartSide.push_back(p);
}

void SPV::EventSegment::removeExtraPointOnStartSide()
{
    if (extraPointsOnStartSide.size() > 0) {
        extraPointsOnStartSide.pop_back();
    }
}

void SPV::EventSegment::addExtraPointsOnEndSide(Point p)
{
    extraPointsOnEndSide.push_back(p);
}

void SPV::EventSegment::removeExtraPointOnEndSide()
{
    if (extraPointsOnEndSide.size() > 0) {
        extraPointsOnEndSide.pop_back();
    }
}

std::vector<Point> SPV::EventSegment::getExtraPointsOnStartSide()
{
    return extraPointsOnStartSide;
}

std::vector<Point> SPV::EventSegment::getExtraPointsOnEndSide()
{
    return extraPointsOnEndSide;
}

void SPV::EventSegment::setIndexOfLastSPPointOnStartSide(unsigned i)
{
    indexOfLastSPPointOnStartSide = i;
}

void SPV::EventSegment::setIndexOfLastSPPointOnEndSide(unsigned i)
{
    indexOfLastSPPointOnEndSide = i;
}

unsigned SPV::EventSegment::getIndexOfLastSPPointOnStartSide()
{
    return indexOfLastSPPointOnStartSide;
}

unsigned SPV::EventSegment::getIndexOfLastSPPointOnEndSide()
{
    return indexOfLastSPPointOnEndSide;
}

void SPV::EventSegment::setStartSideLoSVisible(bool s)
{
    startSideLoSVisible = s;
}

bool SPV::EventSegment::getStartSideLoSVisible()
{
    return startSideLoSVisible;
}

bool SPV::EventSegment::isLoSVisible(bool onStartSide)
{
    if (onStartSide) {
        return startSideLoSVisible;
    }
    return endSideLoSVisible;
}

void SPV::EventSegment::setEndSideLoSVisible(bool e)
{
    endSideLoSVisible = e;
}

bool SPV::EventSegment::getEndSideLoSVisible()
{
    return endSideLoSVisible;
}

void SPV::EventSegment::setStartSideOnPolygonEdge(bool s)
{
    startSideOnPolygonEdge = s;
}

bool SPV::EventSegment::getStartSideOnPolygonEdge()
{
    return startSideOnPolygonEdge;
}

void SPV::EventSegment::setEndSideOnPolygonEdge(bool e)
{
    endSideOnPolygonEdge = e;
}

bool SPV::EventSegment::getEndSideOnPolygonEdge()
{
    return endSideOnPolygonEdge;
}

bool SPV::EventSegment::isPathOnPolygonEdgeAtBeginning(bool onStartSide)
{
    if (onStartSide) {
        return startSideOnPolygonEdge;
    }
    return endSideOnPolygonEdge;
}

std::shared_ptr<SPV::LineOfSight> SPV::EventSegment::getFirstLineOfSightFromStart()
{
    return firstLineOfSightFromStart;
}

void SPV::EventSegment::setFirstLineOfSightFromStart(std::shared_ptr<LineOfSight> fL)
{
    firstLineOfSightFromStart = fL;
}

std::shared_ptr<SPV::LineOfSight> SPV::EventSegment::getSecondLineOfSightFromStart()
{
    return secondLineOfSightFromStart;
}

void SPV::EventSegment::setSecondLineOfSightFromStart(std::shared_ptr<LineOfSight> sL)
{
    secondLineOfSightFromStart = sL;
}

std::shared_ptr<SPV::PointOnShortestPath> SPV::EventSegment::getPivotPoint()
{
     return pivotPoint;
}

bool SPV::EventSegment::hasSuccessor()
{
    return successorSet;
}

bool SPV::EventSegment::hasPredecessor()
{
    return predecessorSet;
}

Point SPV::EventSegment::getSegmentStartPoint(bool onStartSide)
{
    if (onStartSide) {
        return firstLineOfSightFromStart->getPointOnStartSide();
    }
    return secondLineOfSightFromStart->getPointOnEndSide();
}

Point SPV::EventSegment::getSegmentEndPoint(bool onStartSide)
{
    if (onStartSide) {
        return secondLineOfSightFromStart->getPointOnStartSide();
    }
    return firstLineOfSightFromStart->getPointOnEndSide();
}

bool SPV::EventSegment::bendEventsOnStartSideAreHandled()
{
    return bendEventsOnStartSideHandled;
}

void SPV::EventSegment::setEventsOnStartSideHandled()
{
    bendEventsOnStartSideHandled = true;
}

bool SPV::EventSegment::bendEventsOnEndSideAreHandled()
{
    return bendEventsOnEndSideHandled;
}

void SPV::EventSegment::setEventsOnEndSideHandled()
{
    bendEventsOnEndSideHandled = true;
}

double SPV::EventSegment::getDistanceToLastVertex(bool onStartSide)
{
    if (onStartSide) {
        return distanceToLastVertexOnStartSide;
    }
    return distanceToLastVertexOnEndSide;
}

void SPV::EventSegment::setDistanceToLastVertex(double d, bool onStartSide)
{
    if (onStartSide) {
        distanceToLastVertexOnStartSide = d;
        distanceOnStartSideSet = true;
    } else {
        distanceToLastVertexOnEndSide = d;
        distanceOnEndSideSet = true;
    }
}
