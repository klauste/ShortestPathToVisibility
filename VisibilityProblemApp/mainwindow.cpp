#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    addMenuItems();
    setGeometry(0, 0, 800, 800);
    centralView = new QGraphicsView(&scene, this);
    centralView->setSceneRect(QRectF(0, 0, 750, 750));
    centralView->setMouseTracking(true);
    centralView->show();
    setCentralWidget(centralView);
    connect(&scene, &VisibilityProblemScene::polygonReady, this, &MainWindow::onPolygonReady);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    scene.reset();
}

void MainWindow::addMenuItems()
{
    minMaxButton = new QAction("Min Max", this);
    minMaxButton->setCheckable(true);
    minMaxButton->setChecked(true);
    minMaxButton->setEnabled(false);
    connect(minMaxButton, SIGNAL(triggered()), this, SLOT(minMaxButtonClicked()));

    minMaxCircleButton = new QAction("Min Max Circle", this);
    minMaxCircleButton->setCheckable(true);
    minMaxCircleButton->setChecked(false);
    minMaxCircleButton->setEnabled(false);
    connect(minMaxCircleButton, SIGNAL(triggered()), this, SLOT(minMaxCircleButtonClicked()));

    minSumButton = new QAction("Min Sum", this);
    minSumButton->setCheckable(true);
    minSumButton->setChecked(false);
    minSumButton->setEnabled(false);
    connect(minSumButton, SIGNAL(triggered()), this, SLOT(minSumButtonClicked()));

    QMenu *minimumMenu = menuBar()->addMenu("Minimum Type");
    minimumMenu->addAction(minMaxButton);
    minimumMenu->addAction(minMaxCircleButton);
    minimumMenu->addAction(minSumButton);

    addEventButtons();
    addLabelButtons();
    addTestDataButtons();
    addToolButtons();
}

void MainWindow::addToolButtons()
{
    QMenu *toolsMenu = menuBar()->addMenu("Tools");
    resetButton = new QAction("Reset", this);
    resetButton->setEnabled(false);
    connect(resetButton, SIGNAL(triggered()), this, SLOT(resetButtonClicked()));
    toolsMenu->addAction(resetButton);

    animateButton = new QAction("Animate", this);
    animateButton->setEnabled(false);
    connect(animateButton, SIGNAL(triggered()), this, SLOT(animateButtonClicked()));
    toolsMenu->addAction(animateButton);

    QMenu *precisionMenu = toolsMenu->addMenu("Decimal Places");
    noDecimalPlace = new QAction("0", this);
    connect(noDecimalPlace, SIGNAL(triggered()), this, SLOT(noDecimalPlaceClicked()));

    oneDecimalPlace = new QAction("1", this);
    connect(oneDecimalPlace, SIGNAL(triggered()), this, SLOT(oneDecimalPlaceClicked()));

    twoDecimalPlaces = new QAction("2", this);
    connect(twoDecimalPlaces, SIGNAL(triggered()), this, SLOT(twoDecimalPlacesClicked()));

    threeDecimalPlaces = new QAction("3", this);
    connect(threeDecimalPlaces, SIGNAL(triggered()), this, SLOT(threeDecimalPlacesClicked()));

    fourDecimalPlaces = new QAction("4", this);
    connect(fourDecimalPlaces, SIGNAL(triggered()), this, SLOT(fourDecimalPlacesClicked()));

    precisionMenu->addAction(noDecimalPlace);
    precisionMenu->addAction(oneDecimalPlace);
    precisionMenu->addAction(twoDecimalPlaces);
    precisionMenu->addAction(threeDecimalPlaces);
    precisionMenu->addAction(fourDecimalPlaces);

    QMenu *scaleFactorMenu = toolsMenu->addMenu("Test Scale Factor");
    scaleFactorThirty = new QAction("30", this);
    connect(scaleFactorThirty, SIGNAL(triggered()), this, SLOT(scaleFactorThirtyClicked()));

    scaleFactorForty = new QAction("40", this);
    connect(scaleFactorForty, SIGNAL(triggered()), this, SLOT(scaleFactorFortyClicked()));

    scaleFactorFifty = new QAction("50", this);
    connect(scaleFactorFifty, SIGNAL(triggered()), this, SLOT(scaleFactorFiftyClicked()));

    scaleFactorSixty = new QAction("60", this);
    connect(scaleFactorSixty, SIGNAL(triggered()), this, SLOT(scaleFactorSixtyClicked()));

    scaleFactorMenu->addAction(scaleFactorThirty);
    scaleFactorMenu->addAction(scaleFactorForty);
    scaleFactorMenu->addAction(scaleFactorFifty);
    scaleFactorMenu->addAction(scaleFactorSixty);;
}

