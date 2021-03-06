#pragma once
#include "Point.h"
#include "Vector.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Ray final
    {
        Point origin;
        Vector direction;
    public:
        Ray(const Point& origin, const Vector& direction);

		/// <summary>
		/// Resolves a distance along the ray into a point.
		/// </summary>
		Point ResolveDistance(double distance) const;

        /// <summary>
        /// The origin of the ray.
        /// </summary>
        const Point& Origin() const { return origin; }

        /// <summary>
        /// The direction of the ray. This will be a normalized vector.
        /// </summary>
        const Vector& Direction() const { return direction; }
    };
}