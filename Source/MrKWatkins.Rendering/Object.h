#pragma once
#include "Intersection.h"
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

        virtual Intersection NearestIntersection(const Ray& ray) const = 0;
    };
}
