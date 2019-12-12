#include <iostream>
#include <QApplication>
#include <QRectF>
#include <QGraphicsView>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    //SPV::SPVGraphicsScene scene;
    QRectF rect(0, 0, 600, 600);

    //scene.setSceneRect(rect);
    //QGraphicsView * view = new QGraphicsView(&scene);
    //view->setMouseTracking(true);

    //view->show();

    return app.exec();
}
