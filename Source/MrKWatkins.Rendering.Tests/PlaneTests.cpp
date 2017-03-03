#include "stdafx.h"
#include "catch.hpp"
#include "Random.h"
// TODO: Use include directory to get rid of path.
#include "../MrKWatkins.Rendering/Plane.h"
#include "Matchers.hpp"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::PointTests
{
    TEST_CASE("Plane - NearestIntersection - ray above plane intersecting orthogonally", "[Plane]")
    {
        // Plane on origin covering x,y axes. Positive z is 'above' the plane.
        auto plane = Plane(Point(Random::Double(), Random::Double(), 0), Vector(0, 0, Random::Double()));
        auto ray = Ray(Point(Random::Double(), Random::Double(), 5 + Random::Double()), Vector(0, 0, -Random::Double()));

        auto result = plane.NearestIntersection(ray);
        REQUIRE(result.HasIntersection() == true);
        REQUIRE_THAT(result.Point(), Equals(Point(ray.Origin().X(), ray.Origin().Y(), 0)));
        REQUIRE_THAT(result.Normal(), Equals(plane.Normal()));
    }

    TEST_CASE("Plane - NearestIntersection - ray below plane intersecting orthogonally", "[Plane]")
    {
        // Plane on origin covering x,y axes. Negative z is 'below' the plane.
        auto plane = Plane(Point(Random::Double(), Random::Double(), 0), Vector(0, 0, Random::Double()));
        auto ray = Ray(Point(Random::Double(), Random::Double(), -5 - Random::Double()), Vector(0, 0, Random::Double()));

        auto result = plane.NearestIntersection(ray);
        REQUIRE(result.HasIntersection() == true);
        REQUIRE_THAT(result.Point(), Equals(Point(ray.Origin().X(), ray.Origin().Y(), 0)));
        REQUIRE_THAT(result.Normal(), Equals(-plane.Normal()));
    }
}