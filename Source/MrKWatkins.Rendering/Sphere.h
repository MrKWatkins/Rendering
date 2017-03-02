#pragma once
#include "Object.h"
#include "Point.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Geometry
{
    class Sphere : public Object
    {
        Point center;
        double radius;
    public:
        Sphere(const Point& center, double radius);
        Sphere(double x, double y, double z, double r);

        Intersection NearestIntersection(const Ray& ray) const override;
    };
}
