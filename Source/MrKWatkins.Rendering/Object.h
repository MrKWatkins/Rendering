#pragma once
#include "Point.h"
#include "Optional.h"
#include "Ray.h"

namespace MrKWatkins::Rendering::Geometry
{
    /// <summary>
    /// Base for all geometrical objects.
    /// </summary>
    class Object
    {
    public:
        virtual ~Object() = default;

        virtual Optional<Point> NearestIntersection(const Ray& ray) const = 0;
    };
}
