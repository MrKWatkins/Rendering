#pragma once
#include "Solid.h"
#include "Point.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Plane final : public Solid
    {
        Point pointOnPlane;
        Vector normal;
    public:
        Plane(const Point& pointOnPlane, const Vector& normal);

		std::unique_ptr<Intersection> NearestIntersection(const Ray& ray) const override;

        const Point& PointOnPlane() const { return pointOnPlane; }
        const Vector& Normal() const { return normal; }
    };
}
