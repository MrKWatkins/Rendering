#pragma once
#include "stdafx.h"
#include "Ray.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Geometry
{
    /// <summary>
    /// Base for all geometrical objects.
    /// </summary>
    class Solid
    {
    public:
        virtual ~Solid() = default;

		/// <summary>
		/// Does the specified <see cref="Ray" /> intersect with this <see cref="Solid" />?
		/// </summary>
		virtual bool Intersects(const Ray& ray) const;

		/// <summary>
		/// Find the nearest <see cref="Intersection" /> between the specified <see cref="Ray" /> and this <see cref="Solid" /> or <c>nullptr</c> if
		/// the ray does not intersect.
		/// </summary>
		/// <remarks>
		/// Would be nice to use <see cref="std::optional" /> instead of a pointer as the return type but I had issues with it working with sub types
		/// of <see cref="Intersection" />.
		/// </remarks>
        virtual std::unique_ptr<Intersection> NearestIntersection(const Ray& ray) const = 0;
    };
}
