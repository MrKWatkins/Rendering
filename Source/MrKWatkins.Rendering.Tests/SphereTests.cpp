#include "stdafx.h"
#include "catch.hpp"
#include "Random.h"
// TODO: Use include directory to get rid of path.
#include "../MrKWatkins.Rendering/Sphere.h"
#include "Matchers.hpp"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::PointTests
{
    // TODO: Optional equals.
    // TODO: Test Ray normalizes direction.
    TEST_CASE("Sphere - NearestIntersection - sphere behind ray", "[Sphere]")
    {
        // Sphere centered at point on negative x-axis with radius less than distance along x-axis so sphere entirely in negative x.
        // No intersection with ray along positive x-axis.
        auto radius = Random::Double();
        auto xOrigin = -Random::Double() * radius;
        auto result = Sphere(Point(xOrigin, 0, 0), radius).NearestIntersection(Ray(Point::Origin(), Vector(1, 0, 0)));
        REQUIRE(result.HasValue() == false);
    }

    TEST_CASE("Sphere - NearestIntersection - ray and sphere on x axis", "[Sphere]")
    {
        // Sphere centered at point on x-axis with radius less than distance along x-axis so sphere entirely in positive x.
        // Intersection with ray along x-axis will be at origin - radius on x-axis.
        auto radius = Random::Double();
        auto xOrigin = Random::Double() * radius;
        auto result = Sphere(Point(xOrigin, 0, 0), radius).NearestIntersection(Ray(Point::Origin(), Vector(1, 0, 0)));
        REQUIRE(result.HasValue() == true);
        REQUIRE_THAT(result.Value(), Equals(Point(xOrigin - radius, 0, 0)));
    }

    TEST_CASE("Sphere - NearestIntersection - ray and sphere at origin", "[Sphere]")
    {
        // Sphere centered at origin, ray starting at origin heading down x axis. Should intersect once at sphere radius on the x-axis.
        auto radius = Random::Double();
        auto result = Sphere(Point::Origin(), radius).NearestIntersection(Ray(Point::Origin(), Vector(1, 0, 0)));
        REQUIRE(result.HasValue() == true);
        REQUIRE_THAT(result.Value(), Equals(Point(radius, 0, 0)));
    }
}