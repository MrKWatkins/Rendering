#include "stdafx.h"
#include "AxisAlignedBox.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	AxisAlignedBox::AxisAlignedBox(const Point& minimum, const Point& maximum) : minimum{ minimum }, maximum{ maximum }
	{
		VERIFY_GREATER_THAN_OR_EQUAL_TO(minimum.X(), maximum.X());
		VERIFY_GREATER_THAN_OR_EQUAL_TO(minimum.Y(), maximum.Y());
		VERIFY_GREATER_THAN_OR_EQUAL_TO(minimum.Z(), maximum.Z());
	}

	AxisAlignedBox::AxisAlignedBox(const Point& closestCorner, double width, double height, double depth) : AxisAlignedBox(closestCorner, closestCorner + Vector(width, height, depth))
	{
	}

	std::optional<Intersection> AxisAlignedBox::NearestIntersection(const Ray& ray) const
	{
		throw std::exception("Not implemented.");
	}
}
