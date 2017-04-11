#include "stdafx.h"
#include "SurfaceIntersection.h"
#include "Solid.h"

namespace MrKWatkins::Rendering::Geometry
{
	bool Solid::Intersects(const Ray& ray) const
	{
		return NearestRayIntersection(ray).has_value();
	}

	std::optional<SurfaceIntersection> Solid::NearestSurfaceIntersection(const Ray& ray) const
	{
		auto rayIntersection = NearestRayIntersection(ray);
		if (rayIntersection.has_value())
		{
			return GetSurfaceIntersection(ray, rayIntersection.value());
		}
		return std::optional<SurfaceIntersection>();
	}

	SurfaceIntersection Solid::GetSurfaceIntersection(const Ray& ray, const RayIntersection& rayIntersection) const
	{
		// Plug d back into the ray's equation to get the intersection point.
		auto pointOnSurface = ray.Origin() + rayIntersection.D() * ray.Direction();

		return SurfaceIntersection(pointOnSurface, GetSurfaceNormal(rayIntersection, pointOnSurface));
	}
}
