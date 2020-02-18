#include "Models/sweptsegment.h"

std::shared_ptr<SPV::SweptSegment> SPV::SweptSegment::getClone()
{
    return std::make_shared<SweptSegment>(leftPoint, leftPointPolygonVertex, rightPoint, rightPointPolygonVertex);
}

Point SPV::SweptSegment::getLeftPoint()
{
    return leftPoint;
}

bool SPV::SweptSegment::leftPointIsPolygonVertex()
{
    return leftPointPolygonVertex;
}

Point SPV::SweptSegment::getRightPoint()
{
    return rightPoint;
}

bool SPV::SweptSegment::rightPointIsPolygonVertex()
{
    return rightPointPolygonVertex;
}
