#pragma once
#include "Point.h"
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

		std::unique_ptr<Intersection> NearestIntersection(const Ray& ray) const override;

        const Point& Centre() const { return centre; }
        double Radius() const { return radius; }
    };
}
