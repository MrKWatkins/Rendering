#include "stdafx.h"
#include "Triangle.h"
#include "Doubles.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	Triangle::Triangle(const Point& corner0, const Point& corner1, const Point& corner2)
		: corner0{ corner0 }, corner1{ corner1 }, corner2{ corner2 }, edge1{ corner1 - corner0 }, edge2{ corner2 - corner0 }, normal{ edge1.Cross(edge2) }
	{
	}

	std::optional<RayIntersection> Triangle::NearestRayIntersection(const Ray& ray) const
	{
		// See:
		// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
		// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
		auto p = ray.Direction().Cross(edge2);
		auto determinant = edge1.Dot(p);

		if (Doubles::IsZero(determinant))
		{
			return std::optional<RayIntersection>();
		}

		auto inverseDeterminant = 1 / determinant;

		auto t = ray.Origin() - corner0;
		auto u = t.Dot(p) * inverseDeterminant;
		if (!Doubles::IsZeroToOne(u))	// TODO: Can we get away without tolerant checks here?
		{
			return std::optional<RayIntersection>();
		}

		auto q = t.Cross(edge1);
		auto v = ray.Direction().Dot(q) * inverseDeterminant;
		if (Doubles::IsLessThanZero(v) || Doubles::IsGreaterThan(u + v, 1))	// TODO: Can we get away without tolerant checks here?
		{
			return std::optional<RayIntersection>();
		}

		auto d = edge2.Dot(q) * inverseDeterminant;
		if (Doubles::IsLessThanZero(d))
		{
			return std::optional<RayIntersection>();
		}

		return RayIntersection(d, Doubles::IsGreaterThanZero(determinant));
	}

	// ReSharper disable once CppParameterNeverUsed - required for base class.
	Vector Triangle::GetSurfaceNormal(const RayIntersection& rayIntersection, const Point& pointOnSurface) const
	{
		return rayIntersection.IntersectingOutside() ? normal : -normal;
	}

	const Point& Triangle::operator[](unsigned int index) const
	{
		switch (index)
		{
		case 0:
			return corner0;
		case 1:
			return corner1;
		case 2:
			return corner2;
		}

		throw std::out_of_range("index equals " + std::to_string(index) + " which is not in the range 0 -> 2.");
	}

	Triangle Triangle::Transform(const Matrix& transformation) const
	{
		return Triangle(transformation.Transform(corner0), transformation.Transform(corner1), transformation.Transform(corner2));
	}

	Triangle::Iterator Triangle::begin() const
	{
		return Iterator(this);
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	Triangle::Iterator Triangle::end() const
	{
		return Iterator();
	}

	void TriangleCornerIterator::Move()
	{
		VERIFY_CONDITION((triangle != nullptr), "Iteration finished.");
		corner++;
		if (corner == 3)
		{
			triangle = nullptr;
		}
	}

	TriangleCornerIterator::TriangleCornerIterator() : triangle{ nullptr }, corner{ 3 }	// Default constructor generates end().
	{
	}

	TriangleCornerIterator::TriangleCornerIterator(const Triangle* triangle) : triangle{ triangle }
	{
	}

	TriangleCornerIterator& TriangleCornerIterator::operator++()
	{
		Move();
		return *this;
	}

	TriangleCornerIterator TriangleCornerIterator::operator++(int)
	{
		auto copy(*this);
		Move();
		return copy;
	}

	bool TriangleCornerIterator::operator==(const TriangleCornerIterator& other) const
	{
		return triangle == other.triangle && corner == other.corner;
	}

	bool TriangleCornerIterator::operator!=(const TriangleCornerIterator& other) const
	{
		return triangle != other.triangle || corner != other.corner;
	}

	const Point& TriangleCornerIterator::operator*() const
	{
		VERIFY_CONDITION((triangle != nullptr), "Iteration finished.");
		return triangle->operator[](corner);
	}

	const Point& TriangleCornerIterator::operator->() const
	{
		VERIFY_CONDITION((triangle != nullptr), "Iteration finished.");
		return triangle->operator[](corner);
	}
}
