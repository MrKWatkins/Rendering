#include "stdafx.h"
#include "Plane.h"

namespace MrKWatkins::Rendering::Geometry
{
    Plane::Plane(const Point& pointOnPlane, const Vector& normal) : pointOnPlane{ pointOnPlane }, normal{ normal.Normalize() }
    {
    }

    Intersection Plane::NearestIntersection(const Ray& ray) const
    {
        // Ray => R = O + dD.
        // Plane => (P - p).n = 0
        // d = (p - O).n / D.n
        auto Dn = ray.Direction().Dot(normal);
        if (Dn == 0)
        {
            // Ray is parallel to the plane. We'll treat being parallel and in the plane ( (p - O).n = 0 ) as not an intersection.
            return Intersection::None();
        }

        auto d = (pointOnPlane - ray.Origin()).Dot(normal) / Dn;

        // Plug d back into the ray's equation to get the intersection point.
        auto intersection = ray.Origin() + d * ray.Direction();

        // The normal at the surface will depend on which side of the plane we've intersected with. Dn is the dot of the ray direction and the normal -
        // if it's negative they're pointing in opposite directions, in which case the ray is 'above' the plane pointing down so the normal is normal.
        // If it's positive then it's in the same direction so the ray is 'below' the plane - normal needs to be negative.
        if (Dn < 0)
        {
            return Intersection(intersection, normal);
        }
        return Intersection(intersection, -normal);
    }
}
