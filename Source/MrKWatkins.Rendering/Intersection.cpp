#include "stdafx.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Geometry
{
    Intersection::Intersection(const Geometry::Point& point, const Vector& surfaceNormal) : point{ point }, surfaceNormal{ surfaceNormal.Normalize() }
    {
    }
}
