#pragma once
#include "Solid.h"
#include "Point.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Geometry
{
	class AxisAlignedBox final : public Solid
	{
		Point minimum;
		Point maximum;
	public:
		AxisAlignedBox(const Point& minimum, const Point& maximum);
		AxisAlignedBox(const Point& closestCorner, double width, double height, double depth);

		const Point& Minimum() const noexcept { return minimum; }
		const Point& Maximum() const noexcept { return maximum; }

		std::optional<Intersection> NearestIntersection(const Ray& ray) const override;
	};
}
