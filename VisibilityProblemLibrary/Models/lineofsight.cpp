#include "lineofsight.h"

void SPV::LineOfSight::setEventType(EventType t)
{
    type = t;
}
EventType SPV::LineOfSight::getEventType()
{
    return type;
}

Point SPV::LineOfSight::getPointOnStartSide()
{
    return pointOnStartSide;
}

Point SPV::LineOfSight::getPointOnEndSide()
{
    return pointOnEndSide;
}

bool SPV::LineOfSight::isStartPointVertex()
{
    return pointOnStartSideIsVertex;
}

bool SPV::LineOfSight::isEndPointVertex()
{
    return pointOnEndSideIsVertex;
}
