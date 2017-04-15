#include "stdafx.h"
#include <Plane.h>
#include "catch.hpp"
#include "Random.h"
#include "Matchers.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::Geometry::PlaneTests
{
    TEST_CASE("Plane - NearestIntersection - ray above plane intersecting orthogonally", "[Plane]")
    {
        // Plane on origin covering x,y axes with normal pointing into positive z.
        auto plane = Plane(Point(Random::Double(), Random::Double(), 0), Vector(0, 0, Random::GreaterThanZero()));

        // Ray starts above (above meaning +ve z) plane, points straight into negative z.
        auto ray = Ray(Point(Random::Double(), Random::Double(), Random::GreaterThanZero()), Vector(0, 0, Random::LessThanZero()));

        auto result = plane.NearestIntersection(ray);
        REQUIRE(result != nullptr);

        // As ray is pointing straight down intersection point will have the same x and y as the ray's origin.
        CHECK_THAT(result->Point(), Equals(Point(ray.Origin().X(), ray.Origin().Y(), 0)));
        CHECK_THAT(result->Normal(), Equals(plane.Normal()));
    }

    TEST_CASE("Plane - NearestIntersection - ray below plane intersecting orthogonally", "[Plane]")
    {
        // Plane on origin covering x,y axes. Negative z is 'below' the plane.
        auto plane = Plane(Point(Random::Double(), Random::Double(), 0), Vector(0, 0, Random::GreaterThanZero()));
        auto ray = Ray(Point(Random::Double(), Random::Double(), Random::LessThanZero()), Vector(0, 0, Random::GreaterThanZero()));

        auto result = plane.NearestIntersection(ray);
		REQUIRE(result != nullptr);
        CHECK_THAT(result->Point(), Equals(Point(ray.Origin().X(), ray.Origin().Y(), 0)));
        CHECK_THAT(result->Normal(), Equals(-plane.Normal()));
    }
}