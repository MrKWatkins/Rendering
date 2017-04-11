#pragma once
#include "Solid.h"
#include "Point.h"
#include "RayIntersection.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Plane final : public Solid
    {
        Point pointOnPlane;
        Vector normal;
    public:
        Plane(const Point& pointOnPlane, const Vector& normal);

	    std::optional<RayIntersection> NearestRayIntersection(const Ray& ray) const override;

        const Point& PointOnPlane() const { return pointOnPlane; }

        const Vector& Normal() const { return normal; }

		Vector GetSurfaceNormal(const RayIntersection& rayIntersection, const Point& pointOnSurface) const override;
    };
}
