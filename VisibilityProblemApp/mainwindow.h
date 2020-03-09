#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "visibilityproblemscene.h"

/**
 * @brief The MainWindow class is the main controller for the GUI. It owns a scene where polygons and
 * results can be displayed and listens to button clicks.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

    /**
     * @brief closeEvent listens to the close event and does some clean up
     * @param event
     */
    void closeEvent (QCloseEvent *event);

public slots:
    /**
     * @brief onPolygonReady listens to the polygonReady signal from VisibilityProblemScene
     * and enables the buttons and tools which are available once the solution for the min-max
     * and min-sum problem is ready
     */
    void onPolygonReady();

// Listeners for button clicks
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
    void testData4ButtonClicked();
    void testData5ButtonClicked();
    void testData6ButtonClicked();

    void scaleFactorThirtyClicked();
    void scaleFactorFortyClicked();
    void scaleFactorFiftyClicked();
    void scaleFactorSixtyClicked();

    void minMaxButtonClicked();
    void minSumButtonClicked();
    void minMaxCircleButtonClicked();

    void noDecimalPlaceClicked();
    void oneDecimalPlaceClicked();
    void twoDecimalPlacesClicked();
    void threeDecimalPlacesClicked();
    void fourDecimalPlacesClicked();

    void resetButtonClicked();
    void animateButtonClicked();

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
    QAction *minMaxCircleButton;
    QAction *polygonLabelButton;

    QAction *resetButton;
    QAction *animateButton;
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
    QAction *testData4Button;
    QAction *testData5Button;
    QAction *testData6Button;

    void addMenuItems();
    void addEventButtons();
    void addLabelButtons();
    void addTestDataButtons();
    void addToolButtons();
    void drawAll();
};

#endif // MAINWINDOW_H
