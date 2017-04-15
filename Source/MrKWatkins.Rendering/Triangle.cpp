#include "stdafx.h"
#include "Triangle.h"
#include "Doubles.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	Triangle::Triangle(const Point& vertex0, const Point& vertex1, const Point& vertex2)
		: vertices{ vertex0, vertex1, vertex2 }, edge1{ vertex1 - vertex0 }, edge2{ vertex2 - vertex0 }, vertexNormals{ edge1.Cross(edge2).Normalize(), vertexNormals[0], vertexNormals[0] }
	{
	}

	Triangle::Triangle(const Point& vertex0, const Vector& vertexNormal0, const Point& vertex1, const Vector& vertexNormal1, const Point& vertex2, const Vector& vertexNormal2)
		: vertices{ vertex0, vertex1, vertex2 }, edge1{ vertex1 - vertex0 }, edge2{ vertex2 - vertex0 }, vertexNormals{ vertexNormal0.Normalize(), vertexNormal1.Normalize(), vertexNormal2.Normalize() }
	{
	}

	class TriangleIntersection final : public SolidIntersection<Triangle>
	{
		bool strikingFront;
		double u;
		double v;

	protected:
		Vector CalculateNormal() const override
		{
			auto interpolatedNormal = (1.0 - u - v) * solid->VertexNormal0() + u * solid->VertexNormal1() + v * solid->VertexNormal2();

			return strikingFront ? interpolatedNormal : -interpolatedNormal;
		}
	public:
		TriangleIntersection(const Geometry::Ray& ray, double distanceAlongRay, const Triangle* solid, bool strikingFront, double u, double v)
			: SolidIntersection<Triangle>(ray, distanceAlongRay, solid), strikingFront{ strikingFront }, u{ u }, v{ v }
		{
		}
	};

	std::unique_ptr<Intersection> Triangle::NearestIntersection(const Ray& ray) const
	{
		// See:
		// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
		// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
		auto p = ray.Direction().Cross(edge2);
		auto determinant = edge1.Dot(p);

		if (Doubles::IsZero(determinant))	// TODO: Can we get away without tolerant checks here?
		{
			return nullptr;
		}

		auto inverseDeterminant = 1 / determinant;

		auto t = ray.Origin() - vertices[0];
		auto u = t.Dot(p) * inverseDeterminant;
		if (!Doubles::IsZeroToOne(u))	// TODO: Can we get away without tolerant checks here?
		{
			return nullptr;
		}

		auto q = t.Cross(edge1);
		auto v = ray.Direction().Dot(q) * inverseDeterminant;
		if (Doubles::IsLessThanZero(v) || Doubles::IsGreaterThan(u + v, 1))	// TODO: Can we get away without tolerant checks here?
		{
			return nullptr;
		}

		auto d = edge2.Dot(q) * inverseDeterminant;
		if (Doubles::IsLessThanZero(d))
		{
			return nullptr;
		}

		return std::make_unique<TriangleIntersection>(ray, d, this, Doubles::IsGreaterThanZero(determinant), u, v);
	}

	const Point& Triangle::operator[](unsigned int index) const
	{
		return vertices[index];
	}

	Triangle Triangle::Transform(const Matrix& transformation) const
	{
		return Triangle(
			transformation.Transform(vertices[0]), transformation.Transform(vertexNormals[0]),
			transformation.Transform(vertices[1]), transformation.Transform(vertexNormals[1]),
			transformation.Transform(vertices[2]), transformation.Transform(vertexNormals[2]));
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

	void TriangleVertexIterator::Move()
	{
		VERIFY_CONDITION((triangle != nullptr), "Iteration finished.");
		corner++;
		if (corner == 3)
		{
			triangle = nullptr;
		}
	}

	TriangleVertexIterator::TriangleVertexIterator() : triangle{ nullptr }, corner{ 3 }	// Default constructor generates end().
	{
	}

	TriangleVertexIterator::TriangleVertexIterator(const Triangle* triangle) : triangle{ triangle }
	{
	}

	TriangleVertexIterator& TriangleVertexIterator::operator++()
	{
		Move();
		return *this;
	}

	TriangleVertexIterator TriangleVertexIterator::operator++(int)
	{
		auto copy(*this);
		Move();
		return copy;
	}

	bool TriangleVertexIterator::operator==(const TriangleVertexIterator& other) const
	{
		return triangle == other.triangle && corner == other.corner;
	}

	bool TriangleVertexIterator::operator!=(const TriangleVertexIterator& other) const
	{
		return triangle != other.triangle || corner != other.corner;
	}

	const Point& TriangleVertexIterator::operator*() const
	{
		VERIFY_CONDITION((triangle != nullptr), "Iteration finished.");
		return triangle->operator[](corner);
	}

	const Point& TriangleVertexIterator::operator->() const
	{
		VERIFY_CONDITION((triangle != nullptr), "Iteration finished.");
		return triangle->operator[](corner);
	}
}
