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

	std::optional<Intersection> AxisAlignedBox::NearestIntersection(const Ray& ray) const
	{
		// Use the slabs method (http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm) to find the intersection.
		auto dNear = -std::numeric_limits<double>::infinity();
		auto dFar = std::numeric_limits<double>::infinity();

		for (unsigned int axis = 0; axis < 3; axis++)
		{
			const auto origin = ray.Origin()[axis];
			const auto direction = ray.Direction()[axis];

			// If the direction in this axis is zero then the ray is parallel to the box.
			if (Doubles::IsNotZero(direction))
			{
				// Ray is not parallel. Find out where intersects with the minimum and maximum sides.
				auto dMinimum = (minimum[axis] - origin) / direction;
				auto dMaximum = (maximum[axis] - origin) / direction;

				// The value of d for the near side on this axis side is the smallest of dMinimum and dMaxmimum. Keep the largest value of the current
				// dNear and our value for this axis.
				dNear = std::max(dNear, std::min(dMinimum, dMaximum));

				// Similar to above; the value of d for the far side on this axis is the largest of dMinimum and dMaxmimum. Keep the smallest dFar
				dFar = std::min(dFar, std::max(dMinimum, dMaximum));
			}
			// Ray is parallel to the axis. The ray's origin in that axis therefore needs to lie be inside the box's boundaries.
			else if (origin < minimum[axis] || origin > maximum[axis])
			{
				return std::optional<Intersection>();
			}
		}

		// If the far point is before the near point then the ray does not intersect the box. If the far point is less than zero then both points are behind
		// the origin of the ray.
		if (dFar < 0.0 || dFar < dNear)
		{
			return std::optional<Intersection>();
		}

		// If dNear is less than zero then it is behind the ray's origin - therefore the ray starts inside the box.
		auto insideBox = Doubles::IsLessThanZero(dNear);
		auto intersection = ray.Origin() + (insideBox ? dFar : dNear) * ray.Direction();
		auto normal = CalculateSurfaceNormal(intersection, insideBox);

		return Intersection(intersection, normal);
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
}
