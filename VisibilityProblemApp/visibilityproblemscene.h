#ifndef VISIBILITYPROBLEMSCENE_H
#define VISIBILITYPROBLEMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include "Utils/cgalgeometryconnector.h"
#include <QObject>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QString>
#include <boost/format.hpp>
#include <math.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon;


class VisibilityProblemScene : public QGraphicsScene
{
    Q_OBJECT

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void toggleShortestPath(bool display);
    void togglePathEvents(bool display);
    void toggleBoundaryEvents(bool display);
    void toggleBendEvents(bool display);
    void toggleMinMaxMinima(bool display);
    void toggleMinSumMinima(bool display);

    void toggleShortestPathLabels(bool display);
    void togglePathEventLabels(bool display);
    void toggleBoundaryEventLabels(bool display);
    void toggleBendEventLabels(bool display);
    void togglePolygonLabels(bool display);
    void toggleMinMaxLabels(bool display);
    void toggleMinSumLabels(bool display);
    void setDecimalPlaces(int d);
    void setTestData(int numberOfTest);
    void setTestDataScaleFactor(double f);

    void reset();

signals:
    void polygonReady();

private:
    void closePolyline();
    bool polygonIsClosed = false;
    int numberOfPointsAdded = 0;
    bool displayDashLine = false;
    void handleNewPointForPolygon(QPointF p);
    void handleStartOrEndPoint(QPointF p);
    CGALGeometryConnector gC = CGALGeometryConnector();
    QPointF lastPolylinePoint;
    QPointF firstPolylinePoint;
    QGraphicsEllipseItem *firstPointDisplay;
    QGraphicsEllipseItem *startPoint = nullptr;
    QGraphicsEllipseItem *endPoint = nullptr;
    QGraphicsLineItem* lineToMousePosition = nullptr;
    void toggleEvents(bool display, const std::vector<QLineF*> &events, std::vector<QGraphicsLineItem*> &lines, bool isShortestPath = false);
    void toggleMinima(bool display, const std::vector<CGALGeometryConnector::MinData*> &minima, std::vector<QGraphicsLineItem*> &lines);
    void toggleLabels(bool display, const std::vector<QGraphicsLineItem*> &lines, std::vector<QGraphicsProxyWidget*> &labels);
    void toggleMinLabels(bool display, const std::vector<CGALGeometryConnector::MinData*> &minima, std::vector<QGraphicsProxyWidget*> &labels);
    std::vector<QGraphicsLineItem *> pathEvents;
    std::vector<QGraphicsLineItem *> boundaryEvents;
    std::vector<QGraphicsLineItem *> bendEvents;
    std::vector<QGraphicsLineItem *> shortestPath;
    std::vector<QGraphicsLineItem *> minMaxLines;
    std::vector<QGraphicsLineItem *> minSumLines;
    std::vector<QGraphicsLineItem *> polygonLines;
    std::vector<QGraphicsProxyWidget *> pathEventLabels;
    std::vector<QGraphicsProxyWidget *> boundaryEventLabels;
    std::vector<QGraphicsProxyWidget *> bendEventLabels;
    std::vector<QGraphicsProxyWidget *> shortestPathLabels;
    std::vector<QGraphicsProxyWidget *> minMaxLabels;
    std::vector<QGraphicsProxyWidget *> minSumLabels;
    std::vector<QGraphicsProxyWidget *> polygonLabels;
    int decimalPlaces = 0;
    std::string roundToDecimalPlaces(double value);
    double testDataScaleFactor = 30;
};

#endif // VISIBILITYPROBLEMSCENE_H
