#include "stdafx.h"
#include "SurfaceIntersection.h"

namespace MrKWatkins::Rendering::Geometry
{
	SurfaceIntersection::SurfaceIntersection(const Geometry::Point& point, const Vector& normal) : point{ point }, normal{ normal.Normalize() }
	{
	}
}
