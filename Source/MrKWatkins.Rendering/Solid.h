#pragma once
#include <optional>	// Needs to be here for some reason despite being in stdafx.h.
#include "Ray.h"
#include "RayIntersection.h"
#include "SurfaceIntersection.h"

namespace MrKWatkins::Rendering::Geometry
{
    /// <summary>
    /// Base for all geometrical objects.
    /// </summary>
    class Solid
    {
    public:
        virtual ~Solid() = default;

		bool Intersects(const Ray& ray) const;

		/// <summary>
		/// Finds details of the nearest intersection with the specified ray. Prefer this method to NearestSurfaceIntersection if possible as that
		/// has extra work to do to find the exact point and surface normal.
		/// </summary>
        virtual std::optional<RayIntersection> NearestRayIntersection(const Ray& ray) const = 0;

		/// <summary>
		/// Finds details of the surface at the nearest intersection pointwith the specified ray. 
		/// </summary>
        std::optional<SurfaceIntersection> NearestSurfaceIntersection(const Ray& ray) const;

		/// <summary>
		/// Get the full details of the specified intersection on the surface of the solid from the ray intersection.
		/// </summary>
		SurfaceIntersection GetSurfaceIntersection(const Ray& ray, const RayIntersection& rayIntersection) const;

		virtual Vector GetSurfaceNormal(const RayIntersection& rayIntersection, const Point& pointOnSurface) const = 0;
    };
}
