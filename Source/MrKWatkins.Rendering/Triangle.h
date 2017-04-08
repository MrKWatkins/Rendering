#pragma once
#include "Solid.h"
#include "Point.h"
#include "Intersection.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	class TriangleCornerIterator;

	class Triangle final : public Solid
	{
		Point corner0;
		Point corner1;
		Point corner2;
	public:
		Triangle(const Point& corner0, const Point& corner1, const Point& corner2);

		std::optional<Intersection> NearestIntersection_MöllerTrumbore(const Ray& ray) const;

		std::optional<Intersection> NearestIntersection(const Ray& ray) const override;

		const Point& Corner0() const { return corner0; }
		const Point& Corner1() const { return corner1; }
		const Point& Corner2() const { return corner2; }

		const Point& operator [](unsigned int index) const;

		typedef TriangleCornerIterator Iterator;

		Iterator begin() const;
		Iterator end() const;
	};

	// Only making a const iterator as Points cannot be mutated.
	class TriangleCornerIterator : public std::iterator<std::forward_iterator_tag, const Point*>
	{
		const Triangle* triangle;
		int corner = 0;

		void Move();
	public:
		TriangleCornerIterator();
		explicit TriangleCornerIterator(const Triangle* triangle);

		TriangleCornerIterator& operator++ ();		// Pre-increment.
		TriangleCornerIterator operator++ (int);	// Post-increment.

		bool operator == (const TriangleCornerIterator& other) const;
		bool operator != (const TriangleCornerIterator& other) const;

		const Point& operator* () const;
		const Point& operator-> () const;
	};
}
