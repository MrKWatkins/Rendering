#include "stdafx.h"
#include "Triangle.h"
#include "Doubles.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	Triangle::Triangle(const Point& corner1, const Point& corner2, const Point& corner3) : corner1 { corner1 }, corner2 { corner2 }, corner3 { corner3 }
	{
	}

	std::optional<Intersection> Triangle::NearestIntersection(const Ray& ray) const
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
		if (Doubles::IsLessThanZero(u) || Doubles::IsGreaterThan(u, 1))	// TODO: Can we get away without tolerant checks here?
		{
			return std::optional<Intersection>();
		}

		auto q = t.Cross(edge1);
		auto v = ray.Direction().Dot(q) * inverseDeterminant;
		if (Doubles::IsLessThanZero(v) || Doubles::IsGreaterThan(u + v, 1))	// TODO: Can we get away without tolerant checks here?
		{
			return std::optional<Intersection>();
		}

		//if (Doubles::IsLessThanZero(edge2.Dot(q) * inverseDeterminant))
		//{
		//	return std::optional<Intersection>();
		//}

		auto point = ResolveBarycentricCoordinates(u, v);
		auto normal = edge1.Cross(edge2);
		if (Doubles::IsLessThanZero(determinant))
		{
			normal = -normal;
		}
		return Intersection(point, normal);
	}

	Point Triangle::ResolveBarycentricCoordinates(double u, double v) const
	{
		VERIFY_ZERO_TO_ONE(u);
		VERIFY_ZERO_TO_ONE(v);

		auto w = 1 - u - v;
		VERIFY_ZERO_TO_ONE(w);

		return Point(
			u * corner1.X() + v * corner2.X() + w * corner3.X(),
			u * corner1.Y() + v * corner2.Y() + w * corner3.Y(),
			u * corner1.Z() + v * corner2.Z() + w * corner3.Z());
	}
}
