#include <QtTest>
#include "shortestpathtest.h"
#include "bendeventtest.h"
#include "minsumtest.h"
#include "minmaxtest.h"

int main(int argc, char* argv[])
{
    int status = 0;
    {
        ShortestPathTest sP;
        status |= QTest::qExec(&sP, argc, argv);
    }
    {
        BendEventTest bE;
        status |= QTest::qExec(&bE, argc, argv);
    }
    {
        MinSumTest mS;
        status |= QTest::qExec(&mS, argc, argv);
    }
    {
        MinMaxTest mM;
        status != QTest::qExec(&mM, argc, argv);
    }
    return status;
}
