#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <iostream>
#include <QApplication>
#include <QRectF>
#include <QGraphicsView>
#include <CGAL/Qt/PolygonGraphicsItem.h>

#include "SPVGraphicsScene.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    SPV::SPVGraphicsScene scene;
    QRectF rect(0, 0, 600, 600);

    scene.setSceneRect(rect);
    QGraphicsView * view = new QGraphicsView(&scene);
    view->setMouseTracking(true);

    view->show();

    return app.exec();
}
