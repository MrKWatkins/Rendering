#pragma once
#include <optional>
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

        virtual std::optional<Intersection> NearestIntersection(const Ray& ray) const = 0;
    };
}
