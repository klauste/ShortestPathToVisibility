#include <QtTest>
#include "bendeventtest.h"
#include "minsumtest.h"

int main(int argc, char* argv[])
{
    int status = 0;
    {
        //BendEventTest bE;
        //status |= QTest::qExec(&bE, argc, argv);
    }
    {
        MinSumTest mS;
        status |= QTest::qExec(&mS, argc, argv);
    }
    return status;
}
