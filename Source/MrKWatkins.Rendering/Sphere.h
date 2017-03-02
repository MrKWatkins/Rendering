#pragma once
#include "Object.h"
#include "Point.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Sphere : public Object
    {
        Point center;
        double radius;
    public:
        Sphere(const Point& center, double radius);
        Sphere(double x, double y, double z, double r);

        Optional<Point> NearestIntersection(const Ray& ray) const override;
    };
}