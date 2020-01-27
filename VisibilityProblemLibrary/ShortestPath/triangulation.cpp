#include "ShortestPath/triangulation.h"
const CDT& SPV::Triangulation::getTriangulation() {
    cdt.insert_constraint(polygon.vertices_begin(), polygon.vertices_end(), true);

    //Mark faces that are inside the domain bounded by the polygon
    markDomains(cdt);
    return cdt;
}

void SPV::Triangulation::markDomains(
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

void SPV::Triangulation::markDomains(CDT& cdt) {
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