void MainWindow::addEventButtons()
{
    pathEventButton = new QAction("Path Events", this);
    pathEventButton->setCheckable(true);
    pathEventButton->setChecked(false);
    pathEventButton->setEnabled(false);
    connect(pathEventButton, SIGNAL(triggered()), this, SLOT(pathEventsButtonClicked()));

    boundaryEventButton = new QAction("Boundary Events", this);
    boundaryEventButton->setCheckable(true);
    boundaryEventButton->setChecked(false);
    boundaryEventButton->setEnabled(false);
    connect(boundaryEventButton, SIGNAL(triggered()), this, SLOT(boundaryEventsButtonClicked()));

    bendEventButton = new QAction("Bend Events", this);
    bendEventButton->setCheckable(true);
    bendEventButton->setChecked(false);
    bendEventButton->setEnabled(false);
    connect(bendEventButton, SIGNAL(triggered()), this, SLOT(bendEventsButtonClicked()));

    shortestPathButton = new QAction("Shortest Path", this);
    shortestPathButton->setCheckable(true);
    shortestPathButton->setChecked(false);
    shortestPathButton->setEnabled(false);
    connect(shortestPathButton, SIGNAL(triggered()), this, SLOT(shortestPathButtonClicked()));

    QMenu *eventButtonsMenu = menuBar()->addMenu("Events");
    eventButtonsMenu->addAction(pathEventButton);
    eventButtonsMenu->addAction(boundaryEventButton);
    eventButtonsMenu->addAction(bendEventButton);
    eventButtonsMenu->addAction(shortestPathButton);
}

void MainWindow::addLabelButtons()
{
    pathEventLabelButton = new QAction("Path Event Labels", this);
    pathEventLabelButton->setCheckable(true);
    pathEventLabelButton->setChecked(false);
    pathEventLabelButton->setEnabled(false);
    connect(pathEventLabelButton, SIGNAL(triggered()), this, SLOT(pathEventLabelButtonClicked()));

    boundaryEventLabelButton = new QAction("Boundary Event Labels", this);
    boundaryEventLabelButton->setCheckable(true);
    boundaryEventLabelButton->setChecked(false);
    boundaryEventLabelButton->setEnabled(false);
    connect(boundaryEventLabelButton, SIGNAL(triggered()), this, SLOT(boundaryEventLabelButtonClicked()));

    bendEventLabelButton = new QAction("Bend Event Labels", this);
    bendEventLabelButton->setCheckable(true);
    bendEventLabelButton->setChecked(false);
    bendEventLabelButton->setEnabled(false);
    connect(bendEventLabelButton, SIGNAL(triggered()), this, SLOT(bendEventLabelButtonClicked()));

    shortestPathLabelButton = new QAction("Shortest Path Labels", this);
    shortestPathLabelButton->setCheckable(true);
    shortestPathLabelButton->setChecked(false);
    shortestPathLabelButton->setEnabled(false);
    connect(shortestPathLabelButton, SIGNAL(triggered()), this, SLOT(shortestPathLabelButtonClicked()));

    minMaxLabelButton = new QAction("Min Max Labels", this);
    minMaxLabelButton->setCheckable(true);
    minMaxLabelButton->setChecked(false);
    minMaxLabelButton->setEnabled(false);
    connect(minMaxLabelButton, SIGNAL(triggered()), this, SLOT(minMaxLabelButtonClicked()));

    minSumLabelButton = new QAction("Min Sum Labels", this);
    minSumLabelButton->setCheckable(true);
    minSumLabelButton->setChecked(false);
    minSumLabelButton->setEnabled(false);
    connect(minSumLabelButton, SIGNAL(triggered()), this, SLOT(minSumLabelButtonClicked()));

    polygonLabelButton = new QAction("Polygon Labels", this);
    polygonLabelButton->setCheckable(true);
    polygonLabelButton->setChecked(false);
    polygonLabelButton->setEnabled(false);
    connect(polygonLabelButton, SIGNAL(triggered()), this, SLOT(polygonLabelButtonClicked()));

    QMenu *labelMenu = menuBar()->addMenu("Labels");
    labelMenu->addAction(pathEventLabelButton);
    labelMenu->addAction(boundaryEventLabelButton);
    labelMenu->addAction(bendEventLabelButton);
    labelMenu->addAction(shortestPathLabelButton);
    labelMenu->addAction(minMaxLabelButton);
    labelMenu->addAction(minSumLabelButton);
    labelMenu->addAction(polygonLabelButton);
}


