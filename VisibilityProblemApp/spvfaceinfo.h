#ifndef SPVFACEINFO_H
#define SPVFACEINFO_H

#include <vector>
#include "spveventonshortestpath.h"
#include "spveventintersection.h"
#include <boost/bind.hpp>

typedef K::Segment_2 Segment;

namespace SPV {
    class FaceInfo {
    public:
        FaceInfo();
        bool inDomain();
        int getNestingLevel();
        void setNestingLevel(int nl);
        void addShortestPathEvent(SPV::EventOnShortestPath* spr);
        SPV::EventOnShortestPath* getShortestPathEvent(Point startingPoint, Point endPoint);
        boost::variant<bool, SPV::EventOnShortestPath*> getShortestPathEventByIntersection(Point iS) {
            if (!hasShortestPathEvents) {
                return false;
            }
            for (unsigned i = 0; i < shortestPathEvents.size(); i++) {
                if (shortestPathEvents.at(i)->getFirstPointIntersection() == iS || shortestPathEvents.at(i)->getSecondPointIntersection() == iS) {
                    return shortestPathEvents.at(i);
                }
            }
            return false;
        }
        std::vector<SPV::EventOnShortestPath*> getShortestPathEvents();
        bool getHasShortestPathEvent(Point startingPoint, Point endPoint);
        bool getHasShortestPathEvents();

        void addEventIntersection (EventIntersection* ei) {
            if (hasEventIntersections1 == false) {
                hasEventIntersections1 = true;
                eventIntersections1.push_back(ei);
                return;
            }
            EventIntersection *eventInter = eventIntersections1.at(0);
            if (intersectionsAreOnSameSegment(eventInter, ei)) {
                addIntersectionInOrder(1, ei);
                return;
            }
            if (hasEventIntersections2 == false) {
                hasEventIntersections2 = true;
                eventIntersections2.push_back(ei);
                return;
            }
            eventInter = eventIntersections2.at(0);
            if (intersectionsAreOnSameSegment(eventInter, ei)) {
                addIntersectionInOrder(2, ei);
                return;
            }
            std::cout << "Something went wrong!" << std::endl;
        }
        bool getHasEventIntersections1() {
            return hasEventIntersections1;
        }
        bool getHasEventIntersections2() {
            return hasEventIntersections2;
        }
        std::vector<SPV::EventIntersection*> getEventIntersections1() {
            return eventIntersections1;
        }
        std::vector<SPV::EventIntersection*> getEventIntersections2() {
            return eventIntersections1;
        }

        boost::variant<bool, std::vector<SPV::EventIntersection*>> getIntersectionsForSegment(Point segStart, Point segEnd) {
            if (hasEventIntersections1 && segmentIsTheSame(eventIntersections1.at(0), segStart, segEnd)) {
                return eventIntersections1;
            }
            if (hasEventIntersections2 && segmentIsTheSame(eventIntersections2.at(0), segStart, segEnd)) {
                return eventIntersections2;
            }
            return false;
        }

        boost::variant<bool, SPV::EventIntersection*> getEventIntersectionForIntersection(Point iS) {
            unsigned i;
            Point currentP;
            if (hasEventIntersections1) {
                for (i = 0; i < eventIntersections1.size(); i++) {
                    currentP = eventIntersections1.at(i)->getIntersection();
                    if (eventIntersections1.at(i)->getIntersection() == iS) {
                        return eventIntersections1.at(i);
                    }
                }
            }
            if (hasEventIntersections2) {
                for (i = 0; i < eventIntersections2.size(); i++) {
                    currentP = eventIntersections2.at(i)->getIntersection();

                    if (eventIntersections2.at(i)->getIntersection() == iS) {
                        return eventIntersections2.at(i);
                    }
                }
            }
            return false;
        }

