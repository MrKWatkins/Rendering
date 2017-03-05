#include "stdafx.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Geometry
{
    Intersection::Intersection(): hasIntersection{ false }, point { Point::Origin() }, surfaceNormal{ Vector::Zero() }
    {
    }

    Intersection::Intersection(const Geometry::Point& point, const Vector& surfaceNormal) : hasIntersection{ true }, point{ point }, surfaceNormal{ surfaceNormal.Normalize() }
    {
    }

    const Point& Intersection::Point() const
    {
        VerifyIntersection();
        return point;
    }

    const Vector& Intersection::SurfaceNormal() const
    {
        VerifyIntersection();
        return surfaceNormal;
    }
}
