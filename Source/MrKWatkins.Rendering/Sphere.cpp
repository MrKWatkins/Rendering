#include "stdafx.h"
#include "Sphere.h"

namespace MrKWatkins::Rendering::Geometry
{
    Sphere::Sphere(const Point& center, double radius) : center{center}, radius{radius}
    {
    }

    Sphere::Sphere(double x, double y, double z, double r): center{ x, y, z }, radius{ r }
    {
    }

    Optional<Point> Sphere::NearestIntersection(const Ray& ray) const
    {
        // Based on http://gamedev.stackexchange.com/a/96487/12495. Explanation at
        // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.

        auto m = ray.Origin() - center;

        // a = 1.
        auto b = m.Dot(ray.Direction());
        auto c = m.Dot(m) - radius * radius;

        // No intersection if r’s origin outside s (c > 0) and r pointing away from s. (b > 0)
        if (b > 0 && c > 0)
        {
            return Optional<Point>();
        }

        auto discriminant = b * b - c;

        // A negative discriminant corresponds to ray missing sphere 
        if (discriminant < 0)
        {
            return Optional<Point>();
        }

        // Ray now found to intersect sphere, compute smallest t value of intersection
        auto t = -b - sqrt(discriminant);

        // If t is negative, ray started inside sphere.
        if (t < 0.0f)
        {
            throw std::exception("Not yet implemented.");
        }
        
        return Optional<Point>(ray.Origin() + t * ray.Direction());
    }
}
