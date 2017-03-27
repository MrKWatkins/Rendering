#pragma once
#include <optional>	// Needed here because we don't have a Solid.cpp that would include stdafx.h.
#include "Intersection.h"
#include "Ray.h"

namespace MrKWatkins::Rendering::Geometry
{
    /// <summary>
    /// Base for all geometrical objects.
    /// </summary>
    class Solid
    {
    public:
        virtual ~Solid() = default;

		virtual bool IsSphere() const { return false; }

        virtual std::optional<Intersection> NearestIntersection(const Ray& ray) const = 0;
    };
}
