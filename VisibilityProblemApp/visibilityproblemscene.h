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
#include <QRectF>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon;

/**
 * @brief The VisibilityProblemScene class is a graphical display area where polygons and results of
 * the minimum calculations can be displayed.
 */
class VisibilityProblemScene : public QGraphicsScene
{
    Q_OBJECT

public:
    VisibilityProblemScene();

    /**
     * @brief mousePressEvent either adds a point to the polyline, or if the polygon is ready
     * adds a start/end point
     * @param mouseEvent
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

    /**
     * @brief mouseMoveEvent visualises the next line segement to be added to the polyline
     * @param mouseEvent
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

    /**
     * @brief toggleShortestPath display/hide the shortest path
     * @param display
     */
    void toggleShortestPath(bool display);

    /**
     * @brief togglePathEvents display/hide path events
     * @param display
     */
    void togglePathEvents(bool display);

    /**
     * @brief toggleBoundaryEvents display/hide boundary events
     * @param display
     */
    void toggleBoundaryEvents(bool display);

    /**
     * @brief toggleBendEvents display/hide bend events
     * @param display
     */
    void toggleBendEvents(bool display);

    /**
     * @brief toggleMinMaxMinima display/hide the result of the min-max calculation
     * @param display
     */
    void toggleMinMaxMinima(bool display);

    /**
     * @brief toggleMinMaxCircle display/hide the circle of a min-max minimum (if it exists)
     * @param display
     */
    void toggleMinMaxCircle(bool display);

    /**
     * @brief toggleMinSumMinima display/hide the result of the min-sum calculation
     * @param display
     */
    void toggleMinSumMinima(bool display);

    /**
     * @brief toggleShortestPathLabels display/hide labels for points on the shortest path
     * @param display
     */
    void toggleShortestPathLabels(bool display);

    /**
     * @brief togglePathEventLabels display/hide labels for points making up path events
     * @param display
     */
    void togglePathEventLabels(bool display);

    /**
     * @brief toggleBoundaryEventLabels display/hide labels for points making up boundary events
     * @param display
     */
    void toggleBoundaryEventLabels(bool display);

    /**
     * @brief toggleBendEventLabels display/hide labels for points making up bend events
     * @param display
     */
    void toggleBendEventLabels(bool display);

    /**
     * @brief togglePolygonLabels display/hide labels for points making up the polygon
     * @param display
     */
    void togglePolygonLabels(bool display);

    /**
     * @brief toggleMinMaxLabels display/hide labels for points making up the min-max solution
     * @param display
     */
    void toggleMinMaxLabels(bool display);

    /**
     * @brief toggleMinSumLabels display/hide labels for points making up the min-sum solution(s)
     * @param display
     */
    void toggleMinSumLabels(bool display);

    /**
     * @brief setDecimalPlaces sets the amount of decimal places to be displayed in labels
     * @param d
     */
    void setDecimalPlaces(int d);

    /**
     * @brief setTestData allows to display one of the polygons used in the tests of the library
     * @param numberOfTest
     */
    void setTestData(int numberOfTest);

    /**
     * @brief setTestDataScaleFactor set the factor by which the test polygon is magnified
     * @param f
     */
    void setTestDataScaleFactor(double f);

    /**
     * @brief reset clears all set data, so that a new polygon can be added
     */
    void reset();

signals:
    /**
     * @brief polygonReady emitted when the polygon and min calculations are ready
     */
    void polygonReady();

private:
    /**
     * @brief decimalPlaces how many decimal places to display in labels
     */
    int decimalPlaces;

    /**
     * @brief polygonIsClosed indicates if the polygon is closed
     */
    bool polygonIsClosed;

    /**
     * @brief numberOfPointsAdded indicates whether the start and end point have been added
     */
    int numberOfPointsAdded;

    /**
     * @brief displayDashLine indicates if the dashled line indicating the next edge of the
     * polyline should be displayed when the mouse is moved
     */
    bool displayDashLine;

    /**
     * @brief testDataScaleFactor indicate by how much to increase test data
     */
    double testDataScaleFactor;

    /**
     * @brief gC instance of the geometry connector class
     */
    CGALGeometryConnector gC;

    /**
     * @brief lastPolylinePoint last point of the current polyline
     */
    QPointF lastPolylinePoint;

    /**
     * @brief firstPolylinePoint first point of the polyline
     */
    QPointF firstPolylinePoint;

    /**
     * @brief firstPointDisplay graphic item representing the first point of the polyline
     */
    QGraphicsEllipseItem *firstPointDisplay;

    /**
     * @brief minMaxCircleCenter the center point of the min-max circle
     */
    QGraphicsEllipseItem *minMaxCircleCenter;

    /**
     * @brief startPoint graphic item representing the start point
     */
    QGraphicsEllipseItem *startPoint;

    /**
     * @brief endPoint graphic item representing the end point
     */
    QGraphicsEllipseItem *endPoint;

    /**
     * @brief lineToMousePosition the line between the last point of the polyline and th current
     * mouse position
     */
    QGraphicsLineItem* lineToMousePosition;

    /**
     * @brief circle displays the circle if a minium lies in a disc
     */
    QGraphicsPathItem *circle;
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

    /**
     * @brief closePolyline turns the polyline the user entered into a closed polygon
     */
    void closePolyline();

    /**
     * @brief handleNewPointForPolygon adds a new point to the polygon at position p. Determines
     * if the polyline should be closed to a polygon
     * @param p
     */
    void handleNewPointForPolygon(QPointF p);

    /**
     * @brief handleStartOrEndPoint add the start or end point at position p
     * @param p
     */
    void handleStartOrEndPoint(QPointF p);

    /**
     * @brief toggleEvents helper function to hide/display events
     * @param display
     * @param events
     * @param lines
     * @param isShortestPath
     */
    void toggleEvents(bool display, const std::vector<QLineF*> &events, std::vector<QGraphicsLineItem*> &lines, bool isShortestPath = false);

    /**
     * @brief toggleMinima helper function to hide/display minima
     * @param display
     * @param minima
     * @param lines
     */
    void toggleMinima(bool display, const std::vector<CGALGeometryConnector::MinData*> &minima, std::vector<QGraphicsLineItem*> &lines);

    /**
     * @brief toggleLabels helper function to hide/display event labels
     * @param display
     * @param lines
     * @param labels
     */
    void toggleLabels(bool display, const std::vector<QGraphicsLineItem*> &lines, std::vector<QGraphicsProxyWidget*> &labels);

    /**
     * @brief toggleMinLabels helper function to hide/displaye minimum labels
     * @param display
     * @param minima
     * @param labels
     */
    void toggleMinLabels(bool display, const std::vector<CGALGeometryConnector::MinData*> &minima, std::vector<QGraphicsProxyWidget*> &labels);

    /**
     * @brief roundToDecimalPlaces helper function to create a string from value with the number of
     * decimal places indicated by field decimalPlaces
     * @param value
     * @return
     */
    std::string roundToDecimalPlaces(double value);
};

#endif // VISIBILITYPROBLEMSCENE_H
