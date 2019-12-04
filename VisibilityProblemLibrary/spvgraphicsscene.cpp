#include "spvgraphicsscene.h"
#include <QGraphicsSceneMouseEvent>
#include <iostream>

namespace SPV {
    /**
     * This function handles mouse press events in the scene.
     *
     * @brief SPVGraphicsScene::mousePressEvent
     * @param mouseEvent
     */
    void SPVGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
        QPointF currentPos = mouseEvent->scenePos();
        QRectF currentRect = QRectF(currentPos.x() - 5, currentPos.y() - 5, 10, 10);

        if (polygonIsClosed) {
            if (numberOfPointsAdded < 2 && cgalModel.isPointInPolygon(currentPos)) {
                cgalModel.addPairPoint(currentPos, numberOfPointsAdded);
                numberOfPointsAdded++;
                addEllipse(currentRect, QPen(Qt::red, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(Qt::red, Qt::SolidPattern));
                if (numberOfPointsAdded == 2) {
                    cgalModel.calculateShortestPath();
                    //std::vector<SPV::PointOnShortestPath *> spt = cgalModel.getShorttestPathTree();
                    std::vector<SPV::ShortestPathEntry *> p = cgalModel.getSleevePath(3);
                    for (int i = 0; i < p.size(); i++) {

                        if (p.at(i)->isMidPoint() && p.at(i)->getFaceHandle()->info().getHasShortestPathEvents()) {
                        std::vector<EventOnShortestPath*> rs = p.at(i)->getFaceHandle()->info().getShortestPathEvents();
                        EventOnShortestPath* r;
                        Point po = p.at(i)->getPoint();
                        for (int i = 0; i < rs.size(); i++) {
                            r = rs.at(i);
                            Point iS = r->getFirstPointIntersection();
                            Point iE = r->getSecondPointIntersection();
                            std::cout << "intersection first: " << iS << std::endl;
                            std::cout << "intersection end: " << iE << std::endl;


                            addLine(
                                                r->getFirstPointIntersection().x(),
                                                r->getFirstPointIntersection().y(),
                                        r->getSecondPointIntersection().x(),
                                        r->getSecondPointIntersection().y(),

                                                QPen(Qt::black, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                        }
                        }
                        if (p.at(i)->isEndPoint() && p.at(i - 1)->getFaceHandle()->info().getHasShortestPathEvent(p.at(i-1)->getPoint(), p.at(i)->getPoint())) {
                            EventOnShortestPath* r = p.at(i - 1)->getFaceHandle()->info().getShortestPathEvent(p.at(i-1)->getPoint(), p.at(i)->getPoint());
                                addLine(
                                                    r->getFirstPointIntersection().x(),
                                                    r->getFirstPointIntersection().y(),
                                            r->getSecondPointIntersection().x(),
                                            r->getSecondPointIntersection().y(),

                                                    QPen(Qt::black, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                            }

                    }
                    std::vector<Minimum*> allMinima = cgalModel.getMinima();
                    for (unsigned i = 0; i < allMinima.size(); i ++) {
                        Point start = allMinima.at(i)->getStartIntersectionOnEdge();
                        Point endPoint = allMinima.at(i)->getEndIntersectionOnEdge();
                        addLine(
                                            start.x(),
                                start.y(),
                        endPoint.x(),
                                    endPoint.y(),
                                            QPen(Qt::red, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                    }
                    /*
                    for (int i = 0; i < p.size() - 1; i ++) {
                        addLine(
                                            p.at(i)->getPoint().x(),
                                            p.at(i)->getPoint().y(),
                                            p.at(i+1)->getPoint().x(),
                                            p.at(i+1)->getPoint().y(),
                                            QPen(Qt::green, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                    }
                    //p = cgalModel.getSleevePath(3);
                    for (int i = 0; i < spt.size(); i ++) {
                        if (!spt.at(i)->isFinalPoint()) {
                            SPV::PointOnShortestPath * pred = spt.at(i) -> getPreviousPoint();
                            addLine(
                                                spt.at(i)->getCurrentPoint().x(),
                                                spt.at(i)->getCurrentPoint().y(),
                                                pred->getCurrentPoint().x(),
                                                pred->getCurrentPoint().y(),
                                                QPen(Qt::black, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                        }
                    }*/
                }
            }

            return;
        }
        if (hasAddedLast == true) {
            // If the current point is close enough to the first one, close the polyline to a polygon
            if (cgalModel.shouldClosePolyline(currentPos)) {
                displayDashLine = false;
                closePolyline();
                polygonIsClosed = true;
                return;
            }
            // If segments intersect, no new line is allowed to be added
            if (cgalModel.doSegmentsIntersect(lastPointAdded, currentPos)) {
                return;
            }
            addLine(
                lastPointAdded.x(),
                lastPointAdded.y(),
                currentPos.x(),
                currentPos.y(),
                QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
            );
            cgalModel.addSegment(lastPointAdded, currentPos);
        } else {
            cgalModel.setPolylineStartPoint(currentPos);
        }

        addEllipse(currentRect, QPen(Qt::green, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(Qt::green, Qt::SolidPattern));
        lastPointAdded = currentPos;
        hasAddedLast = true;
        displayDashLine = true;
    }

    /**
     * Handles mouse movement events
     *
     * @brief SPVGraphicsScene::mouseMoveEvent
     * @param mouseEvent
     */
    void SPVGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
        if (displayDashLine == false) {
            return;
        }

        if (hasAddedLast == true) {
            QPointF currentPos = mouseEvent->scenePos();
            if (lineToMousePosition == nullptr) {
                lineToMousePosition = addLine(
                    lastPointAdded.x(),
                    lastPointAdded.y(),
                    currentPos.x(),
                    currentPos.y(),
                    QPen(Qt::blue, 0, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin)
                );
            } else {
                lineToMousePosition->setLine(
                    lastPointAdded.x(),
                    lastPointAdded.y(),
                    currentPos.x(),
                    currentPos.y()
                );
            }
        }
    }

    void SPVGraphicsScene::closePolyline() {
        QList<QGraphicsItem *> currentItems = items();
        while (!currentItems.isEmpty()) {
            QGraphicsItem *first = currentItems.takeFirst();
            removeItem(first);
            delete first;
        }

        cgalModel.closePolyline(lastPointAdded);
        QGraphicsItem *polygon = cgalModel.getQtPolygon();
        Polygon p = cgalModel.getPolygon();

        for (int i = 0; i < p.size(); i++) {
                    std::string s1 = std::to_string((int)p[i].x());
                    std::string s2 = std::to_string((int)p[i].y());
                    std::string s3 = s1 + ", " + s2;
                    QGraphicsTextItem *text = addText(s3.data());
                    text->setPos(p[i].x(), p[i].y());
                }
        addItem(polygon);
        const CDT& cdt = cgalModel.getCdt();

        for (
             CDT::Finite_faces_iterator fit = cdt.finite_faces_begin();
             fit != cdt.finite_faces_end();
             fit++
             ) {
            if ( fit->info().inDomain() ) {
                Triangle t = cdt.triangle(fit);

                addLine(
                    t.vertex(0).x(),
                    t.vertex(0).y(),
                    t.vertex(1).x(),
                    t.vertex(1).y(),
                    QPen(Qt::blue, 0, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin)
                );
                addLine(
                    t.vertex(1).x(),
                    t.vertex(1).y(),
                    t.vertex(2).x(),
                    t.vertex(2).y(),
                    QPen(Qt::blue, 0, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin)
                );
                addLine(
                    t.vertex(2).x(),
                    t.vertex(2).y(),
                    t.vertex(0).x(),
                    t.vertex(0).y(),
                    QPen(Qt::blue, 0, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin)
                );
            }
        }
    }
}
