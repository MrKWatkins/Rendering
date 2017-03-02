#include "stdafx.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Geometry
{
    Intersection::Intersection(): hasIntersection{ false }, point { Point::Origin() }, normal { Vector::Zero() }
    {
    }

    Intersection::Intersection(Geometry::Point point, Vector normal) : hasIntersection{ true }, point{ point }, normal{ normal.Normalize() }
    {
    }

    Point Intersection::Point() const
    {
        VerifyIntersection();
        return point;
    }

    Vector Intersection::Normal() const
    {
        VerifyIntersection();
        return normal;
    }
}
