#pragma once
#include "stdafx.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"

namespace MrKWatkins::Rendering::Geometry
{
	/// <summary>
	/// Details of an intersection between a <see cref="Ray" /> and a <see cref="Solid" />.
	/// </summary>
	class Intersection
	{
		mutable std::optional<Point> point;
		mutable std::optional<Vector> normal;

	protected:
		const Ray* ray;
		double distanceAlongRay;

		/// <summary>
		/// Calculates the surface normal at the intersection point. Should return a normalized <see cref="Vector" />.
		/// </summary>
		virtual Vector CalculateNormal() const;
	public:
		virtual ~Intersection() = default;
		Intersection(const Ray& ray, double distanceAlongRay);
		Intersection(const Ray& ray, double distanceAlongRay, const Vector& normal);

		/// <summary>
		/// The <see cref="Ray" /> the intersection is for.
		/// </summary>
		const Ray& Ray() const noexcept { return *ray; }

		/// <summary>
		/// The distance along the <see cref="Ray" /> to the intersection point.
		/// </summary>
		double DistanceAlongRay() const noexcept { return distanceAlongRay; }

		/// <summary>
		/// The intersection point.
		/// </summary>
		const Point& Point() const;

		/// <summary>
		/// The surface normal at the intersection point.
		/// </summary>
		const Vector& Normal() const;
	};

	class Solid;

	template<class TSolid>
	class SolidIntersection : public Intersection
	{
		static_assert(std::is_base_of<Solid, TSolid>::value, "TSolid is not an instance of Solid.");

	protected:
		const TSolid* solid;
	public:
		SolidIntersection(const Geometry::Ray& ray, double distanceAlongRay, const TSolid* solid)
			: Intersection(ray, distanceAlongRay), solid { solid }
		{
		}
	};
}
