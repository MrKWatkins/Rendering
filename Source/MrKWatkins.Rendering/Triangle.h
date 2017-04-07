#pragma once
#include "Solid.h"
#include "Point.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Geometry
{
	class Triangle final : public Solid
	{
		Point corner1;
		Point corner2;
		Point corner3;
	public:
		Triangle(const Point& corner1, const Point& corner2, const Point& corner3);

		std::optional<Intersection> NearestIntersection_MöllerTrumbore(const Ray& ray) const;

		std::optional<Intersection> NearestIntersection(const Ray& ray) const override;

		const Point& Corner1() const { return corner1; }
		const Point& Corner2() const { return corner2; }
		const Point& Corner3() const { return corner3; }
	};
}
