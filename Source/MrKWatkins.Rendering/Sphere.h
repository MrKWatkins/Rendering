#pragma once
#include "Point.h"
#include "RayIntersection.h"
#include "Solid.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Sphere final : public Solid
    {
        Point centre;
        double radius;
    public:
        Sphere(const Point& centre, double radius);
        Sphere(double x, double y, double z, double r);

	    std::optional<RayIntersection> NearestRayIntersection(const Ray& ray) const override;

        const Point& Centre() const { return centre; }
        double Radius() const { return radius; }

		Vector GetSurfaceNormal(const RayIntersection& rayIntersection, const Point& pointOnSurface) const override;
    };
}
