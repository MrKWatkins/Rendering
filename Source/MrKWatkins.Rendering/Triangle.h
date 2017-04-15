#pragma once
#include "Solid.h"
#include "Point.h"
#include "Matrix.h"

namespace MrKWatkins::Rendering::Geometry
{
	class TriangleVertexIterator;

	class Triangle final : public Solid
	{
		Point vertices[3];
		Vector edge1;
		Vector edge2;
		Vector vertexNormals[3];
	public:
		Triangle(const Point& vertex0, const Point& vertex1, const Point& vertex2);
		Triangle(const Point& vertex0, const Vector& vertexNormal0, const Point& vertex1, const Vector& vertexNormal1, const Point& vertex2, const Vector& vertexNormal2);

		std::unique_ptr<Intersection> NearestIntersection(const Ray& ray) const override;

		const Point& Vertex0() const { return vertices[0]; }
		const Point& Vertex1() const { return vertices[1]; }
		const Point& Vertex2() const { return vertices[2]; }
		const Vector& VertexNormal0() const { return vertexNormals[0]; }
		const Vector& VertexNormal1() const { return vertexNormals[1]; }
		const Vector& VertexNormal2() const { return vertexNormals[2]; }

		const Point& operator [](unsigned int index) const;

		Triangle Transform(const Matrix& transformation) const;

		typedef TriangleVertexIterator Iterator;

		Iterator begin() const;
		Iterator end() const;
	};

	// Only making a const iterator as Points cannot be mutated.
	class TriangleVertexIterator : public std::iterator<std::forward_iterator_tag, const Point*>
	{
		const Triangle* triangle;
		int corner = 0;

		void Move();
	public:
		TriangleVertexIterator();
		explicit TriangleVertexIterator(const Triangle* triangle);

		TriangleVertexIterator& operator++ ();		// Pre-increment.
		TriangleVertexIterator operator++ (int);	// Post-increment.

		bool operator == (const TriangleVertexIterator& other) const;
		bool operator != (const TriangleVertexIterator& other) const;

		const Point& operator* () const;
		const Point& operator-> () const;
	};
}
