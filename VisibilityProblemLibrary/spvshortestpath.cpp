#include "spvshortestpath.h"

void SPV::ShortestPath::initialize(const Polygon &p)
{
    polygon = p;
    cdt.insert_constraint(polygon.vertices_begin(), polygon.vertices_end(), true);

    //Mark faces that are inside the domain bounded by the polygon
    markDomains(cdt);
}

const CDT& SPV::ShortestPath::getTriangulation() {
    return cdt;
}

void SPV::ShortestPath::markDomains(
        CDT& ct,
        CDT::Face_handle start,
        int index,
        std::list<CDT::Edge>& border
)
{
    if(start->info().getNestingLevel() != -1){
        return;
    }
    std::list<CDT::Face_handle> queue;
    queue.push_back(start);
    while(! queue.empty()){
        CDT::Face_handle fh = queue.front();
        queue.pop_front();
        if(fh->info().getNestingLevel() == -1){
            fh->info().setNestingLevel(index);
            for(int i = 0; i < 3; i++){
                CDT::Edge e(fh,i);
                CDT::Face_handle n = fh->neighbor(i);
                if(n->info().getNestingLevel() == -1){
                    if(ct.is_constrained(e)) border.push_back(e);
                    else queue.push_back(n);
                }
            }
        }
    }
}

void SPV::ShortestPath::markDomains(CDT& cdt) {
    for(CDT::All_faces_iterator it = cdt.all_faces_begin(); it != cdt.all_faces_end(); ++it){
        it->info().setNestingLevel(-1);
    }
    std::list<CDT::Edge> border;
    markDomains(cdt, cdt.infinite_face(), 0, border);
    while(! border.empty()){
        CDT::Edge e = border.front();
        border.pop_front();
        CDT::Face_handle n = e.first->neighbor(e.second);
        if(n->info().getNestingLevel() == -1){
            markDomains(cdt, n, e.first->info().getNestingLevel()+1, border);
        }
    }
}

std::vector<SPV::PointOnShortestPath*> SPV::ShortestPath::calculateShortestPath() {
    ShortestPathCalculator *spc = new ShortestPathCalculator(
                polygon,
                cdt,
                sPoint,
                ePoint
    );

    std::vector<PointOnShortestPath* > sP = spc->calculateShortestPath();
    ShortestPathTreeCalculator *sptcStart = new ShortestPathTreeCalculator(
        sPoint,
        sP,
        false
    );
    ShortestPathTreeCalculator *sptcEnd = new ShortestPathTreeCalculator(
        ePoint,
        sP,
        true
    );
    sptcStart->setSweptSegmentsInShortestPath(spc->getStartFace());
    sptcEnd->setSweptSegmentsInShortestPath(spc->getEndFace());

    delete sptcStart;
    delete sptcEnd;
    delete spc;
    return sP;


    /*if (setFacesFromStartToEndPoint() == true) {
        FaceOnPath *currentFaceOnPath = facesFromStartToEnd.at(0);
        int lastIndex = facesFromStartToEnd.size() - 1;
        CDT::Face_handle currentFace = currentFaceOnPath->currentFace;
        CDT::Face_handle lastFace = facesFromStartToEnd.at(lastIndex)->currentFace;

        int nextFaceIndex = currentFaceOnPath->nextFaceIndex;
        funnelTail.push_back(startPoint);

        int vertexIndex = currentFace->ccw(nextFaceIndex);
        ShortestPathEntry *leftEntry = new ShortestPathEntry(currentFace, vertexIndex);
        funnelLeftPath.push_back(startPoint);
        funnelLeftPath.push_back(leftEntry);

        vertexIndex = currentFace->cw(nextFaceIndex);
        ShortestPathEntry *rightEntry = new ShortestPathEntry(currentFace, vertexIndex);
        funnelRightPath.push_back(startPoint);
        funnelRightPath.push_back(rightEntry);

        // Loop over all the diagonals
        for (int i = 1; i < facesFromStartToEnd.size() - 1; i++) {
            bool startOnLeftPath = true;
            currentFaceOnPath = facesFromStartToEnd.at(i);
            currentFace = currentFaceOnPath->currentFace;
            nextFaceIndex = currentFaceOnPath->nextFaceIndex;
            vertexIndex = currentFace->ccw(nextFaceIndex);
            std::vector<ShortestPathEntry *> forwardVector;
            ShortestPathEntry *nextEntry = new ShortestPathEntry(currentFace, vertexIndex);

            // Set next point to the point which is not on the current diagonal
            if (nextEntry->getPoint() == leftEntry->getPoint()) {
                startOnLeftPath = false;
                vertexIndex = currentFace->cw(nextFaceIndex);
                delete nextEntry;
                nextEntry = new ShortestPathEntry(currentFace, vertexIndex);
                rightEntry = nextEntry;

            } else {
                leftEntry = nextEntry;
            }

            // Check if nextPoint is part of the right or left sleeve
            if (startOnLeftPath) {
                // Add the elements from end to front to forwardVector
                for (int j = funnelRightPath.size() - 1; j >= 0; j--) {
                    forwardVector.push_back(funnelRightPath.at(j));
                    funnelRightPath.pop_back();
                }
                handleNextPoint(funnelLeftPath, forwardVector, nextEntry, false);
                for (int j = forwardVector.size() - 1; j >= 0; j--) {
                    funnelRightPath.push_back(forwardVector.at(j));
                }
            } else {
                for (int j = funnelLeftPath.size() - 1; j >= 0; j--) {
                    forwardVector.push_back(funnelLeftPath.at(j));
                    funnelLeftPath.pop_back();
                }
                handleNextPoint(funnelRightPath, forwardVector, nextEntry, true);
                for (int j = forwardVector.size() - 1; j >= 0; j--) {
                    funnelLeftPath.push_back(forwardVector.at(j));
                }
            }
        }
    }

    // Handle the last point
    std::vector<ShortestPathEntry *> forwardVector;
    for (int i = funnelRightPath.size() - 1; i >= 0; i--) {
        forwardVector.push_back(funnelRightPath.at(i));
        funnelRightPath.pop_back();
    }

    handleNextPoint(funnelLeftPath, forwardVector, endPoint, false);

    // Add the last points to the funnelTail
    for (int i = 1; i < funnelLeftPath.size(); i++) {
        ShortestPathEntry* currentEntry = funnelLeftPath.at(i);
        funnelTail.push_back(currentEntry);
        if (currentEntry->isMidPoint()) {
            currentEntry->getFaceHandle()->info().addShortestPathIndex(funnelTail.size() - 1);
        }
    }

    calculateShortestPathTree(false);
    calculateShortestPathTree(true);

    boundaryEvents = BoundaryEvents(funnelTail, eventMap, shortestPathTree, shortestPathTreeFromEnd);
    boundaryEventIntersections = boundaryEvents.calculateBoundaryEvents();
    bendEvents = BendEvents(funnelTail, eventMap);
    bendEventIntersections = bendEvents.calculateBendEvents();
    minimumCalculator = MinimumCalculator(funnelTail, eventMap);
    minimumCalculator.calculateMinima();
    std::vector<Minimum*> allMinima = minimumCalculator.getAllMinima();*/
    //return false;
}

void SPV::ShortestPath::setPoint(int index, float x, float y) {
    if (index == 0) {
        sPoint = Point(x, y);
    }
    if (index == 1) {
        ePoint = Point(x, y);
    }
}
