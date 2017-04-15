#include "stdafx.h"
#include "Intersection.h"
#include "Ray.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	Intersection::Intersection(const Geometry::Ray& ray, double distanceAlongRay) : ray { &ray }, distanceAlongRay { distanceAlongRay }
	{
	}

	Intersection::Intersection(const Geometry::Ray& ray, double distanceAlongRay, const Vector& normal) : normal { normal }, ray{ &ray }, distanceAlongRay{ distanceAlongRay }
	{
	}

	Vector Intersection::CalculateNormal() const
	{
		throw std::exception("Not implemented.");
	}

	const Point& Intersection::Point() const
	{
		if (!point.has_value())
		{
			point = ray->ResolveDistance(distanceAlongRay);
		}
		return point.value();
	}

	const Vector& Intersection::Normal() const
	{
		if (!normal.has_value())
		{
			normal = CalculateNormal();

			// We don't call Normalize() here as a lot of the solids will be able to return a normalized vector without any extra work so we can save ourselves a call.
			VERIFY_IS_NORMALIZED(normal.value());
		}
		return normal.value();
	}
}
