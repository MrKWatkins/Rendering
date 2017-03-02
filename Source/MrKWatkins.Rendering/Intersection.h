#pragma once
#include "Point.h"
#include "Vector.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Intersection
    {
        bool hasIntersection;
        Point point;
        Vector normal;

        void VerifyIntersection() const
        {
            if (!hasIntersection)
            {
                throw std::logic_error("No intersection.");
            }
        }

        Intersection();

    public:
        Intersection(Point point, Vector normal);

        bool HasIntersection() const noexcept { return hasIntersection; }

        Point Point() const;
        Vector Normal() const;

        static Intersection None() { return Intersection(); }
    };
}
