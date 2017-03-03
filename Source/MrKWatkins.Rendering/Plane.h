#pragma once
#include "Object.h"
#include "Point.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Plane : public Object
    {
        Point pointOnPlane;
        Vector normal;
    public:
        Plane(const Point& pointOnPlane, const Vector& normal);

        Intersection NearestIntersection(const Ray& ray) const override;

        const Point& PointOnPlane() const { return pointOnPlane; }

        const Vector& Normal() const { return normal; }
    };
}
