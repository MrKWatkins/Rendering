#pragma once
#include "Point.h"
#include "Vector.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Intersection
    {
        Point point;
        Vector surfaceNormal;

    public:
        Intersection(const Point& point, const Vector& surfaceNormal);

		const Point& Point() const noexcept { return point; }
        const Vector& SurfaceNormal() const noexcept { return surfaceNormal; }
    };
}
