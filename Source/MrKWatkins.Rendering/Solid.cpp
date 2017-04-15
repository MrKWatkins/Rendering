#include "stdafx.h"
#include "Solid.h"

namespace MrKWatkins::Rendering::Geometry
{
	bool Solid::Intersects(const Ray& ray) const
	{
		return NearestIntersection(ray) != nullptr;
	}
}
