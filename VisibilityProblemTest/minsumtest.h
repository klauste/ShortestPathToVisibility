#ifndef MINSUMTEST_H
#define MINSUMTEST_H
#include <QtTest>

// add necessary includes here
#include "Minima/minsumcalculator.h"
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

class MinSumTest : public QObject
{
    Q_OBJECT

public:
    MinSumTest();
    ~MinSumTest();
private:
    Polygon polygon;
    SPV::MinSumCalculator *minSumCalculator;
    SPV::GeometryUtil gU = SPV::GeometryUtil();

private slots:
    void minSumTest1();
    void minSumTest2();
    void minSumTest3();
    void minSumTest4();
    void minSumTest5();
    void minSumTest6();
    void minSumTest7();
    void minSumTest8();
    void minSumTest9();
    void minSumTest10();
    void minSumTest11();
    void minSumTest12();
    void minSumTest13();
    void minSumTest14();
    void minSumTest15();
    void minSumTest16();
    void minSumTest17();
    void minSumTest18();
    void minSumTest19();
    void minSumTest20();
    void minSumTest21();
    void minSumTest22();
    void minSumTest23();
    void minSumTest24();
};
#endif // MINSUMTEST_H
