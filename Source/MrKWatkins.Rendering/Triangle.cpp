#include "stdafx.h"
#include "Triangle.h"
#include "Doubles.h"

namespace MrKWatkins::Rendering::Geometry
{
	Triangle::Triangle(const Point& corner1, const Point& corner2, const Point& corner3) : corner1 { corner1 }, corner2 { corner2 }, corner3 { corner3 }
	{
	}

	std::optional<Intersection> Triangle::NearestIntersection_MöllerTrumbore(const Ray& ray) const
	{
		// See:
		// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
		// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
		auto edge1 = corner2 - corner1;
		auto edge2 = corner3 - corner1;

		auto p = ray.Direction().Cross(edge2);
		auto determinant = edge1.Dot(p);

		if (Doubles::IsZero(determinant))
		{
			return std::optional<Intersection>();
		}

		auto inverseDeterminant = 1 / determinant;

		auto t = ray.Origin() - corner1;
		auto u = t.Dot(p) * inverseDeterminant;
		if (!Doubles::IsZeroToOne(u))	// TODO: Can we get away without tolerant checks here?
		{
			return std::optional<Intersection>();
		}

		auto q = t.Cross(edge1);
		auto v = ray.Direction().Dot(q) * inverseDeterminant;
		if (Doubles::IsLessThanZero(v) || Doubles::IsGreaterThan(u + v, 1))	// TODO: Can we get away without tolerant checks here?
		{
			return std::optional<Intersection>();
		}

		auto d = edge2.Dot(q) * inverseDeterminant;
		if (Doubles::IsLessThanZero(d))
		{
			return std::optional<Intersection>();
		}

		auto point = ray.Origin() + d * ray.Direction();
		auto normal = edge1.Cross(edge2);
		if (Doubles::IsLessThanZero(determinant))
		{
			normal = -normal;
		}
		return Intersection(point, normal);
	}

	std::optional<Intersection> Triangle::NearestIntersection(const Ray& ray) const
	{
		return NearestIntersection_MöllerTrumbore(ray);
	}
}