        bool getHasSptFromStartIndices() {
            return hasSptFromStartIndices;
        }
        bool getHasSptFromEndIndices() {
            return hasSptFromEndIndices;
        }
        bool getHasShortestPathIndices() {
            return hasShortestPathIndices;
        }
        std::vector<int> getSptFromStartIndices() {
            return sptFromStartIndices;
        }
        std::vector<int> getSptFromEndIndices() {
            return sptFromEndIndices;
        }
        std::vector<unsigned> getShortestPathIndices() {
            return shortestPathIndices;
        }
        void addSptFromStartIndex(int i) {
            hasSptFromStartIndices = true;
            sptFromStartIndices.push_back(i);
        }
        void addSptFromEndIndex(int i) {
            hasSptFromEndIndices = true;
            sptFromEndIndices.push_back(i);
        }
        void addShortestPathIndex(unsigned i) {
            hasShortestPathIndices = true;
            shortestPathIndices.push_back(i);
        }
    private:
        int nestingLevel;
        bool hasShortestPathEvents = false;
        int firstFromRightToLeft;
        std::vector<SPV::EventOnShortestPath*> shortestPathEvents;
        std::vector<SPV::EventIntersection*> eventIntersections1;
        std::vector<SPV::EventIntersection*> eventIntersections2;

        // Contains the entries in the shortest path tree from start associated with this face. Using indices instead of
        // object pointers because entries in the shortest path contain a pointer to the face they are associated with
        // and I wasn't able to add face pointers to a face pointer info. This is not a great solution, but the only
        // one I could come up with.
        std::vector<int> sptFromStartIndices;

        // Contains the entries in the shortest path tree from end associated with this face. Using indices instead of
        // object pointers because entries in the shortest path contain a pointer to the face they are associated with
        // and I wasn't able to add face pointers to a face pointer info. This is not a great solution, but the only
        // one I could come up with.
        std::vector<int> sptFromEndIndices;

        // Contains the entries in the shortest path associated with this face. Using indices instead of
        // object pointers because entries in the shortest path contain a pointer to the face they are associated with
        // and I wasn't able to add face pointers to a face pointer info. This is not a great solution, but the only
        // one I could come up with.
        std::vector<unsigned> shortestPathIndices;

        bool hasSptFromStartIndices = false;
        bool hasSptFromEndIndices = false;
        bool hasShortestPathIndices = false;
        bool hasEventIntersections1 = false;
        bool hasEventIntersections2 = false;
        bool intersectionsAreOnSameSegment(EventIntersection* ei1, EventIntersection* ei2) {
            if (ei1->getSegmentStart() == ei2->getSegmentStart() && ei1->getSegmentEnd() == ei2->getSegmentEnd()) {
                return true;
            }
            if (ei1->getSegmentStart() == ei2->getSegmentEnd() && ei1->getSegmentEnd() == ei2->getSegmentStart()) {
                ei2->swapSegmentPoints();
                return true;
            }
            return false;
        }
        bool segmentIsTheSame(EventIntersection *ei, Point p1, Point p2) {
            return (
                (ei->getSegmentStart() == p1 && ei->getSegmentEnd() == p2) ||
                (ei->getSegmentStart() == p2 && ei->getSegmentEnd() == p1)
            );
        }
        void addIntersectionInOrder(int vectorNumber, EventIntersection* ei) {
            std::vector<SPV::EventIntersection*>::iterator it;
            std::vector<SPV::EventIntersection*> interVector = eventIntersections1;
            if (vectorNumber == 2) {
                interVector = eventIntersections2;
            }
            Point segmentStart = ei->getSegmentStart();
            Point newIntersection = ei->getIntersection();
            for (it=interVector.begin(); it<interVector.end(); it++) {
                Point currentIntersection = (*it)->getIntersection();
                if (Segment(segmentStart, newIntersection).squared_length() < Segment(segmentStart, currentIntersection).squared_length()) {
                    break;
                }
            }
            interVector.insert(it, ei);
            if (vectorNumber == 1) {
                eventIntersections1 = interVector;
            } else {
                eventIntersections2 = interVector;
            }
        }
    };
}

#endif // SPVFACEINFO_H
