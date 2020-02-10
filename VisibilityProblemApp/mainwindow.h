#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "visibilityproblemscene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

public slots:
    void onPolygonReady();

private slots:
    void pathEventLabelButtonClicked();
    void boundaryEventLabelButtonClicked();
    void bendEventLabelButtonClicked();
    void shortestPathLabelButtonClicked();
    void minMaxLabelButtonClicked();
    void minSumLabelButtonClicked();
    void polygonLabelButtonClicked();

    void pathEventsButtonClicked();
    void boundaryEventsButtonClicked();
    void bendEventsButtonClicked();
    void shortestPathButtonClicked();

    void testData1ButtonClicked();
    void testData2ButtonClicked();
    void testData3ButtonClicked();

    void scaleFactorThirtyClicked();
    void scaleFactorFortyClicked();
    void scaleFactorFiftyClicked();
    void scaleFactorSixtyClicked();

    void minMaxButtonClicked();
    void minSumButtonClicked();

    void noDecimalPlaceClicked();
    void oneDecimalPlaceClicked();
    void twoDecimalPlacesClicked();
    void threeDecimalPlacesClicked();
    void fourDecimalPlacesClicked();

    void resetButtonClicked();

private:
    QGraphicsView *centralView;
    VisibilityProblemScene scene;
    QAction *pathEventButton;
    QAction *boundaryEventButton;
    QAction *bendEventButton;
    QAction *shortestPathButton;

    QAction *pathEventLabelButton;
    QAction *boundaryEventLabelButton;
    QAction *bendEventLabelButton;
    QAction *shortestPathLabelButton;
    QAction *minMaxLabelButton;
    QAction *minSumLabelButton;
    QAction *polygonLabelButton;

    QAction *resetButton;
    QAction *noDecimalPlace;
    QAction *oneDecimalPlace;
    QAction *twoDecimalPlaces;
    QAction *threeDecimalPlaces;
    QAction *fourDecimalPlaces;
    QAction *scaleFactorThirty;
    QAction *scaleFactorForty;
    QAction *scaleFactorFifty;
    QAction *scaleFactorSixty;

    QAction *minMaxButton;
    QAction *minSumButton;
    QAction *testData1Button;
    QAction *testData2Button;
    QAction *testData3Button;

    void addMenuItems();
    void addEventButtons();
    void addLabelButtons();
    void addTestDataButtons();
    void addToolButtons();
    void drawAll();
};

#endif // MAINWINDOW_H
