#pragma once
#include "Object.h"
#include "Point.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Sphere final : public Object
    {
        Point centre;
        double radius;
    public:
        Sphere(const Point& centre, double radius);
        Sphere(double x, double y, double z, double r);

        Intersection NearestIntersection(const Ray& ray) const override;

        const Point& Centre() const { return centre; }

        double Radius() const { return radius; }
    };
}
