#ifndef MINMAXTEST_H
#define MINMAXTEST_H
#include <QtTest>

// add necessary includes here
#include "Minima/minmaxcalculator.h"
#include "Models/eventsegment.h"
#include "Models/lineofsight.h"
#include "Utils/geometryutil.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon;

class MinMaxTest : public QObject
{
    Q_OBJECT

public:
    MinMaxTest();
    ~MinMaxTest();
private:
    Polygon polygon;
    SPV::MinMaxCalculator *minMaxCalculator;
    SPV::GeometryUtil gU = SPV::GeometryUtil();

private slots:
    void minMaxTest1();
    void minMaxTest2();
    void minMaxTest3();
    void minMaxTest4();
    void minMaxTest5();
    void minMaxTest6();
    void minMaxTest7();
    void minMaxTest8();
    void minMaxTest9();
    void minMaxTest10();
    void minMaxTest11();
    void minMaxTest12();
    void minMaxTest13();
    void minMaxTest14();
    void minMaxTest15();
    void minMaxTest16();
    void minMaxTest17();
    void minMaxTest18();
};
#endif // MINMAXTEST_H
