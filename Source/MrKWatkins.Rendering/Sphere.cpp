#include "stdafx.h"
#include "Sphere.h"

namespace MrKWatkins::Rendering::Geometry
{
    Sphere::Sphere(const Point& centre, double radius) : centre{ centre }, radius{radius}
    {
    }

    Sphere::Sphere(double x, double y, double z, double r): centre{ x, y, z }, radius{ r }
    {
    }

	std::optional<Intersection> Sphere::NearestIntersection(const Ray& ray) const
    {
        // Ray => R = O + dD.
        // Sphere => (S - C).(S - C) = r * r.
        // M = O - C.
        auto M = ray.Origin() - centre;

        // Ray starts outside the sphere if M.M - r² > 0.
        auto c = M.Dot(M) - radius * radius;
		auto outsideSphere = c > 0;

        // Solutions are -D.M ± √((D.M)² - M.M + r²)
        auto DM = ray.Direction().Dot(M);

        // If the value under the root is negative there can be no (real) solutions.
        auto discriminant = DM * DM - c;
        if (discriminant < 0)
        {
			return std::optional<Intersection>();
        }

        // Smallest solution is the one closest to the ray; will occur with the negative solution as the result of the sqrt will always be positive. (Or zero)
		// The exception to this is if we're inside the sphere then it will be the greater solution as the smallest one starts behind us.
        auto d = outsideSphere ? -DM - sqrt(discriminant) : -DM + sqrt(discriminant);
        if (d < 0)
        {
            return std::optional<Intersection>();
        }
        
        // Plug d back into the ray's equation to get the intersection point.
        auto intersection = ray.Origin() + d * ray.Direction();

        // The normal at the surface will be the vector from the centre to the intersection point, unless we're inside the sphere in which case it will be in the opposite direction.
        auto normal = outsideSphere ? intersection - centre : centre - intersection;

        return Intersection(intersection, normal);
    }
}
