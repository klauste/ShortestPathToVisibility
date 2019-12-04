#ifndef SPVGraphicsScene_H
#define SPVGraphicsScene_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "SPVGraphicsSceneCGALModel.h"
#include "spvshortestpath.h"
#include <vector>
#include <CGAL/Point_2.h>
typedef K::Point_2 Point;

namespace SPV {
    class SPVGraphicsScene: public QGraphicsScene {
    public:
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

    private:
        SPVGraphicsSceneCGALModel cgalModel;
        QPointF lastPointAdded;
        QGraphicsLineItem* lineToMousePosition = nullptr;
        bool hasAddedLast = false;
        bool displayDashLine = false;
        bool polygonIsClosed = false;
        int numberOfPointsAdded = 0;

        void closePolyline();
    };
}

#endif