void MainWindow::addTestDataButtons()
{
    testData1Button = new QAction("Test data 1", this);
    testData1Button->setEnabled(true);
    connect(testData1Button, SIGNAL(triggered()), this, SLOT(testData1ButtonClicked()));

    testData2Button = new QAction("Test data 2", this);
    testData2Button->setEnabled(true);
    connect(testData2Button, SIGNAL(triggered()), this, SLOT(testData2ButtonClicked()));

    testData3Button = new QAction("Test data 3", this);
    testData3Button->setEnabled(true);
    connect(testData3Button, SIGNAL(triggered()), this, SLOT(testData3ButtonClicked()));

    testData4Button = new QAction("Test data 4", this);
    testData4Button->setEnabled(true);
    connect(testData4Button, SIGNAL(triggered()), this, SLOT(testData4ButtonClicked()));

    testData5Button = new QAction("Test data 5", this);
    testData5Button->setEnabled(true);
    connect(testData5Button, SIGNAL(triggered()), this, SLOT(testData5ButtonClicked()));

    testData6Button = new QAction("Test data 6", this);
    testData6Button->setEnabled(true);
    connect(testData6Button, SIGNAL(triggered()), this, SLOT(testData6ButtonClicked()));

    QMenu *testDataMenu = menuBar()->addMenu("Load test data");
    testDataMenu->addAction(testData1Button);
    testDataMenu->addAction(testData2Button);
    testDataMenu->addAction(testData3Button);
    testDataMenu->addAction(testData4Button);
    testDataMenu->addAction(testData5Button);
    testDataMenu->addAction(testData6Button);
}

void MainWindow::pathEventsButtonClicked()
{
    scene.togglePathEvents(pathEventButton->isChecked());
    pathEventLabelButton->setEnabled(pathEventButton->isChecked());
    scene.togglePathEventLabels(pathEventButton->isChecked() && pathEventLabelButton->isChecked());
}

void MainWindow::boundaryEventsButtonClicked()
{
    scene.toggleBoundaryEvents(boundaryEventButton->isChecked());
    boundaryEventLabelButton->setEnabled(boundaryEventButton->isChecked());
    scene.toggleBoundaryEventLabels(boundaryEventButton->isChecked() && boundaryEventLabelButton->isChecked());
}

void MainWindow::bendEventsButtonClicked()
{
    scene.toggleBendEvents(bendEventButton->isChecked());
    bendEventLabelButton->setEnabled(bendEventButton->isChecked());
    scene.toggleBendEventLabels(bendEventButton->isChecked() && bendEventLabelButton->isChecked());
}

void MainWindow::shortestPathButtonClicked()
{
    scene.toggleShortestPath(shortestPathButton->isChecked());
    shortestPathLabelButton->setEnabled(shortestPathButton->isChecked());
    scene.toggleShortestPathLabels(shortestPathButton->isChecked() && shortestPathLabelButton->isChecked());
}

void MainWindow::pathEventLabelButtonClicked()
{
    scene.togglePathEventLabels(pathEventButton->isChecked() && pathEventLabelButton->isChecked());
}

void MainWindow::boundaryEventLabelButtonClicked()
{
    scene.toggleBoundaryEventLabels(boundaryEventButton->isChecked() && boundaryEventLabelButton->isChecked());
}

void MainWindow::bendEventLabelButtonClicked()
{
    scene.toggleBendEventLabels(bendEventButton->isChecked() && bendEventLabelButton->isChecked());
}

void MainWindow::shortestPathLabelButtonClicked()
{
    scene.toggleShortestPathLabels(shortestPathButton->isChecked() && shortestPathLabelButton->isChecked());
}

void MainWindow::minMaxLabelButtonClicked()
{
    scene.toggleMinMaxLabels(minMaxButton->isChecked() && minMaxLabelButton->isChecked());
}

void MainWindow::minSumLabelButtonClicked()
{
    scene.toggleMinSumLabels(minSumButton->isChecked() && minSumLabelButton->isChecked());
}

void MainWindow::polygonLabelButtonClicked()
{
    scene.togglePolygonLabels(polygonLabelButton->isChecked());
}

void MainWindow::testData1ButtonClicked()
{
    scene.setTestData(1);
}

void MainWindow::testData2ButtonClicked()
{
    scene.setTestData(2);
}

void MainWindow::testData3ButtonClicked()
{
    scene.setTestData(3);
}

void MainWindow::testData4ButtonClicked()
{
    scene.setTestData(4);
}

void MainWindow::testData5ButtonClicked()
{
    scene.setTestData(5);
}

void MainWindow::testData6ButtonClicked()
{
    scene.setTestData(6);
}

void MainWindow::minMaxButtonClicked()
{
    scene.toggleMinMaxMinima(minMaxButton->isChecked());
    minMaxLabelButton->setEnabled(minMaxButton->isChecked());
    scene.toggleMinMaxLabels(minMaxButton->isChecked() && minMaxLabelButton->isChecked());
}

