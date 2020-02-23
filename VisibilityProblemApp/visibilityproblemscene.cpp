#include "visibilityproblemscene.h"
VisibilityProblemScene::VisibilityProblemScene()
{
    numberOfPointsAdded = 0;
    startPoint = nullptr;
    endPoint = nullptr;
    lineToMousePosition = nullptr;
    firstPointDisplay = nullptr;
    decimalPlaces = 0;
    testDataScaleFactor = 30;
    polygonIsClosed = false;
    displayDashLine = false;
    gC = CGALGeometryConnector();
    circle = nullptr;
    minMaxCircleCenter = nullptr;
}

void VisibilityProblemScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (polygonIsClosed && numberOfPointsAdded == 2) {
        return;
    }
    QPointF currentPos = mouseEvent->scenePos();

    if (!polygonIsClosed) {
        if (gC.shouldClosePolyline(currentPos)) {
            closePolyline();
            return;
        }
        if (gC.doSegmentsIntersect(currentPos)) {
            return;
        }
        handleNewPointForPolygon(currentPos);
        return;
    }

    handleStartOrEndPoint(currentPos);
}

void VisibilityProblemScene::handleStartOrEndPoint(QPointF p)
{
    if (gC.isPointInPolygon(p)) {
        QRectF currentRect = QRectF(p.x() - 3, p.y() - 3, 6, 6);

        if (numberOfPointsAdded == 0) {
            gC.handleFinalPoint(p, true);
            startPoint = addEllipse(
                currentRect,
                QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
                QBrush(Qt::black, Qt::SolidPattern)
            );
        } else {
            gC.handleFinalPoint(p, false);
            endPoint = addEllipse(
                currentRect,
                QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
                QBrush(Qt::black, Qt::SolidPattern)
            );
            // Let the main window know that calculations are done
            emit polygonReady();
        }
        numberOfPointsAdded++;
    }
}

void VisibilityProblemScene::handleNewPointForPolygon(QPointF p)
{
    gC.addPointToCGALPolygon(p);
    if (displayDashLine) {
        polygonLines.push_back(addLine(
            lastPolylinePoint.x(),
            lastPolylinePoint.y(),
            p.x(),
            p.y(),
            QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
        ));
    } else {
        firstPolylinePoint = p;
        QRectF currentRect = QRectF(p.x() - 3, p.y() - 3, 6, 6);
        firstPointDisplay = addEllipse(
            currentRect,
            QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
            QBrush(Qt::black, Qt::SolidPattern)
        );
        displayDashLine = true;
    }
    lastPolylinePoint = p;
}


void VisibilityProblemScene::closePolyline()
{
    polygonLines.push_back(addLine(
        lastPolylinePoint.x(),
        lastPolylinePoint.y(),
        firstPolylinePoint.x(),
        firstPolylinePoint.y(),
        QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
    ));
    delete firstPointDisplay;
    firstPointDisplay = nullptr;
    displayDashLine = false;
    delete lineToMousePosition;
    lineToMousePosition = nullptr;
    polygonIsClosed = true;
}

void VisibilityProblemScene::setDecimalPlaces(int d) {
    decimalPlaces = d;
}

/**
 * Handles mouse movement events
 *
 * @brief SPVGraphicsScene::mouseMoveEvent
 * @param mouseEvent
 */
void VisibilityProblemScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (!displayDashLine) {
        return;
    }
    QPointF currentPos = mouseEvent->scenePos();
    if (lineToMousePosition == nullptr) {
        lineToMousePosition = addLine(
            lastPolylinePoint.x(),
            lastPolylinePoint.y(),
            currentPos.x(),
            currentPos.y(),
            QPen(Qt::green, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin)
        );
    } else {
        lineToMousePosition->setLine(
            lastPolylinePoint.x(),
            lastPolylinePoint.y(),
            currentPos.x(),
            currentPos.y()
        );
        if (gC.doSegmentsIntersect(currentPos)) {
            lineToMousePosition->setPen(QPen(Qt::red, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
        } else {
            lineToMousePosition->setPen(QPen(Qt::green, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
        }
    }
}

void VisibilityProblemScene::toggleEvents(bool display, const std::vector<QLineF*>& events, std::vector<QGraphicsLineItem*> &lines, bool isShortestPath)
{
    QPen linesPen = QPen(Qt::black, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    if (isShortestPath) {
        linesPen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    }
    unsigned i;
    QLineF *currentLine;
    if (display) {
        for (i = 0; i < events.size(); i++) {
            currentLine = events.at(i);
            lines.push_back(
                addLine(
                    *(currentLine),
                    linesPen
                )
            );
        }
    }
    else {
        for (i = 0; i < lines.size(); i++) {
            removeItem(lines.at(i));
        }
        lines.clear();
    }
}

void VisibilityProblemScene::toggleMinima(bool display, const std::vector<CGALGeometryConnector::MinData*> &minima, std::vector<QGraphicsLineItem*> &lines)
{
    QPen linesPen = QPen(Qt::red, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QPen linesPenLos = QPen(Qt::black, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);

    unsigned i;
    if (display) {
        for (i = 0; i < minima.size(); i++) {
            lines.push_back(
                addLine(
                    *(minima.at(i)->loS),
                    linesPenLos
                )
            );
            for (unsigned j = 0; j < minima.at(i)->linesToMin.size(); j++) {
                lines.push_back(
                    addLine(
                        *(minima.at(i)->linesToMin.at(j)),
                        linesPen
                    )
                );
            }
        }
    } else {
        for (i = 0; i < lines.size(); i++) {
            removeItem(lines.at(i));
        }
        lines.clear();
    }
}

void VisibilityProblemScene::reset()
{
    unsigned i;
    toggleShortestPath(false);
    togglePathEvents(false);
    toggleBoundaryEvents(false);
    toggleBendEvents(false);
    toggleMinMaxMinima(false);
    toggleMinMaxCircle(false);
    toggleMinSumMinima(false);

    toggleShortestPathLabels(false);
    togglePathEventLabels(false);
    toggleBoundaryEventLabels(false);
    toggleBendEventLabels(false);
    toggleMinMaxLabels(false);
    toggleMinSumLabels(false);
    togglePolygonLabels(false);
    for (i = 0; i < polygonLines.size(); i++) {
        removeItem(polygonLines.at(i));
    }
    polygonLines.clear();
    if (startPoint) {
        delete startPoint;
        startPoint = nullptr;
    }
    if (endPoint) {
        delete endPoint;
        endPoint = nullptr;
    }
    if (circle) {
        removeItem(circle);
        delete circle;
        circle = nullptr;
    }
    if (minMaxCircleCenter) {
        removeItem(minMaxCircleCenter);
        delete minMaxCircleCenter;
        minMaxCircleCenter = nullptr;
    }
    if (lineToMousePosition) {
        removeItem(lineToMousePosition);
        delete lineToMousePosition;
        lineToMousePosition = nullptr;
    }
    if (firstPointDisplay) {
        removeItem(firstPointDisplay);
        delete firstPointDisplay;
        firstPointDisplay = nullptr;
    }
    polygonIsClosed = false;
    numberOfPointsAdded = 0;
    gC.reset();
    displayDashLine = false;
}

void VisibilityProblemScene::togglePathEvents(bool display)
{
    toggleEvents(display, gC.getPathEvents(), pathEvents);
}

void VisibilityProblemScene::toggleBoundaryEvents(bool display)
{
    toggleEvents(display, gC.getBoundaryEvents(), boundaryEvents);
}

void VisibilityProblemScene::toggleBendEvents(bool display)
{
    toggleEvents(display, gC.getBendEvents(), bendEvents);
}

void VisibilityProblemScene::toggleShortestPath(bool display)
{
    toggleEvents(display, gC.getShortestPathGraph(), shortestPath, true);
}

void VisibilityProblemScene::toggleMinMaxMinima(bool display)
{
    toggleMinima(display, gC.getMinMaxMinima(), minMaxLines);
}

void VisibilityProblemScene::toggleMinMaxCircle(bool display)
{
    if (display == true) {
        if (gC.getMinMaxMinima().size() > 0) {
            auto min = gC.getMinMaxMinima().at(0);
            if (min->hasRadius == true) {
                double radius = min->radius;
                QPointF center = min->centerPoint;
                circle = new QGraphicsPathItem();
                QPainterPath path = QPainterPath();
                path.moveTo(QPointF(center.x() + radius, center.y()));
                path.arcTo(QRectF(center.x() - radius, center.y() - radius, radius * 2, radius *2), 0, 360);
                circle->setPath(path);
                addItem(circle);

                QRectF currentRect = QRectF(center.x() - 3, center.y() - 3, 6, 6);
                minMaxCircleCenter = addEllipse(
                    currentRect,
                    QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
                    QBrush(Qt::black, Qt::SolidPattern)
                );
            }
        }
    } else if (circle) {
        removeItem(circle);
        delete circle;
        circle = nullptr;
        removeItem(minMaxCircleCenter);
        delete minMaxCircleCenter;
        minMaxCircleCenter = nullptr;
    }
}

void VisibilityProblemScene::toggleMinSumMinima(bool display)
{
    toggleMinima(display, gC.getMinSumMinima(), minSumLines);
}

void VisibilityProblemScene::toggleLabels(bool display, const std::vector<QGraphicsLineItem*> &lines, std::vector<QGraphicsProxyWidget*> &labels)
{
    unsigned i;
    int labelBuffer = 5;

    if (display) {
        for (i = 0; i < lines.size(); i++) {
            QLabel *qLabel = new QLabel();
            QLineF currentLine = lines.at(i)->line();
            std::string x = roundToDecimalPlaces(currentLine.x1());
            std::string y = roundToDecimalPlaces(currentLine.y1());
            std::string label = "(" + x + ", " + y + ")";
            qLabel->setText(label.c_str());
            qLabel->move(currentLine.x1() + labelBuffer, currentLine.y1() - labelBuffer);
            labels.push_back(addWidget(qLabel));
            qLabel = new QLabel();
            x = roundToDecimalPlaces(currentLine.x2());
            y = roundToDecimalPlaces(currentLine.y2());
            label = "(" + x + ", " + y + ")";
            qLabel->setText(label.c_str());
            qLabel->move(currentLine.x2() + labelBuffer, currentLine.y2() - labelBuffer);
            labels.push_back(addWidget(qLabel));
        }
    } else {
        for (i = 0; i < labels.size(); i++) {
            removeItem(labels.at(i));
        }
        labels.clear();
    }
}

void VisibilityProblemScene::togglePathEventLabels(bool display)
{
    toggleLabels(display, pathEvents, pathEventLabels);
}


void VisibilityProblemScene::toggleBoundaryEventLabels(bool display)
{
    toggleLabels(display, boundaryEvents, boundaryEventLabels);
}

void VisibilityProblemScene::toggleBendEventLabels(bool display)
{
    toggleLabels(display, bendEvents, bendEventLabels);
}

void VisibilityProblemScene::toggleShortestPathLabels(bool display)
{
    toggleLabels(display, shortestPath, shortestPathLabels);
}

void VisibilityProblemScene::togglePolygonLabels(bool display)
{
    unsigned i;
    int labelBuffer = 5;

    if (display) {
        for (i = 0; i < polygonLines.size(); i++) {
            QLabel *qLabel = new QLabel();
            QLineF currentLine = polygonLines.at(i)->line();
            std::string x = roundToDecimalPlaces(currentLine.x1());
            std::string y = roundToDecimalPlaces(currentLine.y1());
            std::string label = "(" + x + ", " + y + ")";
            qLabel->setText(label.c_str());
            qLabel->move(currentLine.x1() + labelBuffer, currentLine.y1() - labelBuffer);
            polygonLabels.push_back(addWidget(qLabel));
        }
    } else {
        for (i = 0; i < polygonLabels.size(); i++) {
            removeItem(polygonLabels.at(i));
        }
        polygonLabels.clear();
    }
}

void VisibilityProblemScene::toggleMinMaxLabels(bool display)
{
    toggleMinLabels(display, gC.getMinMaxMinima(), minMaxLabels);
}

void VisibilityProblemScene::toggleMinSumLabels(bool display)
{
    toggleMinLabels(display, gC.getMinSumMinima(), minSumLabels);
}

std::string VisibilityProblemScene::roundToDecimalPlaces(double value)
{
    double multValue = pow(10, decimalPlaces);
    double roundedValue = std::round(value * multValue);
    std::string stringValue = boost::lexical_cast<std::string>(roundedValue);
    std::string returnValue = "";
    int currentPosition = 1;

    for (int i = stringValue.size() - 1; i >= 0; i--) {
        if (decimalPlaces > 0 && decimalPlaces == currentPosition) {
            returnValue = std::string(".") + stringValue.at(i) + returnValue;
        } else {
            returnValue = stringValue.at(i) + returnValue;
        }
        currentPosition++;
    }
    return returnValue;
}

void VisibilityProblemScene::toggleMinLabels(bool display, const std::vector<CGALGeometryConnector::MinData*> &minima, std::vector<QGraphicsProxyWidget*> &labels)
{
    unsigned i;
    int labelBuffer = 5;
    if (display) {
        for (i = 0; i < minima.size(); i++) {
            QLabel *qLabel = new QLabel();
            std::string minValue = roundToDecimalPlaces(minima.at(i)->minValue);

            std::string x = roundToDecimalPlaces(minima.at(i)->pointOnStartSide.x());
            std::string y = roundToDecimalPlaces(minima.at(i)->pointOnStartSide.y());
            std::string label = "(" + x + ", " + y + "), distance: " + minValue;
            qLabel->setText(label.c_str());
            qLabel->move(minima.at(i)->pointOnStartSide.x() + labelBuffer, minima.at(i)->pointOnStartSide.y() - labelBuffer);
            labels.push_back(addWidget(qLabel));
            qLabel = new QLabel();
            x = roundToDecimalPlaces(minima.at(i)->pointOnEndSide.x());
            y = roundToDecimalPlaces(minima.at(i)->pointOnEndSide.y());
            label = "(" + x + ", " + y + "), distance: " + minValue;
            qLabel->setText(label.c_str());
            qLabel->move(minima.at(i)->pointOnEndSide.x() + labelBuffer,minima.at(i)->pointOnEndSide.y() - labelBuffer);
            labels.push_back(addWidget(qLabel));
        }
    } else {
        for (i = 0; i < labels.size(); i++) {
            removeItem(labels.at(i));
        }
        labels.clear();
    }
}

void VisibilityProblemScene::setTestDataScaleFactor(double f)
{
    testDataScaleFactor = f;
}


void VisibilityProblemScene::setTestData(int numberOfTest)
{
    reset();
    switch (numberOfTest) {
        case 1 :
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 6.0, testDataScaleFactor *12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.0,testDataScaleFactor * 12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.0,testDataScaleFactor * 9.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 13.0,testDataScaleFactor * 10.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 13.0,testDataScaleFactor * 11.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 15.0,testDataScaleFactor * 11.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 14.0,testDataScaleFactor * 7.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 15.0,testDataScaleFactor * 9.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 17.0,testDataScaleFactor * 7.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 21.0,testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 21.0,testDataScaleFactor * 4.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 17.0,testDataScaleFactor * 2.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 11.5,testDataScaleFactor * 3.5));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 10.0,testDataScaleFactor * 2.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 7.0, testDataScaleFactor * 2.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.5, testDataScaleFactor * 3.5));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 7.0, testDataScaleFactor * 3.5));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 6.0, testDataScaleFactor * 5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0, testDataScaleFactor * 6.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 9.0, testDataScaleFactor * 4.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 15.0,testDataScaleFactor * 4.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 20.0,testDataScaleFactor * 5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 9.0, testDataScaleFactor * 5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 10.9,testDataScaleFactor * 8.3));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 9.0, testDataScaleFactor * 7.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 11.0,testDataScaleFactor * 9.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0, testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0, testDataScaleFactor * 10.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 6.0, testDataScaleFactor * 10.0));
            closePolyline();
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 10.5, testDataScaleFactor * 11.0));
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 8.0,  testDataScaleFactor * 5.0));
            break;
        case 2 :
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 16.0, testDataScaleFactor *12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 19.0, testDataScaleFactor *12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 19.0, testDataScaleFactor *7.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 13.0, testDataScaleFactor *7.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 14.0, testDataScaleFactor *5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 18.0, testDataScaleFactor *5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 18.0, testDataScaleFactor *3.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.0, testDataScaleFactor *3.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 11.0, testDataScaleFactor *5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0,  testDataScaleFactor *5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.5, testDataScaleFactor *6));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 11.0, testDataScaleFactor *8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 14.5, testDataScaleFactor *7.5));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 11.0, testDataScaleFactor *12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 14.0, testDataScaleFactor *12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 14.0, testDataScaleFactor *10.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 15.0, testDataScaleFactor *8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 16.0, testDataScaleFactor *10.0));
            closePolyline();
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 17.0, testDataScaleFactor * 11.0));
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 17.0, testDataScaleFactor * 4.0));
            break;
        case 3 :
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 6.0,  testDataScaleFactor * 12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.0, testDataScaleFactor * 12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.0, testDataScaleFactor * 9.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 14.0, testDataScaleFactor * 7.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 16.0, testDataScaleFactor * 7.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 17.0, testDataScaleFactor * 9.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 17.0, testDataScaleFactor * 12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 21.0, testDataScaleFactor * 12.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 21.0, testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 18.0, testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 21.0, testDataScaleFactor * 5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 16.0, testDataScaleFactor * 6.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 14.0, testDataScaleFactor * 3.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 13.0, testDataScaleFactor * 5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 10.0, testDataScaleFactor * 5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 11.0, testDataScaleFactor * 9.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0,  testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0,  testDataScaleFactor * 10.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 6.0,  testDataScaleFactor * 10.0));
            closePolyline();
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 11.0, testDataScaleFactor * 11.0));
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 19.0, testDataScaleFactor * 11.0));
            break;
        case 4 :
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 3.0,  testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 3.0,  testDataScaleFactor * 2.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.0, testDataScaleFactor * 2.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.0, testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0,  testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 7.0,  testDataScaleFactor * 4.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 6.0,  testDataScaleFactor * 8.0));
            closePolyline();
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 6.5, testDataScaleFactor * 5.0));
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 8.5, testDataScaleFactor * 7.5));
            break;
        case 5 :
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 1.0,  testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 4.0,  testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 5.0,  testDataScaleFactor * 5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 6.0,  testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 7.0,  testDataScaleFactor * 5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0,  testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 9.0,  testDataScaleFactor * 5.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 10.0, testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 13.0, testDataScaleFactor * 8.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 13.0, testDataScaleFactor * 3.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 9.0,  testDataScaleFactor * 3.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0,  testDataScaleFactor * 6.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 7.0,  testDataScaleFactor * 3.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 6.0,  testDataScaleFactor * 6.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 5.0,  testDataScaleFactor * 3.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 1.0,  testDataScaleFactor * 3.0));
            closePolyline();
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 4.0, testDataScaleFactor * 6.0));
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 10.0, testDataScaleFactor * 6.0));
            break;
        case 6 :
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 0.0,  testDataScaleFactor * 6.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 4.0,  testDataScaleFactor * 6.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 6.0,  testDataScaleFactor * 2.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 8.0,  testDataScaleFactor * 6.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.0, testDataScaleFactor * 6.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 12.0, testDataScaleFactor * 3.0));
            handleNewPointForPolygon(QPointF(testDataScaleFactor * 0.0,  testDataScaleFactor * 0.0));
            closePolyline();
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 1.0, testDataScaleFactor * 4.0));
            handleStartOrEndPoint(QPointF(testDataScaleFactor * 11.1, testDataScaleFactor * 4.04));
            break;
    }
}
