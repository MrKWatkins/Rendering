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
        if (d < 0)
        {
            // Intersection is behind the ray's origin.
            return Intersection::None();
        }

        // Plug d back into the ray's equation to get the intersection point.
        auto intersection = ray.Origin() + d * ray.Direction();

        // The normal at the surface will depend on which side of the plane we've intersected with. Dn is the dot of the ray direction and the normal.
        // The dot product between two vector is positive for 0 -> 90 degress, then negative for 90 -> 180 degrees, *when both vectors start at the
        // same point*. With our vectors however the ray is in the opposite direction. Therefore when the ray strikes the top our dot product will be
        // negative, and when it strikes the underneath it will be positive.
        if (Dn < 0)
        {
            return Intersection(intersection, normal);
        }
        return Intersection(intersection, -normal);
    }
}
