#pragma once
#include "Point.h"
#include "Vector.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Intersection final
    {
        bool hasIntersection;
        Point point;
        Vector surfaceNormal;

        void VerifyIntersection() const
        {
            if (!hasIntersection)
            {
                throw std::logic_error("No intersection.");
            }
        }

        Intersection();

    public:
        Intersection(const Point& point, const Vector& surfaceNormal);

        bool HasIntersection() const noexcept { return hasIntersection; }

        const Point& Point() const;
        const Vector& SurfaceNormal() const;

        static Intersection None() { return Intersection(); }
    };
}
