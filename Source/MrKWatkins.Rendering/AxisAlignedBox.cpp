#include "stdafx.h"
#include "AxisAlignedBox.h"
#include "Verify.h"
#include "Doubles.h"

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

	Vector AxisAlignedBox::CalculateSurfaceNormal(const Point& intersection, bool insideBox) const
	{
		// Test both sides in each axis to find the one we intersect. If we intersect multiple, i.e. an edge or corner, then just return the first one we find. We don't try to do
		// anything complex and arguably wrong like have the normal at an angle.
		for (unsigned int axis = 0; axis < 3; axis++)
		{
			// Are we intersecting on the near side?
			if (Doubles::AreEqual(intersection[axis], minimum[axis]))
			{
				return insideBox ? Vector::Axis(axis) : -Vector::Axis(axis);
			}

			// What about the far side?
			if (Doubles::AreEqual(intersection[axis], maximum[axis]))
			{
				return insideBox ? -Vector::Axis(axis) : Vector::Axis(axis);
			}
		}

		throw std::logic_error("Could not determine side of box for intersection.");
	}

	std::optional<Intersection> AxisAlignedBox::NearestIntersection(const Ray& ray) const
	{
		auto dNear = -std::numeric_limits<double>::infinity();
		auto dFar = std::numeric_limits<double>::infinity();

		for (unsigned int axis = 0; axis < 3; axis++)
		{
			const auto origin = ray.Origin()[axis];
			const auto direction = ray.Direction()[axis];

			if (Doubles::IsNotZero(direction))
			{
				auto dx1 = (minimum[axis] - origin) / direction;
				auto dx2 = (maximum[axis] - origin) / direction;

				dNear = std::max(dNear, std::min(dx1, dx2));
				dFar = std::min(dFar, std::max(dx1, dx2));
			}
			// Ray is parallel to the axis. The ray's origin in that axis therefore needs to lie be inside the box's boundaries.
			else if (origin < minimum[axis] || origin > maximum[axis])
			{
				return std::optional<Intersection>();
			}
		}

		if (dFar < dNear)
		{
			return std::optional<Intersection>();
		}

		auto insideBox = Doubles::IsLessThanZero(dNear);
		auto intersection = ray.Origin() + (insideBox ? dFar : dNear) * ray.Direction();
		auto normal = CalculateSurfaceNormal(intersection, insideBox);
		return Intersection(intersection, normal);
	}
}