void MainWindow::minMaxCircleButtonClicked()
{
    scene.toggleMinMaxCircle(minMaxCircleButton->isChecked());
}

void MainWindow::minSumButtonClicked()
{
    scene.toggleMinSumMinima(minSumButton->isChecked());
    minSumLabelButton->setEnabled(minSumButton->isChecked());
    scene.toggleMinSumLabels(minSumButton->isChecked() && minSumLabelButton->isChecked());
}

void MainWindow::resetButtonClicked()
{
    scene.reset();
    minMaxButton->setEnabled(false);
    minMaxCircleButton->setEnabled(false);
    minSumButton->setEnabled(false);
    resetButton->setEnabled(false);
    animateButton->setEnabled(false);
    shortestPathButton->setEnabled(false);
    pathEventButton->setEnabled(false);
    boundaryEventButton->setEnabled(false);
    bendEventButton->setEnabled(false);
}

void MainWindow::animateButtonClicked()
{
    scene.startAnimation();
};

void MainWindow::onPolygonReady()
{
    minMaxButton->setEnabled(true);
    minMaxCircleButton->setEnabled(true);
    minMaxLabelButton->setEnabled(true);
    minSumButton->setEnabled(true);
    resetButton->setEnabled(true);
    animateButton->setEnabled(true);
    shortestPathButton->setEnabled(true);
    pathEventButton->setEnabled(true);
    boundaryEventButton->setEnabled(true);
    bendEventButton->setEnabled(true);
    polygonLabelButton->setEnabled(true);

    drawAll();
}

void MainWindow::drawAll()
{
    if (minMaxButton->isChecked()) {
        scene.toggleMinMaxMinima(false);
        scene.toggleMinMaxMinima(true);
    }
    if (minMaxCircleButton->isChecked()) {
        scene.toggleMinMaxCircle(false);
        scene.toggleMinMaxCircle(true);
    }
    if (minSumButton->isChecked()) {
        scene.toggleMinSumMinima(false);
        scene.toggleMinSumMinima(true);
    }
    if (pathEventButton->isChecked()) {
        scene.togglePathEvents(false);
        scene.togglePathEvents(true);
    }
    if (boundaryEventButton->isChecked()) {
        scene.toggleBoundaryEvents(false);
        scene.toggleBoundaryEvents(true);
    }
    if (bendEventButton->isChecked()) {
        scene.toggleBoundaryEvents(false);
        scene.toggleBoundaryEvents(true);
    }
    if (shortestPathButton->isChecked()) {
        scene.toggleShortestPath(false);
        scene.toggleShortestPath(true);
    }
    if (minMaxLabelButton->isChecked()) {
        scene.toggleMinMaxLabels(false);
        scene.toggleMinMaxLabels(true);
    }
    if (minSumLabelButton->isChecked()) {
        scene.toggleMinSumLabels(false);
        scene.toggleMinSumLabels(true);
    }
    if (pathEventLabelButton->isChecked()) {
        scene.togglePathEventLabels(false);
        scene.togglePathEventLabels(true);
    }
    if (boundaryEventLabelButton->isChecked()) {
        scene.toggleBoundaryEventLabels(false);
        scene.toggleBoundaryEventLabels(true);
    }
    if (bendEventLabelButton->isChecked()) {
        scene.toggleBoundaryEventLabels(false);
        scene.toggleBoundaryEventLabels(true);
    }
    if (shortestPathLabelButton->isChecked()) {
        scene.toggleShortestPathLabels(false);
        scene.toggleShortestPathLabels(true);
    }
    if (polygonLabelButton->isChecked()) {
        scene.togglePolygonLabels(false);
        scene.togglePolygonLabels(true);
    }
}

void MainWindow::noDecimalPlaceClicked()
{
    scene.setDecimalPlaces(0);
    drawAll();
}

void MainWindow::oneDecimalPlaceClicked()
{
    scene.setDecimalPlaces(1);
    drawAll();
}

void MainWindow::twoDecimalPlacesClicked()
{
    scene.setDecimalPlaces(2);
    drawAll();
}

void MainWindow::threeDecimalPlacesClicked()
{
    scene.setDecimalPlaces(3);
    drawAll();
}

void MainWindow::fourDecimalPlacesClicked()
{
    scene.setDecimalPlaces(4);
    drawAll();
}

void MainWindow::scaleFactorThirtyClicked()
{
    scene.setTestDataScaleFactor(30);
}

void MainWindow::scaleFactorFortyClicked()
{
    scene.setTestDataScaleFactor(40);
}
void MainWindow::scaleFactorFiftyClicked()
{
    scene.setTestDataScaleFactor(50);
}

void MainWindow::scaleFactorSixtyClicked()
{
    scene.setTestDataScaleFactor(60);
}
