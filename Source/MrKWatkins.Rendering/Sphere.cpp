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

    Intersection Sphere::NearestIntersection(const Ray& ray) const
    {
        // Ray => R = O + dD.
        // Sphere => (S - C).(S - C) = r * r.
        // M = O - C.
        auto M = ray.Origin() - center;

        // Ray starts inside the sphere if M.M - r² <= 0.
        auto c = M.Dot(M) - radius * radius;
        if (c <= 0)
        {
            throw std::exception("Ray's origin is inside this sphere.");
        }

        // Solutions are -D.M ± √((D.M)² - M.M + r²)
        auto DM = ray.Direction().Dot(M);

        // If the value under the root is negative there can be no (real) solutions.
        auto discriminant = DM * DM - c;
        if (discriminant < 0)
        {
            return Intersection::None();
        }

        // Smallest solution is the one closest to the ray; will occur with the negative solution as the result of the sqrt will always be positive. (Or zero)
        auto d = -DM - sqrt(discriminant);
        if (d < 0)
        {
            return Intersection::None();
        }
        
        // Plug d back into the ray's equation to get the intersection point.
        auto intersection = ray.Origin() + d * ray.Direction();

        // The normal at the surface will be the vector from the centre to the intersection point.
        auto normal = intersection - center;

        return Intersection(intersection, normal);
    }
}
