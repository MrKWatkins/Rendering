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

	Matrix AxisAlignedBox::GetNormalizeTransform() const
	{
		// To normalize we need to first move the mesh to start at (0, 0, 0).
		auto translate = Matrix::Translate(-minimum.X(), -minimum.Y(), -minimum.Z());

		// Then we need to scale it. We need to find the largest side of the box and scale by the inverse of that.
		auto largestSide = std::max(std::max(Width(), Height()), Depth());
		if (largestSide == 0)
		{
			// We could in theory return a zero volume mesh but it's far more likely we've done something stupid so throw instead.
			throw std::logic_error("Mesh has zero volume.");
		}

		auto scale = Matrix::Scale(1.0 / largestSide);

		return scale * translate;
	}

	bool AxisAlignedBox::NearestIntersection(const Ray& ray, double& dNear, double& dFar) const
	{
		// Use the slabs method (http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm) to find the intersection.
		dNear = -std::numeric_limits<double>::infinity();
		dFar = std::numeric_limits<double>::infinity();

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
				return false;
			}
		}

		// If the far point is before the near point then the ray does not intersect the box. If the far point is less than zero then both points are behind
		// the origin of the ray.
		if (dFar < 0.0 || dFar < dNear)
		{
			return false;
		}

		return true;
	}

	bool AxisAlignedBox::Intersects(const Ray& ray) const
	{
		// Common case is to just test intersection true/false so we specialise here to avoid allocation of an Intersection instance.
		double dNear, dFar;
		return NearestIntersection(ray, dNear, dFar);
	}

	class AxisAlignedBoxIntersection final : public SolidIntersection<AxisAlignedBox>
	{
		bool outsideBox;
	protected:
		Vector CalculateNormal() const override
		{
			auto pointOnSurface = Point();

			// Test both sides in each axis to find the one we intersect. If we intersect multiple, i.e. an edge or corner, then just return the first one we find. We don't try to do
			// anything complex (and arguably wrong!) like have the normal at an angle.
			for (unsigned int axis = 0; axis < 3; axis++)
			{
				// Are we intersecting on the near side?
				if (Doubles::AreEqual(pointOnSurface[axis], solid->Minimum()[axis]))
				{
					return outsideBox ? -Vector::Axis(axis) : Vector::Axis(axis);
				}

				// What about the far side?
				if (Doubles::AreEqual(pointOnSurface[axis], solid->Maximum()[axis]))
				{
					return outsideBox ? Vector::Axis(axis) : -Vector::Axis(axis);
				}
			}

			throw std::logic_error("Could not determine side of box for intersection.");
		}
	public:
		AxisAlignedBoxIntersection(const Geometry::Ray& ray, double distanceAlongRay, const AxisAlignedBox* solid, bool outsideBox)
			: SolidIntersection<AxisAlignedBox>(ray, distanceAlongRay, solid), outsideBox { outsideBox }
		{
		}
	};

	std::unique_ptr<Intersection> AxisAlignedBox::NearestIntersection(const Ray& ray) const
	{
		double dNear, dFar;
		if (!NearestIntersection(ray, dNear, dFar))
		{
			return nullptr;
		}

		// If dNear is less than zero then it is behind the ray's origin - therefore the ray starts inside the box.
		auto intersectsOutside = Doubles::IsGreaterThanZero(dNear);
		return std::make_unique<AxisAlignedBoxIntersection>(ray, intersectsOutside ? dNear : dFar, this, intersectsOutside);
	}
}
