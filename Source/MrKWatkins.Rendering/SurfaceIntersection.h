#pragma once
#include "Point.h"
#include "Vector.h"

namespace MrKWatkins::Rendering::Geometry
{
	/// <summary>
	/// Details of an interaction with a point on a surface.
	/// </summary>
    class SurfaceIntersection
    {
        Point point;
        Vector normal;

    public:
		SurfaceIntersection(const Point& point, const Vector& normal);

		const Point& Point() const noexcept { return point; }
        const Vector& Normal() const noexcept { return normal; }
    };
}
